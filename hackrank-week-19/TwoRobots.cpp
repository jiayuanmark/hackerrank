#include <cstdio>
#include <cstring>

using namespace std;

static const int INF = 2 * 1e6;
static const int N = 1005;
int table[N][N], copy[N][N];
int x[N], y[N];
int m, n;

inline int ABS(const int& x) {
  return x > 0 ? x : -x;
}

inline int MIN(const int& x, const int& y) {
  return x < y ? x : y;
}

void init() {
  int val = ABS(y[0] - x[0]);
  for (int i = 0; i <= m; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (i == y[0] || j == y[0]) {
        table[i][j] = val;
      } else {
        table[i][j] = INF;
      }
    }
  }
}

int sol() {
  int res = INF;
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= m; ++j) {
      res = MIN(res, table[i][j]);
    }
  }
  return res;
}

void transfer() {
  for (int i = 1; i <= m; ++i) {
    memcpy(table[i], copy[i], sizeof(copy[i]));
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d %d", &x[i], &y[i]);
    }

    init();
    for (int i = 1; i < n; ++i) {
      // dp
      int u = ABS(x[i] - y[i]);
      for (int j = 1; j <= m; ++j) {
        for (int k = 1; k <= m; ++k) {
          if (j == y[i]) {
            int v = INF;
            for (int l = 1; l <= m; ++l) {
              v = MIN(v, table[l][k] + ABS(l - x[i]) + u);
            }
            copy[j][k] = v;
          } else if (k == y[i]) {
            int v = INF;
            for (int l = 1; l <= m; ++l) {
              v = MIN(v, table[j][l] + ABS(l - x[i]) + u);
            }
            copy[j][k] = v;
          } else {
            copy[j][k] = INF;
          }
        }
      }
      transfer();
    }
    printf("%d\n", sol());
  }
  return 0;
}
