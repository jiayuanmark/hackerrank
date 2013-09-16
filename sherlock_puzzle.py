import sys

if __name__ == "__main__":
	IN = raw_input().split()
	K, S = int(IN[0]), str(IN[1])

	stats, Num1= {-1:0}, 0
	for i in xrange(len(S)):
		if S[i] == "1":
			Num1 = Num1 + 1
		stats[i] = Num1

	Num0 = len(S) - Num1
	if 2 * Num0 <= 3 * Num1:
		print K * len(S)
		sys.exit(0)

	
	N = len(S) * K

	ans = 0
	for i in xrange(N):
		for j in xrange(max(i+1, i+ans-1), N):
			ones = Num1 * (j / len(S) - (i-1) / len(S)) + stats[j % len(S)] - stats[(i-1)% len(S)]
			if 2 * (j - i + 1) <= 5 * ones:
				ans = max(ans, j-i+1)
	print ans


