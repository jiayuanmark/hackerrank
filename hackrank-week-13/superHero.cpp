#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 2e9;

int n, m;
int p[105][500005];
int b[105][500005];
int dp[105][500005];

int solve() {
	for (int j = 0; j < m; ++j)
		dp[0][j] = p[0][j];

	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			for (int k = 0; k < m; ++k) {
				if (b[i-1][k] >= p[i][j])
					dp[i][j] = min(dp[i][j], dp[i-1][k]);
				else
					dp[i][j] = min(dp[i][j], dp[i-1][k] + p[i][j] - b[i-1][k]); 
			}
		}
	}

	int sol = INF;
	for (int j = 0; j < m; ++j) {
		sol = min(sol, dp[n-1][j]);
	}
	return sol;
}



int main() {
	int t;
	scanf("%d", &t);

	while (t--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				scanf("%d", &p[i][j]);
				dp[i][j] = INF;
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				scanf("%d", &b[i][j]);
			}
		}
		printf("%d\n", solve());
	}

	return 0;
}