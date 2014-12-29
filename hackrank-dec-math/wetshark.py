
MOD = (10 ** 9) + 7

def solve(strength):
	base = strength * 2
	slot = base / 42
	while True:
		temp = (slot * 2 + base) / 42
		if temp == slot:
			break
		slot = temp
	return (base + slot * 2) % MOD

if __name__ == "__main__":
	t = int(raw_input())
	for _ in xrange(t):
		print solve(int(raw_input()))