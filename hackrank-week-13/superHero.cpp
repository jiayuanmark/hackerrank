#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int INF = 5e5;

int n, m;
vector<int> p[100], b[100], dp[100];

vector<pair<int,int> > bvec;
vector<pair<int,int> > pvec;

int solve() {
	bvec.clear();
	for (int j = 0; j < m; ++j) {
		dp[0][j] = p[0][j];
		bvec.push_back(make_pair(b[0][j], dp[0][j]));
	}
	sort(bvec.begin(), bvec.end());

	for (int i = 1; i < n; ++i) {
		// sort (p[i][j], j)
		pvec.clear();
		for (int j = 0; j < m; ++j) {
			pvec.push_back(make_pair(p[i][j], j));
		}
		sort(pvec.begin(), pvec.end());

		int k = 0, diff = INF;
		for (int j = 0; j < m; ++j) { 
			while (k < m && bvec[k].first <= pvec[j].first) {
				diff = min(diff, bvec[k].second - bvec[k].first);
				++k;
			}
			dp[i][pvec[j].second] = min(dp[i][pvec[j].second], diff + pvec[j].first);
		}

		k = m-1, diff = INF;
		for (int j = m-1; j >= 0; --j) {
			while (k >= 0 && bvec[k].first >= pvec[j].first) {
				diff = min(diff, bvec[k].second);
				--k;
			}
			dp[i][pvec[j].second] = min(dp[i][pvec[j].second], diff);
		}

		// sort (b[i-1][j], dp[i-1][j])
		bvec.clear();
		for (int j = 0; j < m; ++j) {
			bvec.push_back(make_pair(b[i][j], dp[i][j]));
		}
		sort(bvec.begin(), bvec.end());
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
			p[i].clear();
			p[i].resize(m);
			dp[i].clear();
			dp[i].resize(m);
			for (int j = 0; j < m; ++j) {
				scanf("%d", &p[i][j]);
				dp[i][j] = INF;
			}
		}

		for (int i = 0; i < n; ++i) {
			b[i].clear();
			b[i].resize(m);
			for (int j = 0; j < m; ++j) {
				scanf("%d", &b[i][j]);
			}
		}
		printf("%d\n", solve());
	}

	return 0;
}