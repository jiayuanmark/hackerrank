import array, base64, zlib, re, hashlib, string, math, uuid
import cPickle as pickle
import sys

unigram_model='''
<unigram label>
'''

whitelist = set([ "that", "who", "which", "of", "to", "in", "on" ])

rule1 = set([ "theyve", "Theyve", "theyre", "Theyre", "weve", "We've",
              "Ive", "Were", "youve", "Youve", "youre", "Youre" ])
rule2 = set([ "hed", "shed", "Id", "wont", "Wont", "Hed", "Shed",
              "theyd", "Theyd"])

def load_unigram():
  return pickle.loads(zlib.decompress(base64.decodestring(unigram_model)))

def remove_sym(w):
  return string.translate(w, None, ".,!?:\";")

def solve(model, words):
  n = len(words)
  for (i, w) in enumerate(words):
    if i == n-1:
      sys.stdout.write(w + "\n")
    elif (w[-1] == 's' and len(w) > 2 and
          w[:-1].lower() in model and
          w.lower() not in model and
          words[i+1].lower() not in whitelist) :
      sys.stdout.write(w[:-1] + "'s ")
    elif remove_sym(w) in rule1:
      sys.stdout.write(w[:-2] + "'" + w[-2:] + " ")
    elif remove_sym(w) in rule2:
      sys.stdout.write(w[:-1] + "'" + w[-1:] + " ")
    elif w == 'oclock':
      sys.stdout.write("o'clock ")
    else:
      sys.stdout.write(w + " ")

if __name__ == "__main__":
  model = load_unigram()

  for content in sys.stdin:
    content = content.strip()
    if len(content) == 0:
      break
    words = content.split()
    solve(model, words)
