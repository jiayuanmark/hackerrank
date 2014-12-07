#include <iostream>
#include <cstdio>

using namespace std;

typedef long long LL;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		LL n, ones = 0L, twos = 0L;
		scanf("%lld", &n);
		int temp;
		for (LL i = 0; i < n; ++i) {
			scanf("%d", &temp);
			if (temp == 1) {
				++ones;
			}
			if (temp == 2) {
				++twos;
			}
		}
		LL sol = ones * (ones-1) + ones * (n-ones);
		sol += (twos-1) * twos / 2;
		printf("%lld\n", sol);
	}
	return 0;
}
