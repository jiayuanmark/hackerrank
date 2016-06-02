#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

static const int INF = (1 << 30);
static const int N = 2005;
static const int K = 1050;

int n, m, k, t, a;
int fish[N], dist[N][K];
vector<pair<int,int> > graph[N];

struct node_t {
  int u, cost, item;
  node_t(int uu, int cc, int ii) 
    : u(uu), cost(cc), item(ii) {}
};

int main() {
  memset(fish, 0, sizeof(fish));
  
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < K; ++j) {
      dist[i][j] = INF;
    }
  }

  // input
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &t);
    for (int j = 0; j < t; ++j) {
      scanf("%d", &a);
      fish[i] |= (1 << (a-1));
    }
  }
  int u, v, w;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    graph[u].push_back(make_pair(v, w));
    graph[v].push_back(make_pair(u, w));
  }

  // solve
  queue<node_t> Q;
  Q.push(node_t(1, 0, fish[1]));
  while (!Q.empty()) {
    node_t cur = Q.front();
    Q.pop();
    //printf("%d %d\n", cur.u, cur.cost);
    for (auto &e : graph[cur.u]) {
      node_t nxt(e.first,
        cur.cost + e.second, cur.item | fish[e.first]);
      // printf("(%d,%d) %d<>%d\n", nxt.u, nxt.item, nxt.cost, dist[nxt.u][nxt.item]);
      if (nxt.cost < dist[nxt.u][nxt.item]) {
        dist[nxt.u][nxt.item] = nxt.cost;
        Q.push(nxt);
      }
    }
  }

  int msk = (1 << k) - 1;
  int sol = dist[n][msk];
  for (int i = 1; i < msk; ++i) {
    for (int j = 1; j < msk; ++j) {
      if ((i | j) == msk) {
        sol = min(max(dist[n][i], dist[n][j]), sol);
      }
    }
  }
  printf("%d\n", sol);

  return 0;
}