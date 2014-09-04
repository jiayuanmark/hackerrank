from collections import deque
import array, base64, zlib, re, hashlib, string, math, uuid
import cPickle as pickle
import nltk.stem as nltk

OFFLINE = True

################# Model ####################
def myhash(content, salt):
	return int(hashlib.md5(str(content)+str(salt)).hexdigest(), 16)

class bloomfilter:
	def __init__(self, m=310019, k=2):
		self.m = m;
		self.k = k
		self.array = [False] * self.m
		self.salt = [
		'80cd5aa1-0620-40f3-941f-fe6ac1981ab7',
		'b9df4e35-c4d8-4697-a3df-3399faf1ac0d',
		'40ac135a-801b-4dbb-89e7-462e8898d068']

	def __getitem__(self, token):
		for i in xrange(self.k):
			idx = abs(myhash(token, self.salt[i])) % self.m
			if not self.array[idx]:
				return False
		return True

	def fromhistogram(self, histogram):
		for token in histogram:
			for i in xrange(self.k):
				idx = abs(myhash(token, self.salt[i])) % self.m
				self.array[idx] = True
		return self

	def fromstring(self, encodestr):
		bytes = array.array("B")
		bytes.fromstring(zlib.decompress(base64.decodestring(encodestr)))
		idx = 0
		for byte in bytes:
			for bit in range(0, 8):
				if (byte & (1 << bit)):
					self.array[bit+idx] = True
			idx += 8
		return self

	def tostring(self):
		bytes = array.array("B")
		num = 0
		for i in xrange(self.m):
			if self.array[i]:
				num |= (1 << (i % 8))
			if (i+1) % 8 == 0:
				bytes.append(num & 0xFF)
				num = 0
		if num != 0:
			bytes.append(num & 0xFF)
		return base64.encodestring(zlib.compress(bytes.tostring(), 9))


################ Algorithm ################
def getCorpus():
	f = file("large.txt", "r")
	lines = f.readlines()
	return filter(lambda x : len(x) != 0, [ stem(token.lower()) for line in lines for token in line.split() ])

def getDict():
	f = file("dict.txt", "r")
	lines = f.readlines()
	return [ token.strip().lower() for token in lines ]

def getUnigram(tklist):
	unigram = {}
	for token in tklist:
		unigram[token] = unigram.get(token, 0)+1
	print len(unigram)
	bftr = bloomfilter()
	return bftr.fromhistogram(unigram)

def loadUnigram():
	bftr = bloomfilter()
	return bftr.fromstring(UNIGRAM)

def getBigram(tklist):
	bigram = {}
	'''
	tkPairList = zip(tklist[:-1], tklist[1:])
	for tkPair in tkPairList:
		bigram[tkPair] = bigram.get(tkPair, 0)+1
	'''
	bftr = bloomfilter()
	return bftr.fromhistogram(bigram)

def loadBigram():
	return bloomfilter()

def getCharGram(tklist):
	pattern = re.compile('[\W_]+')
	gram = {}
	for token in set(tklist):
		if len(filter(lambda ch:ord(ch)>=128, token)) != 0:
			continue
		token = "^" + pattern.sub('', token) + "$"
		# unigram
		for ug in token:
			gram[ug] = gram.get(ug, 0) + 1
		# bigram
		for bg in zip(token[:-1], token[1:]):
			key = "".join(bg)
			gram[key] = gram.get(key, 0) + 1
	return gram

def loadCharGram():
	return pickle.loads(zlib.decompress(base64.decodestring(CHGRAM)))

stemmer = nltk.porter.PorterStemmer()

def stem(word):
	if word.endswith("\'s"):
		word = word[:-2]
	word = word.translate(None, string.digits + string.punctuation.translate(None, "#"))
	if word.endswith("ed"):
		return stemmer.stem(word)
	if word.endswith("ing"):
		return stemmer.stem(word)
	return word

def safelog(val):
	if val == 0.0:
		return float("-Inf")
	return math.log(float(val))

alphabet = 'abcdefghijklmnopqrstuvwxyz'

def getCandidate(token):
	cand, q = [], deque([(token, [])])
	while len(q) != 0:
		word, pos = q.popleft()
		idx = word.find("#")
		if idx == -1:
			cand.append((word, pos))
			continue
		pos.append(idx)
		for c in alphabet:
			nword = word[:idx] + c + word[idx+1:]
			q.append((nword, pos))
	return cand

# Laplace smoothing
def getCharScore(cand, gram):
	word, pos = cand;
	score, V = 0.0, len(filter(lambda x: len(x)==1, gram))
	for idx in pos:
		c = word[idx]
		if idx == 0:
			score += (safelog(gram.get("^"+c, 0) + 1) - safelog(gram["^"] + V))
		if idx > 0:
			score += (safelog(gram.get(word[idx-1]+c, 0) + 1) - safelog(gram.get(word[idx-1], 0) + V))
		if idx < len(word)-1:
			score += (safelog(gram.get(c+word[idx+1], 0) + 1) - safelog(gram.get(word[idx+1], 0) + V))
		if idx == len(word)-1:
			score += (safelog(gram.get(c+"$", 0) + 1) - safelog(gram["$"] + V))
	return score

stoplist = [
'the', 'of', 'and', 'to', 'in', 'a', 'is', 'that', 'for', 'it', 'as', 'was', 'with',
'be', 'by', 'on', 'not', 'he', 'i', 'this', 'are', 'or', 'his', 'from', 'at', 'which',
'but', 'have', 'an', 'had', 'they', 'you', 'were', 'their', 'one', 'all', 'we', 'can',
'her', 'has', 'there', 'been', 'if', 'more', 'when', 'will', 'would', 'who', 'so', 'no']

def getMaxScore(cand, prev, wugram, chgram):
	valid = filter(lambda x: wugram[x[0]], cand)
	for word, _ in valid:
		if word in stoplist:
			return word
	if len(valid) != 0:
		return max(valid, key=lambda x:getCharScore(x, chgram))[0]
	else:
		return max(cand, key=lambda x:getCharScore(x, chgram))[0]

def printDiffChar(origin, answer):
	print '\n'.join(map(lambda u:u[1], filter(lambda u:u[0] == '#', zip(origin, answer))))

############### Main Function ##################
if __name__ == "__main__":
	# load model
	if OFFLINE:
		corpus = getCorpus()
		unigram = getUnigram(corpus)
		chgram = getCharGram(corpus)
	else:
		unigram = loadUnigram()
		chgram = loadCharGram()

	# read input
	snippet = raw_input()
	prev = None
	for token in snippet.split():
		token = token.lower()
		if "#" in token:
			token = stem(token)
			cand = getCandidate(token)
			ans = getMaxScore(cand, prev, unigram, chgram)
			prev = ans
			print "%s  =>  %s" % (token, ans)
			printDiffChar(token, ans)
		else:
			prev = token