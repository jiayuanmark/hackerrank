from math import sqrt, ceil

def extendGCD(r1, r2, s1, s2, t1, t2):
	if r2 == 0:
		return r1, s1, t1
	q = r1 / r2
	return extendGCD(r2, r1 % r2, s2, s1 - q * s2, t2, t1 - q * t2)

def modInv(a, mod):
	_, _, inv = extendGCD(mod, a, 1, 0, 0, 1)
	return inv if inv >= 0 else inv + mod

def modExp(a, b, mod):
	res, mu = 1, a 
	while b != 0:
		if b % 2 == 1:
			res = (res * mu) % mod
		mu = (mu ** 2) % mod
		b /= 2
	return res

def solve(a, b, g):
	n, val = int(ceil(sqrt(g))), {}

	val[1] = [0]
	lhs = mu = modExp(a, n, g)
	for i in xrange(1, n+1):
		val.setdefault(lhs, []).append(i)
		lhs = (lhs * mu) % g

	rhs, sol = a, g
	for j in xrange(1, n+1):
		inv = (b * modInv(rhs, g)) % g
		if inv in val:
			sol = min(sol, min(val[inv]) * n + j)
		rhs = (rhs * a) % g

	return sol if sol != g else -1


if __name__ == "__main__":
	for _ in xrange(int(raw_input())):
		a, b, g = map(int, raw_input().split())
		print solve(a, b, g)