import json, sys, string
from nltk.corpus import stopwords
from math import log, log10

STOP = set(stopwords.words("english"))
TABLE = dict((ord(char), None) for char in string.punctuation)
Label = ["gis", "security", "photo", "mathematica", "unix", "wordpress", "scifi", "electronics", "android", "apple"]

def tokenizer(S):
	return [ w for w in S.translate(TABLE).lower().split() if w not in STOP ]

def score_func(text, model, idf):
	return sum([ float(1 + log(model[w])) * float(idf[w]) for w in text if w in model])

if __name__ == "__main__":
	Model, IDF = {}, {}
	N = float(open("training.json", "r").readline())
	for line in open("training.json", "r").readlines()[1:]:
		item = json.loads(line)

		S = Model.setdefault(item["topic"], {})
		Question = tokenizer(item["question"])
		Excerpt = tokenizer(item["excerpt"])
		
		for w in (Question + Excerpt):
			S[w] = S.setdefault(w, 0) + 1
		Model[item["topic"]] = S

		for w in set(Question+Excerpt):
			IDF[w] = IDF.setdefault(w, 0) + 1

	for w in IDF:
		IDF[w] = log10(N / IDF[w])

	T = int(raw_input())
	for t in range(T):
		record = json.loads(raw_input())
		text = tokenizer(record["question"]) + tokenizer(record["excerpt"])

		score = {}
		for key in Label:
			score[key] = score_func(text, Model[key], IDF)
		print sorted(score.keys(), key=lambda x:score[x], reverse=True)[0]



	
