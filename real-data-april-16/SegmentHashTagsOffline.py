import array, base64, zlib, re, hashlib, string, math, uuid
import cPickle as pickle

def hashfunc(content, salt):
  return int(hashlib.sha256(str(content) + str(salt)).hexdigest(), 16)

class BloomFilter:
  def __init__(self, m=1500007, k=2, f=hashfunc):
    self.m = m;
    self.k = k
    self.array = [False] * self.m
    self.salt = ['13', '17', '19']
    self.hash = f;

  def __contains__(self, token):
    for i in xrange(self.k):
      idx = abs(self.hash(token, self.salt[i])) % self.m
      if not self.array[idx]:
        return False
    return True

  def fromlist(self, l):
    for token in l:
      for i in xrange(self.k):
        idx = abs(self.hash(token, self.salt[i])) % self.m
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

def tokenize(f):
  lines = f.readlines()
  tokens = []
  for line in lines:
    tokens.extend(string.translate(line, None, ".,!?:\";").lower().split())
  return tokens

def create_bloom_filter():
  with open("lincoln.txt") as f_in:
    fltr = BloomFilter(m=3000017, k=3)
    tokens = tokenize(f_in)
    fltr.fromlist([ w1 + " " + w2 for (w1, w2) in zip(tokens, tokens[1:]) ])
    with open("bigram.txt", "w") as f_out:
      f_out.write(fltr.tostring())

def create_list():
  with open("google-20000-english-usa.txt") as f_in:
    fltr = BloomFilter(m=2000003)
    fltr.fromlist(tokenize(f_in))
    #serialized = base64.encodestring(zlib.compress(pickle.dumps(s, -1), 9))
    with open("unigram.txt", "w") as f_out:
      f_out.write(fltr.tostring())

if __name__ == "__main__":
  create_list()
  create_bloom_filter()