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
		# update index
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
		# remove from index
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

	def search(self, querystr):
		query = querystr.lower().split()
		tagQuery, termQuery = [], []
		timeQuery = 0
		for subquery in query:
			if subquery.startswith("tag:"):
				tagQuery.append(subquery[4:])
			elif subquery.startswith("created:"):
				dt = datetime.strptime(subquery[8:], "%Y%m%d")
				timeQuery = max(timeQuery, int(dt.strftime('%s')))
			else:
				termQuery.append(subquery)

		res = None
		# create time query
		if timeQuery != 0:
			res = self.searchByCreateTime(timeQuery)
			if len(res) == 0:
				self.printResult(res)
				return
		# tag query
		if len(tagQuery) != 0:
			res = self.searchByTermOrTag(self.tagIndex, tagQuery, res)
			if len(res) == 0:
				self.printResult(res)
				return
		# term query
		if len(termQuery) != 0:
			res = self.searchByTermOrTag(self.termIndex, termQuery, res)

		self.printResult(res)


	def searchByTermOrTag(self, index, query, res=None):
		prefixQuery = filter(lambda x:x.endswith("*"), query)
		normalQuery = filter(lambda x:not x.endswith("*"), query)

		# order by length
		normalQuery = sorted(normalQuery, key=lambda x:len(index.get(x, set())))
		
		# initial set
		sol = None
		if res is not None:
			sol = res
		elif len(normalQuery) != 0:
			sol = index.get(normalQuery[0], set())
		else:
			sol = set()
			pq = makeRegexQuery(prefixQuery[0])
			for key in index:
				if re.match(pq, key) is not None:
					sol.update(index[key])

		# execute normal query
		for qry in normalQuery:
			sol.intersection_update(index.get(qry, set()))
			if len(sol) == 0:
				return sol

		# execute prefix query
		for pqry in prefixQuery:
			temp = set()
			pq = makeRegexQuery(pqry)
			for key in index:
				if re.match(pq, key) is not None:
					temp.update(index[key])
			sol.intersection_update(temp)
			if len(sol) == 0:
				return sol
		sol.difference_update(self.deleted)
		return sol

	def searchByCreateTime(self, time):
		after = filter(lambda x : isoDateToEpoch(x["created"]) >= time, self.article.values())
		res = set(map(lambda x:x["guid"], after))
		res.difference_update(self.deleted)
		return res

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
			corpus.search(self.payload)

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
