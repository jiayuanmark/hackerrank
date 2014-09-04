from collections import deque
import array, base64, zlib, re, hashlib, string, math, uuid
import cPickle as pickle
import nltk.stem as nltk

OFFLINE = True

################# Model ####################
def myhash(content, salt):
	return int(hashlib.md5(str(content)+str(salt)).hexdigest(), 16)

class bloomfilter:
	def __init__(self, m=500009, k=3):
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
	f = file("corpus.txt", "r")
	lines = f.readlines()
	return filter(lambda x : len(x) != 0, [ stem(token.lower()) for line in lines for token in line.split() ])

def getDict():
	f = file("dict.txt", "r")
	lines = f.readlines()
	return [ token.strip().lower() for token in lines ]

def getCharGram(tklist):
	pattern = re.compile('[\W_]+')
	hist = set()
	for token in set(tklist):
		token = pattern.sub('', token)
		# unigram
		for i in range(len(token)-1):
			hist.add(token[i:i+1])
		# bigram
		for i in range(len(token)-2):
			hist.add(token[i:i+2])
		# trigram
		for i in range(len(token)-3):
			hist.add(token[i:i+3])
		# quadgram
		for i in range(len(token)-4):
			hist.add(token[i:i+4])
	gram = bloomfilter()
	return gram.fromhistogram(hist)

def loadCharGram():
	bftr = bloomfilter()
	return bftr.fromstring(CHARGRAM)

stemmer = nltk.porter.PorterStemmer()

def stem(word):
	word = word.translate(None, string.digits+".,:?-_!()\"\'")
	return stemmer.stem(word)

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
def getCharScore(cand, chgram):
	word, pos = cand;
	score = 0
	# unigram
	for i in range(len(word)-1):
		if chgram[word[i:i+1]]:
			score += 1
	# bigram
	for i in range(len(word)-2):
		if chgram[word[i:i+2]]:
			score += 1
	# trigram
	for i in range(len(word)-3):
		if chgram[word[i:i+3]]:
			score += 1 
	# quadgram
	for i in range(len(word)-4):
		if chgram[word[i:i+4]]:
			score += 1
	print (word, score)
	return score

stoplist = [
'the', 'of', 'and', 'to', 'in', 'a', 'is', 'that', 'for', 'it', 'as', 'was', 'with',
'be', 'by', 'on', 'not', 'he', 'i', 'this', 'are', 'or', 'his', 'from', 'at', 'which',
'but', 'have', 'an', 'had', 'they', 'you', 'were', 'their', 'one', 'all', 'we', 'can',
'her', 'has', 'there', 'been', 'if', 'more', 'when', 'will', 'would', 'who', 'so', 'no']

def getMaxScore(cand, prev, chgram):
	print cand
	return max(cand, key=lambda x:getCharScore(x, chgram))[0]

def printDiffChar(origin, answer):
	print '\n'.join(map(lambda u:u[1], filter(lambda u:u[0] == '#', zip(origin, answer))))

############### Main Function ##################
if __name__ == "__main__":
	# load model
	if OFFLINE:
		corpus = getCorpus()
		gram = getCharGram(corpus)
	else:
		gram = loadCharGram()

	# read input
	snippet = raw_input()
	prev = None
	for token in snippet.split():
		token = token.lower()
		if "#" in token:
			token = stem(token)
			cand = getCandidate(token)
			ans = getMaxScore(cand, prev, gram)
			prev = ans
			print "%s  =>  %s" % (token, ans)
			printDiffChar(token, ans)
		else:
			prev = token