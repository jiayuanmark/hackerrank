import numpy as np
import hashlib

class Model:
	def __init__(self):
		self.row = 20000
		self.col = 200
		self.mat = [[0.0 for _ in range(self.col)] for x in range(self.row) ] 
		self.mvec = [0.0 for _ in range(self.col) ]

	def hash(self, payload):
		return int(hashlib.md5(payload).hexdigest(), 16) % self.row

	def update(self, doc, topic):
		for w in doc:
			for t in topic:
				self.mat[self.hash(w)][t % self.col] += 1. / len(doc)

	def train(self):
		for i in xrange(self.col):
			self.mvec[i] = np.mean([ self.mat[r][i] for r in xrange(self.row) ])

	def predict(self, doc):
		topic = [0.0 for _ in range(self.col) ]
		for w in doc:
			row = self.mat[self.hash(w)]
			for i, c in enumerate(row):
				topic[i] += c
		for i in xrange(self.col):
			topic[i] = topic[i] / len(doc) - self.mvec[i]
		return sorted(range(self.col), key=lambda x:topic[x], reverse=True)[:10]

def parser(content):
	word = [ u.lower() for u in content.split() ]
	if word[-1].endswith('?'):
		word[-1] = word[-1][:-1]
	return word

if __name__ == "__main__":
	t, e = [ int(u) for u in raw_input().split() ]

	model = Model()
	for _ in xrange(t):
		topics = raw_input()
		content = raw_input()
		model.update(parser(content), [ int(u) for u in topics.split()[1:] ])

	model.train()

	for _ in xrange(e):
		question = raw_input()
		pred = model.predict(parser(question))
		print " ".join([ str(u) for u in pred ])