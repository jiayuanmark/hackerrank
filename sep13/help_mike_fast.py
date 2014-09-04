
if __name__ == "__main__":
	T = int(raw_input())
	for t in xrange(T):
		line = raw_input().split()
		N, K = int(line[0]), int(line[1])
		gap1, gap2 = N / K, 2 * N / K
		ans = 0

		if K % 2 == 0:
			ans = ((1 + gap1) * gap1 / 2) * K / 2 - gap1
			ans = ans + N * (gap2 - gap1) - (gap1 + 1 + gap2) * (gap2 - gap1) / 2 * K / 2
		else:
			# First part
			even, odd = gap1 / 2, gap1 - gap1 / 2
			evenRear = gap1 if gap1 % 2 == 0 else gap1 - 1
			oddRear = gap1 if gap1 % 2 == 1 else gap1 - 1
			ans = ((2 + evenRear) * even / 2) * K / 2 + ((1 + oddRear) * odd / 2 * K + odd) / 2 - gap1
			ans = ans + N * (gap2 - gap1) - K * (1 + gap1 + gap2) * (gap2 - gap1) / 2
			
			# Second part
			even = (gap2 - gap1 + 1 - ((gap1+1) % 2)) / 2
			odd = gap2 - gap1 - even
			evenHead = gap1+1 if (gap1+1) % 2 == 0 else gap1+2
			oddHead = gap1+1 if (gap1+1) % 2 == 1 else gap1+2
			evenRear = gap2 if gap2 % 2 == 0 else gap2-1
			oddRear = gap2 if gap2 % 2 == 1 else gap2-1
			ans = ans + ((evenHead + evenRear)*even/2)*K/2 + ((oddHead+oddRear)*odd/2*K + odd)/2
			
		print ans