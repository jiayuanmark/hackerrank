from math import sqrt

def compute(n):
	return n * (n+1) * (2*n+1)/6

def search(lo, hi, x):
	while lo < hi:
		mid = lo + (hi - lo + 1) / 2
		sum = compute(mid)
		if sum == x:
			return mid
		if sum > x:
			hi = mid - 1
		else:
			lo = mid
	return lo

if __name__ == "__main__":
	t = int(raw_input())
	for _ in xrange(t):
		x = int(raw_input())
		print search(1, int(sqrt(x)), x)