import array, base64, zlib, re, hashlib, string, math, uuid
import cPickle as pickle

unigram_model = '''
<unigram label>
'''

bigram_model = '''
<bigram label>
'''

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

def load_bigram():
  fltr = BloomFilter(m=3000017, k=3)
  fltr.fromstring(bigram_model)
  return fltr

def load_unigram():
  fltr = BloomFilter(m=2000003)
  fltr.fromstring(unigram_model)
  return fltr
  #return pickle.loads(zlib.decompress(base64.decodestring(unigram_model)))

def gen_candidate(table, s):
  if s.lower() in table:
    yield [s]
  for i in range(len(s)):
    head, tail = s[:i], s[i:]
    if head.lower() not in table:
      continue
    for rst in gen_candidate(table, tail):
      yield [head] + rst

def get_max_candidate(bigram, cand_gen):
  def point(t):
    (a, b) = t
    return (a.lower() + " " + b.lower()) in bigram
  
  def score(sq):
    return len(filter(lambda x : point(x), zip(sq, sq[1:])))

  candidates = []
  for cand in cand_gen:
    candidates.append(cand)
  return max(candidates, key=lambda x : (score(x) - len(x)))

if __name__ == "__main__":
  n = int(raw_input())
  unigram = load_unigram()
  bigram = load_bigram()
  for _ in xrange(n):
    raw = raw_input().strip()
    print " ".join(get_max_candidate(bigram, gen_candidate(unigram, raw)))
