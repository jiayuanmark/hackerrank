import sys
import array
import base64
import cPickle as pickle
import codecs
import zlib, re, os

from missingChar import bloomfilter, stem, getUnigram, getBigram, getCharGram, getCorpus, getDict

def to_gaps(arr):
	return [arr[0]] + map(lambda p : p[1] - p[0], zip(arr[:-1], arr[1:]))
  
def from_gaps(arr):
	sum = 0
	res = []
	for gap in arr:
		sum += gap
		res.append(sum)
	return res

def vb_encode_num(num):
	bytes = array.array("B")
	while num >= 0x80:
		bytes.append(num & 0x7F)
		num >>= 7
	bytes.append(num) 
	bytes[0] |= 0x80;
	bytes.reverse()
	return bytes
  
def vb_encode(arr):
	bytes = array.array("B")
	for num in arr:
		bytes.extend(vb_encode_num(num))
	return bytes
  
def vb_decode(bytes):
	arr = []
	sum = 0
	for byte in bytes:
		sum = (sum << 7) | (0x7F & byte);
		if byte & 0x80:
			arr.append(sum)
			sum = 0
	return arr

def compressCorpus(tklist):
	compressed = {}
	for i, v in enumerate(tklist):
		idxList = compressed.get(v, [])
		idxList.append(i)
		compressed[v] = idxList
	for k in compressed:
		compressed[k] = vb_encode(to_gaps(compressed[k])).tostring()
	return compressed

def decompressCorpus(compressed):
	for k in compressed:
		bytes = array.array("B")
		bytes.fromstring(compressed[k])
		compressed[k] = from_gaps(vb_decode(bytes.tolist()))
	lst = sorted([ (v, k) for k in compressed for v in compressed[k] ])
	return map(lambda x:x[1], lst)

def calculateModelSize(filenames):
	return sum(map(lambda fn: int(os.path.getsize(fn)), filenames))

if __name__ == "__main__":
	corpus = getCorpus()

	unigram = getUnigram(corpus)
	with open("unigram_model", "w") as f_out:
		f_out.write(unigram.tostring())

	backUnigram = bloomfilter()
	backUnigram.fromstring(unigram.tostring())

	count = 0
	for i in range(unigram.m):
		if unigram.array[i] != backUnigram.array[i]:
			print i
		if unigram.array[i]:
			count += 1

	print float(count) / unigram.m

	'''
	bigram = getBigram(corpus).tostring()
	with open("bigram_model", "w") as f_out:
		f_out.write(bigram)
	'''

	gram = getCharGram(corpus)
	with open("chgram_model", "w") as f_out:
		f_out.write(base64.encodestring(zlib.compress(pickle.dumps(gram, -1), 9)))

	print "Model size: %d bytes" % calculateModelSize(["unigram_model", "chgram_model"])
