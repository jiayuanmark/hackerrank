#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>

using namespace std;

static const int N = 100005;

typedef long long LL;

int n, m;
int par[N], sz[N];

vector<pair<int, int> > G[N];
int treeSize[N];
LL soln[200005];
set<LL> bitPos;

void init() {
	for (int i = 1; i <= n; ++i) {
		par[i] = i;
		sz[i] = 1;
	}
}

int find(int x) {
	if (par[x] == x)
		return x;
	return find(par[x]);
}

void merge(int x, int y) {
	int r1 = find(x);
	int r2 = find(y);

	if (r1 == r2)
		return;
	if (sz[r1] >= sz[r2]) {
		sz[r1] += sz[r2];
		par[r2] = r1;
	} else {
		sz[r2] += sz[r1];
		par[r1] = r2;
	}
}

int dfs_size(int p, int u) {
	treeSize[u] = 1;
	for (auto &edg : G[u]) {
		if (edg.first == p) {
			continue;
		}
		treeSize[u] += dfs_size(u, edg.first);
	}
	return treeSize[u];
}

void dfs(int p, int u, int acc) {
	int rst = treeSize[u] + acc;
	for (auto &edg : G[u]) {
		if (edg.first == p) {
			continue;
		}
		soln[edg.second] = LL(treeSize[edg.first]) * LL(rst - treeSize[edg.first]);
		dfs(u, edg.first, rst - treeSize[edg.first]);
	}
}


int main() {
	cin >> n >> m;
	init();

	vector<pair<int, pair<int, int> > > edges(m);
	int u, v, w;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		edges[i] = make_pair(w, make_pair(u, v));
	}
	sort(edges.begin(), edges.end());

	for (int i = 0; i < m; ++i) {
		u = edges[i].second.first;
		v = edges[i].second.second;
		w = edges[i].first;

		int r1 = find(u);
		int r2 = find(v);
		if (r1 == r2) {
			continue;
		}
		merge(r1, r2);

		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
	}

	dfs_size(-1, 1);
	dfs(-1, 1, 0);
	
	for (int i = 0; i < m; ++i) {
		if (soln[i] % 2) {
			bitPos.insert(i);
		}
		soln[i+1] += (soln[i] / 2);
	}

	LL pos = m;
	while (soln[m]) {
		if (soln[m] % 2) {
			bitPos.insert(pos);
		}
		soln[m] /= 2;
		++pos;
	}

	LL limit = *bitPos.rbegin();
	for (LL i = 0; i <= limit; ++i) {
		if (bitPos.count(limit - i)) {
			cout << 1;
		} else {
			cout << 0;
		}
	}
	cout << endl;

	return 0;	
}
