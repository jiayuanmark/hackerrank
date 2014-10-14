#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef long long LL;

const int N = 100005;
const int K = 205;
const LL INF = 1e18;

vector<int> graph[N];
LL val[N], dp[N][K];
int ord[N], sz[N];
int cnt = 0;

void dfs(const int& u) {
	ord[++cnt] = u;
	sz[u] = 1;
	for (int i = 0; i < graph[u].size(); ++i) {
		int v = graph[u][i];
		if (sz[v]) continue;
		dfs(v);
	}
	sz[u] = cnt;
}

int main () {
	// input
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> val[i];
	}

	int src, dst;
	for (int i = 0; i < n-1; ++i) {
		cin >> src >> dst;
		graph[src].push_back(dst);
		graph[dst].push_back(src);
	}

	// dfs
	memset(ord, 0, sizeof(ord));
	memset(sz, 0, sizeof(sz));
	cnt = 0;
	dfs(1);

	// dynamic programming
	memset(dp, -INF, sizeof(dp));

	dp[n][0] = val[ord[n]];
	dp[n][1] = 0;
	for (int i = n-1; i >= 1; --i) {
		dp[i][0] = dp[i+1][0] + val[ord[i]];
		for (int j = 1; j <= k; ++j) {
			dp[i][j] = max(dp[i+1][j] + val[ord[i]], dp[sz[ord[i]]+1][j-1]);
		}
	}

	// output
	LL ans = dp[1][0];
	for (int i = 1; i <= k; ++i) {
		ans = max(dp[1][i], ans);
	}
	cout << ans << endl;

	return 0;
}
