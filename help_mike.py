

if __name__ == "__main__":
	T = int(raw_input())

	for t in range(T):
		item = raw_input().split()
		N, K = int(item[0]), int(item[1])

		mul = 2 * N / K

		ans = 0
		for item in xrange(1, mul+1):
			item = item * K
			upper = item / 2
			upper = upper - (1 if item % 2 == 0 else 0)
			lower = max(1, item - N)
			ans = ans + (upper - lower + 1)

		print ans
