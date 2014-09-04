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


	L = len(S)
	
	# Search for prefix
	Prefix, Suffix = 0, 0
	for i in xrange(2*L-1, -1, -1):
		if 2 * (i+1) <= 5 * (i/L * Num1 + stats[i%L]):
			Prefix = i+1
			break

	# Search for suffix
	for i in xrange(2*L):
		if 2 * (2*L-i) <= 5 * (2*Num1-(i-1)/L*Num1 -stats[(i-1)%L]):
			Suffix = 2*L-i
			break

	print max(Prefix, Suffix)

	



