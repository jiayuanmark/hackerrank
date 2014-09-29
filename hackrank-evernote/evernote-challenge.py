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

punc = set(string.punctuation.translate(None, "'"))

def normalize(s):
	while len(s) > 0 and s[0] in punc:
		s = s[1:]
	while len(s) > 0 and s[-1] in punc:
		s = s[:-1]
	return s

class Article:
	def __init__(self, s):
		self.data = {}
		xmlroot = ET.fromstring(s)
		for child in xmlroot:
			val = child.text.strip()
			if child.tag != "guid" and child.tag != "created":
				val = val.lower()
			if child.tag == "tag":
				self.data.setdefault("tag", []).append(val)
			else:
				self.data[child.tag] = val

	def __getitem__(self, field):
		if field == "tag":
			return self.data.get("tag", [])
		return self.data[field]

class Corpus:
	def __init__(self):
		self.termIndex = {} # term-to-guid index
		self.tagIndex = {} # tag-to-guid index
		self.article = {} # all articles
		self.deleted = set()

	def printResult(self, res):
		res = sorted(res, key=lambda x: isoDateToEpoch(self.article[x]["created"]))
		print "%s" % ",".join(res)

	def create(self, article):
		guid = article["guid"]
		self.article[guid] = article
		self.deleted.discard(guid)
		# Update index
		content = article["content"]
		for token in content.split():
			token = normalize(token)
			if len(token) == 0:
				continue
			self.termIndex.setdefault(token.lower(), set()).add(guid)
		tags = article["tag"]
		for t in tags:
			self.tagIndex.setdefault(t, set()).add(guid)

	def update(self, article):
		guid = article["guid"]
		old = self.article[guid]
		# Remove from index
		content = old["content"]
		for token in content.split():
			token = normalize(token)
			if len(token) == 0:
				continue
			self.termIndex.setdefault(token.lower(), set()).discard(guid)
		tags = old["tag"]
		for t in tags:
			self.tagIndex.setdefault(t, set()).discard(guid)
		self.create(article)

	def delete(self, guid):
		self.deleted.add(guid)

	def searchByTerms(self, terms):
		resList = []
		for term in terms.split():
			q = makeRegexQuery(term.lower())
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
		q = makeRegexQuery(tag.lower())
		for key in self.tagIndex:
			if re.match(q, key) is not None:
				res.update(self.tagIndex[key])
		res.difference_update(self.deleted)
		self.printResult(res)

	def searchByCreateTime(self, time):
		dt = datetime.strptime(time, "%Y%m%d")
		ts = int(dt.strftime('%s'))
		after = filter(lambda x : isoDateToEpoch(x["created"]) >= ts, self.article.values())
		res = set(map(lambda x:x["guid"], after))
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
