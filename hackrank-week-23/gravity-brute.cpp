#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

typedef long long LL;

static const int N = 100005;

// tree
int p[N];
vector<int> graph[N];

// query
int qu[N], qv[N], dep[N], lca[N];
vector<int> qry[N];

// union-find
int prt[N], rnk[N], ans[N];

void mset(int u) {
  prt[u] = u;
}

int find(int u) {
  if (prt[u] != u) {
    prt[u] = find(prt[u]);
  }
  return prt[u];
}

void merge(int u, int v) {
  int uroot = find(u);
  int vroot = find(v);
  if (rnk[uroot] > rnk[vroot]) {
    prt[vroot] = uroot;
  } else if (rnk[vroot] > rnk[uroot]) {
    prt[uroot] = vroot;
  } else if (uroot != vroot) {
    prt[vroot] = uroot;
    rnk[uroot] += 1;
  }
}

void init(const int& n) {
  for (int i = 1; i <= n; ++i) {
    dep[i] = -1;
  }
}

void dfs(int u, int p, int d) {
  mset(u);
  ans[u] = u;
  for (auto &v : graph[u]) {
    if (p == v) continue;
    dfs(v, u, d+1);
    merge(u, v);
    ans[find(u)] = u;
  }
  dep[u] = d;
  for (auto &ix : qry[u]) {
    if (qu[ix] == u && dep[qv[ix]] != -1) {
      lca[ix] = ans[find(qv[ix])];
    }
    if (qv[ix] == u && dep[qu[ix]] != -1) {
      lca[ix] = ans[find(qu[ix])];
    }
  }
}

// cache
LL sz[N], sum[N], sos[N];

void precompute(int u, int p) {
  sz[u] = 1;
  sum[u] = 0;
  sos[u] = 0;
  for (auto &v : graph[u]) {
    if (p == v) {
      continue;
    }
    precompute(v, u);
    sz[u] += sz[v];
    sum[u] += (sum[v] + sz[v]);
    sos[u] += (sos[v] + 2 * sum[v] + sz[v]);
  }
}

// query processing
LL query(int i) {
  int a = lca[i], u = qu[i], v = qv[i];
  //cout << u << " " << v << " " << a << endl; 
  if (a == u) {
    LL l = dep[v] - dep[a];
    return sos[v] + 2 * l * sum[v] + l * l * sz[v];
  } else if (a == v) {
    LL sol = 0L;
    int u1, u2;
    for (LL i = 0L, u1 = u; ; ++i, u1 = p[u1]) {
      if (i == 0L) {
        sol += sos[u];
      } else {
        sol += (i * i);
        for (auto &c : graph[u1]) {
          if (c == u2 || c == p[u1]) {
            continue;
          }
          sol += sos[c] + 2 * (i+1) * sum[c] + (i+1) * (i+1) * sz[c];
        }
      }
      if (u1 == v) {
        return sol;
      }
      u2 = u1;
    }
  } else {
    LL l = (dep[v] - dep[a]) + (dep[u] - dep[a]);
    return sos[v] + 2 * l * sum[v] + l * l * sz[v];
  }
}

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n-1; ++i) {
    cin >> p[i+1];
    graph[p[i+1]].push_back(i+1);
    graph[i+1].push_back(p[i+1]);
  }

  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    cin >> qu[i] >> qv[i];
    qry[qu[i]].push_back(i);
    qry[qv[i]].push_back(i);
  }

  init(n);
  dfs(1, -1, 0);
  precompute(1, -1);

  for (int i = 0; i < q; ++i) {
    cout << query(i) << endl;
  }
  return 0;
}
