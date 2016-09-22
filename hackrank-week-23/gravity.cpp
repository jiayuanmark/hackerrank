#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

typedef long long LL;

static const int N = 100005;

LL sz[N], sum[N], sos[N];
vector<int> graph[N];
int p[N];

void dfs(int x, int p) {
  sz[x] = 1;
  sum[x] = 0;
  sos[x] = 0;
  for (auto &y : graph[x]) {
    if (y == p) {
      continue;
    }
    dfs(y, x);
    sz[x] += sz[y];
    sum[x] += (sum[y] + sz[y]);
    sos[x] += (sos[y] + 2 * sum[y] + sz[y]);
  }
}

LL query(int u, int v) {
  map<int, LL> cost;
  
  // backtrace from v
  int v_pt;
  for (LL i = 0L, v_pt = v; v_pt != 0; ++i, v_pt = p[v_pt]) {
    // v is child of u
    if (v_pt == u) {
      return sos[v] + i * ((sum[v] << 1L) + i * sz[v]);
    }
    cost[v_pt] = i;
  }

  // backtrace from u
  int u1, u2;
  LL sol = 0L;
  for (LL i = 0L, u1 = u; u1 != 0; ++i, u1 = p[u1]) {
    if (i == 0L) {
      sol += sos[u];
    } else {
      sol += (i * i);
      for (auto &chd : graph[u1]) {
        if (chd == u2 || chd == p[u1]) {
          continue;
        }
        sol += sos[chd] + 2 * (i+1) * sum[chd] + (i+1) * (i+1) * sz[chd];
      }
    }

    // u is child of v
    if (u1 == v) {
      return sol;
    }

    // u and v in different branches
    if (cost.count(u1) != 0) {
      LL j = i + cost[u1];
      return sos[v] + 2 * j * sum[v] + j * j * sz[v];
    }
    u2 = u1;
  }
  return 0;
}

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n-1; ++i) {
    cin >> p[i+1];
    graph[p[i+1]].push_back(i+1);
    graph[i+1].push_back(p[i+1]);
  }

  dfs(1, -1);

  int q, u, v;
  cin >> q;
  while (q--) {
    cin >> u >> v;
    cout << query(u, v) << endl;
  }
  return 0;
}
