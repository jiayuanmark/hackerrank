#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef long long LL;

static const int MAX_N = 100005;

int n, m, q;
unordered_set<int> graph[MAX_N], path[MAX_N];
LL a[MAX_N];

void dfs(const int& u) {
  if (!path[u].empty()) {
    return;
  }
  path[u].insert(u);
  for (auto &v : graph[u]) {
    dfs(v);
    path[u].insert(path[v].begin(), path[v].end());
  }
}

void update1(const int& u, const int& x) {
  for (auto &v : path[u]) {
    a[v] = x;
  }
}

void update2(const int& u, const int& x) {
  for (auto &v : path[u]) {
    if (a[v] > x) {
      a[v] = x;
    }
  }
}

int main() {
  cin >> n >> m >> q;
  int u, v;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v;
    graph[u].insert(v);
  }

  for (int i = 1; i <= n; ++i) {
    dfs(i);
  }

  int qtp, x;
  while (q--) {
    cin >> qtp;
    if (qtp == 1) {
      cin >> u >> x;
      update1(u, x);
    } else if (qtp == 2) {
      cin >> u >> x;
      update2(u, x);
    } else {
      cin >> u;
      cout << a[u] << endl;
    }
  }
  return 0;
}