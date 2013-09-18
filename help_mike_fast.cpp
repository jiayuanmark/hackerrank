#include <cstdio>

using namespace std;

inline int MMax(const int &num1, const int &num2) {
	return num1 > num2 ? num1 : num2;
}

int main() {
	long long T, N, K;
	scanf("%lld", &T);

	for (int t = 0; t < T; ++t) {
        scanf("%lld %lld", &N, &K);
        if (K % 2 == 0) {
        	long long gap1 = N/K, gap2 = N * 2 / K;
        	long long ans = ((1 + gap1) * gap1 / 2) * K / 2 - gap1;
        	ans = ans + N * (gap2 - gap1) - (gap1 + 1 + gap2) * (gap2 - gap1) / 2 * K / 2;
        	printf("%lld\n", ans);
        	continue;
        }

		long long mul = 2 * N / K, ans = 0;
        
		long long item, upper, lower;
		for (int i = 1; i <= mul; ++i) {
			item = i * K;
            upper = item / 2 - (item % 2 == 0 ? 1:0);
			lower = MMax(1, item - N);
			ans += (upper - lower + 1);
		}
		printf("%lld\n", ans);
	}

	return 0;
}
