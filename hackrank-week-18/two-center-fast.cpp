#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>

using namespace std;

const int N = 5005;

int n;
vector<set<int>> graph;
vector<pair<int, int>> edges;
int d[N], curmax, curpt;

void dfs(const int& prev,
         const int& cur,
         const int& dep) {
  d[cur] = dep;
  if (d[cur] > curmax) {
    curmax = d[cur];
    curpt = cur;
  }
  for (auto &u : graph[cur]) {
    if (u == prev)
      continue;
    dfs(cur, u, dep + 1);
  }
}

int findRadius(const int& c) {
  // first pass
  curmax = -1;
  curpt = -1;
  dfs(-1, c, 0);

  // second pass
  int s = curpt;
  curmax = -1;
  curpt = -1;
  dfs(-1, s, 0);

  return curmax / 2 + (curmax % 2);
}

int findMaxRadius() {
  for (int i = 0; i <= n; ++i)
    d[i] = -1;

  int r1 = findRadius(1);
  for (int i = 1; i <= n; ++i) {
    if (d[i] == -1) {
      return max(r1, findRadius(i));
    }
  }
  return r1;
}


int main() {
  cin >> n;
  graph.resize(n + 1);
  
  int u, v;
  for (int i = 1; i < n; ++i) {
    cin >> u >> v;
    edges.push_back(make_pair(u, v));
    graph[u].insert(v);
    graph[v].insert(u);
  }

  int sol = n;
  for (int i = 0; i < edges.size(); ++i) {
    graph[edges[i].first].erase(edges[i].second);
    graph[edges[i].second].erase(edges[i].first);

    sol = min(sol, findMaxRadius());
    
    graph[edges[i].first].insert(edges[i].second);
    graph[edges[i].second].insert(edges[i].first);
  }
  cout << sol << endl;

  return 0;
}