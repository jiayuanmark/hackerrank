#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef long long LL;

LL dp[10005];
int n, acc[10005];

inline int diff(const int& i, const int& j) {
	return abs(acc[i-1] - acc[j-1]);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &acc[i]);
		if (acc[i] == 0) acc[i] = 10;
	}

	LL val;
	for (int i = 1; i <= n; ++i) {
		val = dp[0];
		for (int j = 1; j < i-1; ++j) {
			val = min(val, dp[j] + diff(i, j));
		}
		dp[i-1] = val;
		for (int j = 0; j < i-1; ++j) {
			dp[j] += diff(i, i-1);
		}
	}

	LL ans = dp[0];
	for (int i = 1; i < n; ++i) {
		ans = min(ans, dp[i]);
	}
	printf("%lld\n", (ans + (LL)n));

	return 0;
}