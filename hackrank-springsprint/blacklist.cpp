#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int INF = 200000;

int n, k;
int cost[50][50];
int dp[4000][50];

int solve(const int& mask, const int& e) {
	if (dp[mask][e] != -1)
		return dp[mask][e];

	if (e == 0) {
		dp[mask][e] = 0;
		return dp[mask][e];
	}

	if (mask == 0) {
		dp[mask][e] = INF;
		return dp[mask][e];
	}

	int val = INF;
	for (int i = 1; i <= k; ++i) {
		if (!((mask >> (i-1)) & 1))
			continue;
		int sub = mask ^ (1 << (i-1));
		for (int j = 1; j <= e; ++j) {
			val = min(val, solve(sub, j-1) + cost[i][e] - cost[i][j-1]);
		}
	}
	dp[mask][e] = val;
	return dp[mask][e];
}

int main() {
	cin >> n >> k;

	for (int i = 1; i <= k; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> cost[i][j];
			cost[i][j] += cost[i][j-1];
		}
	}

	// initialization
	int s = 1 << k;
	for (int i = 0 ; i < s; ++i) {
		for (int j = 0; j <= n; ++j) {
			dp[i][j] = -1;
		}
	}

	// dynamic programming
	int sol = INF;
	for (int i = 0; i < s; ++i) {
		sol = min(sol, solve(i, n));
	}
	cout << sol << endl;

	return 0;
}