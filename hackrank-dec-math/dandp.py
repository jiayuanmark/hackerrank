from math import sqrt

def is_square(x):
	return x >= 0 and int(sqrt(x)) ** 2 == x

if __name__ == "__main__":
	t = int(raw_input())
	for _ in xrange(t):
		d, p = [ int(u) for u in raw_input().split() ]
		temp = d * d + 4 * p
		if d < 0 or not is_square(temp):
			print 0
		elif d == 0 and temp == 0:
			print 1
		elif d == 0 or temp == 0:
			print 2
		else:
			print 4


