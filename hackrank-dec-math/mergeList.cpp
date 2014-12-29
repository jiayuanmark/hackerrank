#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;

LL dp[210];
const LL MOD = (1e9 + 7);

LL solve(const int& m, const int& n) {
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for (int i = 1; i <= m; ++i) {
		for (int j = n; j >= 1; --j) {
			dp[j] = (dp[j] + dp[j-1]) % MOD;
		}
	}
	return dp[n];
}

int main() {
	int t; cin >> t;
	int n, m;
	while (t--) {
		cin >> n >> m;
		cout << solve(m+n, m<n?m:n) << endl;
	}
	return 0;
}