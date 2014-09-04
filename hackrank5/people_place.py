# Enter your code here. Read input from STDIN. Print output to STDOUT

win = 5;
prop = set(["in", "of", "at"])
verb = set(["had", "has", "is", "was"])

def clean(corpus):
    sentences = corpus.strip().split(".")
    return filter(lambda x : len(x) != 0, [s.strip().split() for s in sentences ])

def feature(window, word):
	#print window
	ppl, plc = 0, 0
	flag = False
	for w in window:
		w = w.replace(',', '').strip()
		if w.find(word) != -1:
			flag = True
			if w.endswith("'s"):
				ppl = ppl + 2
			if w.startswith("\"") and w.endswith("\""):
				ppl = ppl + 1
		if not flag and w.isdigit():
			ppl = ppl + 1
		if flag and w.isdigit():
			plc = plc + 1
		if w in prop:
			plc = plc + 1
		if w in verb:
			ppl = ppl + 1
		if w.endswith("ed"):
			ppl = ppl + 1
	return ppl, plc

def classify(sentences, word):
	people, place = 0, 0
	for s in sentences:
		for idx in range(len(s)):
			if s[idx].find(word) != -1:
				p1, p2 = feature(s[max(0, idx-win):min(idx+win, len(s))], word)
				people = people + p1
				place = place + p2

	#print word, people, place
	return people > place



if __name__ == "__main__":
	sentences = clean(raw_input())
	T = int(raw_input())
	for i in range(T):
		if classify(sentences, raw_input().strip()):
			print "person"
		else:
			print "place"