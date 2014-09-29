import sys, re, string
import xml.etree.ElementTree as ET
from datetime import datetime

def isoDateToEpoch(s):
	dt = datetime.strptime(s, "%Y-%m-%dT%H:%M:%SZ")
	return int(dt.strftime('%s'))

def makeRegexQuery(s):
	if s.endswith("*"):
		t = s[:-1]
	else:
		t = s + '\Z'
	return ('^' + t)

class Article:
	def __init__(self, s):
		self.data = {}
		xmlroot = ET.fromstring(s)
		for child in xmlroot:
			if child.tag == "tag":
				self.data.setdefault("tag", []).append(child.text)
			else:
				self.data[child.tag] = child.text.strip()

	def __getitem__(self, field):
		if field == "tag":
			return self.data.get("tag", [])
		return self.data[field]

class Corpus:
	def __init__(self):
		self.termIndex = {}
		self.tagIndex = {}
		self.createIndex = {}
		self.article = {}
		self.deleted = set([])

	def printResult(self, res):
		res = sorted(res, key=lambda x: isoDateToEpoch(self.article[x]["created"]))
		print "%s" % ",".join(res)

	def create(self, article):
		guid = article["guid"]
		self.article[guid] = article
		self.deleted.discard(guid)
		# Add
		content = article["content"]
		for token in content.split():
			token = token.translate(None, string.punctuation.translate(None, "\'"))
			self.termIndex.setdefault(token.lower(), set()).add(guid)
		tags = article["tag"]
		for t in tags:
			self.tagIndex.setdefault(t, set()).add(guid)
		self.createIndex.setdefault(isoDateToEpoch(article["created"]), set([])).add(guid)

	def update(self, article):
		guid = article["guid"]
		old = self.article[guid]
		# Remove
		content = old["content"]
		for token in content.split():
			token = token.translate(None, string.punctuation.translate(None, "\'"))
			self.termIndex.setdefault(token.lower(), set()).discard(guid)
		tags = old["tag"]
		for t in tags:
			self.tagIndex.setdefault(t, set()).discard(guid)
		self.createIndex.setdefault(isoDateToEpoch(old["created"]), set([])).discard(guid)
		self.create(article)

	def delete(self, guid):
		self.deleted.add(guid)

	def searchByTerms(self, terms):
		resList = []
		for term in terms.split():
			q = makeRegexQuery(term)
			res = set()
			for key in self.termIndex:
				if re.match(q, key) is not None:
					res.update(self.termIndex[key])
			resList.append(res)

		allres = resList[0]
		for s in resList:
			allres.intersection_update(s) 

		allres.difference_update(self.deleted)
		self.printResult(allres)

	def searchByTag(self, tag):
		res = set()
		q = makeRegexQuery(tag)
		for key in self.tagIndex:
			if re.match(q, key) is not None:
				res.update(self.tagIndex[key])
		res.difference_update(self.deleted)
		self.printResult(res)

	def searchByCreateTime(self, time):
		dt = datetime.strptime(time, "%Y%m%d")
		ts = int(dt.strftime('%s'))

		res = set()
		for key in self.createIndex:
			if key >= ts:
				res.update(self.createIndex[key])
		res.difference_update(self.deleted)
		self.printResult(res)

class Command:
	def __init__(self, cmd, payload):
		self.cmd = cmd
		self.payload = payload

	def execute(self, corpus):
		if self.cmd == "CREATE":
			article = Article(self.payload)
			corpus.create(article)
		elif self.cmd == "UPDATE":
			article = Article(self.payload)
			corpus.update(article)
		elif self.cmd == "DELETE":
			corpus.delete(self.payload)
		elif self.cmd == "SEARCH":
			if self.payload.startswith("tag:"):
				corpus.searchByTag(self.payload[4:])
			elif self.payload.startswith("created:"):
				corpus.searchByCreateTime(self.payload[8:])
			else:
				corpus.searchByTerms(self.payload)

def parseCommands(content):
	commands = set(["CREATE", "UPDATE", "DELETE", "SEARCH"])
	buf, res = [], []
	lastCommand = None
	
	for line in content:
		line = line.strip().replace("&", "&amp;")
		if line in commands:
			if lastCommand is not None:
				res.append(Command(lastCommand, "\n".join(buf)))
			lastCommand = line
			buf = []
		else:
			buf.append(line)

	if lastCommand is not None:
		res.append(Command(lastCommand, "\n".join(buf)))
	return res

if __name__ == "__main__":
	data = sys.stdin.readlines()
	commandLst = parseCommands(data)
	corpus = Corpus()

	for cmd in commandLst:
		cmd.execute(corpus)
