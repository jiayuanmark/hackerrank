#include <algorithm>
#include <cstdio>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int n, m;
set<pair<int, int> > s;

inline void add(int u, int v) {
  s.insert(
    make_pair(min(u, v), max(u,v)));
}

inline bool adj(int u, int v) {
  return s.count(
    make_pair(min(u, v), max(u,v))) != 0;
}

int main() {
  scanf("%d%d", &n, &m);
  vector<pair<int, int> > edges(m);
  int x, y;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &x, &y);
    edges[i].first = min(x, y);
    edges[i].second = max(x, y);
    add(x, y);
  }

  sort(edges.begin(), edges.end());

  int count = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j < m; ++j) {
      if (edges[i].first != edges[j].first) {
          
          if (edges[i].second < edges[j].second &&
              adj(edges[i].second, edges[j].first) &&
              adj(edges[j].second, edges[i].first)) {
            /*printf("1: %d -> %d -> %d -> %d -> %d\n",
              edges[i].first, edges[i].second,
              edges[j].first, edges[j].second,
              edges[i].first);*/
            ++count;
          }

          if (edges[i].second < edges[j].first &&
              adj(edges[i].second, edges[j].second) &&
              adj(edges[j].first, edges[i].first)) {
            /*printf("2: %d -> %d -> %d -> %d -> %d\n",
              edges[i].first, edges[i].second,
              edges[j].second, edges[j].first,
              edges[i].first);*/
            ++count;
          }
      }
    }
  }
  printf("%d\n", count);
  return 0;
}
