from itertools import permutations

if __name__ == "__main__":
	n = int(raw_input())
	
	task = []
	for _ in xrange(n):
		t, p = raw_input().split()
		task.append((int(t), float(p)))

	sol = float("Inf")
	for p in permutations(range(n)):
		stask = [ task[u] for u in p ]
		val = stask[0][0]
		for i in xrange(1, n):
			val = val * stask[i][1] + stask[i][0]
		sol = min(val, sol)
	print sol