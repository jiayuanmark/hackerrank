#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

static const int MX = 100005;

int n, m;
vector<int> graph[MX];
bool visited[MX];

ll dfs(int u) {
  visited[u] = true;
  ll res = 1ll;
  for (auto &v : graph[u]) {
    if (!visited[v])  {
      res += dfs(v);
    }
  }
  return res;
}

inline ll compute(const ll& x) {
  return x * (x - 1) * (x + 1) / 3;
}

ll solve() {
  for (int i = 1; i <= n; ++i) {
    visited[i] = false;
  }

  vector<ll> cs;
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      cs.push_back(dfs(i));
    }
  }

  sort(cs.rbegin(), cs.rend());
  
  ll sol = 0ll, acc = 0ll, e = m;
  for (auto &c : cs) {
    sol += compute(c);
    sol += acc * (c - 1);
    acc += c * (c - 1);
    e -= (c - 1);
  }
  return sol + e * acc;
}

int main() {
  int q, x, y;
  cin >> q;
  while (q--) {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
      graph[i].clear();
    }
    for (int i = 0; i < m; ++i) {
      cin >> x >> y;
      graph[x].push_back(y);
      graph[y].push_back(x);
    }
    cout << solve() << endl;
  }
  return 0;
}