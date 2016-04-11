import array, base64, zlib, re, hashlib, string, math, uuid
import cPickle as pickle

def tokenize(f):
  lines = f.readlines()
  tokens = []
  for line in lines:
    tokens.extend(string.translate(line.strip(), None, ".,!?:\";").lower().split())
  return tokens

def create_list():
  s = set([])
  with open("noun.txt", "r") as f_in:
    s.update(tokenize(f_in))
  #with open("frankenstein.txt", "r") as f_in:
  #  s.update(tokenize(f_in))
  with open("google-20000-english-usa.txt", "r") as f_in:
    s.update(tokenize(f_in))
  print len(s)
  serialized = base64.encodestring(zlib.compress(pickle.dumps(s, -1), 9))
  with open("unigram.txt", "w") as f_out:
    f_out.write(serialized)

if __name__ == "__main__":
  create_list()