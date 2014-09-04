

ans = ""

def search(num, t, k):
	global ans
	if len(num) > k or len(ans) != 0:
		return
	if int(num) % t == 0:
		ans = num
		return
	search(num+'0', t, k)
	search(num+'9', t, k)

def solve(t):
	global ans
	ans = ""
	depth = 1
	while len(ans) == 0:
		search("9", t, depth)
		depth = depth + 1
	return ans

if __name__ == "__main__":
	T = int(raw_input())
	for t in range(T):
		print solve(int(raw_input()))