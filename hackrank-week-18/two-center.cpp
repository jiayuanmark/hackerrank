#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 5001;

int d[N][N];
vector<int> graph[N];

void dfs(const int& src,
         const int& cur,
         const int& par,
         const int& dep) {
  for (auto &v : graph[cur]) {
    if (v == par)
      continue;
    d[src][v] = d[v][src] = dep + 1;
    dfs(src, v, cur, dep + 1);
  }
}

int main() {
  int n, u, v;
  cin >> n;
  for (int i = 1; i < n; ++i) {
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  for (int i = 1; i <= n; ++i) {
    dfs(i, i, -1, 0);
  }

  int sol = n * n;
  for (int i = 1; i <= n; ++i) {
    for (int j = i+1; j <= n; ++j) {
      int tmp = 0;    
      for (int k = 1; k <= n; ++k) {
        tmp = max(tmp, min(d[k][i], d[k][j]));
      }
      sol = min(tmp, sol);
    }
  }
  cout << sol << endl;

  return 0;
}