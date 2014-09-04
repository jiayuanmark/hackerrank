import json, sys, string
#from nltk.corpus import stopwords
from sklearn import linear_model
import numpy as np

STOP = set(['i', 'me', 'my', 'myself', 'we', 'our', 'ours', 'ourselves', 'you', 'your', 'yours', 'yourself', 'yourselves', 'he', 'him', 'his', 'himself', 'she', 'her', 'hers', 'herself', 'it', 'its', 'itself', 'they', 'them', 'their', 'theirs', 'themselves', 'what', 'which', 'who', 'whom', 'this', 'that', 'these', 'those', 'am', 'is', 'are', 'was', 'were', 'be', 'been', 'being', 'have', 'has', 'had', 'having', 'do', 'does', 'did', 'doing', 'a', 'an', 'the', 'and', 'but', 'if', 'or', 'because', 'as', 'until', 'while', 'of', 'at', 'by', 'for', 'with', 'about', 'against', 'between', 'into', 'through', 'during', 'before', 'after', 'above', 'below', 'to', 'from', 'up', 'down', 'in', 'out', 'on', 'off', 'over', 'under', 'again', 'further', 'then', 'once', 'here', 'there', 'when', 'where', 'why', 'how', 'all', 'any', 'both', 'each', 'few', 'more', 'most', 'other', 'some', 'such', 'no', 'nor', 'not', 'only', 'own', 'same', 'so', 'than', 'too', 'very', 's', 't', 'can', 'will', 'just', 'don', 'should', 'now'])

TABLE = dict((ord(char), None) for char in string.punctuation)

Label = ["gis", "security", "photo", "mathematica", "unix", "wordpress", "scifi", "electronics", "android", "apple"]
Label2Num = dict([ (Label[idx], idx+1) for idx in range(10) ])
Num2Label = dict([ (idx+1, Label[idx]) for idx in range(10) ])


def tokenizer(S):
	return [ w for w in S.translate(TABLE).lower().split() if w not in STOP ]

def get_features(Text, Dict):
	return [ Text.count(w) for w in Dict ]

def ReadTrainData(FileName):
	Y, X, DICT = [], [], {}
	for line in open(FileName, "r").readlines()[1:]:
		item = json.loads(line)
		Y.append(Label2Num[item["topic"]])
		question_token = tokenizer(item["question"])
		excerpt_token = tokenizer(item["excerpt"])
		X.append({"question":question_token, "excerpt":excerpt_token})
		for w in question_token + excerpt_token:
			DICT[w] = DICT.setdefault(w, 0) + 1
	return Y, X, DICT

def Featurizer(X, D):
	F = []
	for item in X:
		F.append(get_features(item["question"], D) + get_features(item["excerpt"], D))
	return F


if __name__ == "__main__":
	Y, X, DICT = ReadTrainData("training.json")
	DICT = dict(sorted(DICT.iteritems(), key=lambda x : DICT[x[0]], reverse=True)[:2500])
	X = Featurizer(X, DICT)

	clf = linear_model.LogisticRegression(penalty="l1", C=15.0)
	clf.fit(X, Y)

	T = int(raw_input())
	for t in range(T):
		record = json.loads(raw_input())
		feature = get_features(tokenizer(record["question"]), DICT) + get_features(tokenizer(record["excerpt"]), DICT)
		print Num2Label[clf.predict(feature)]


	