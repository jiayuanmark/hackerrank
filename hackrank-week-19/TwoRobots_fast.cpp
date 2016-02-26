#include <cstdio>
#include <cstring>

using namespace std;

static const int INF = 2 * 1e6;
static const int N = 1005;
int dp[N];
int x[N], y[N];
int m, n;

inline int ABS(const int& x) {
  return x >= 0 ? x : -x;
}

inline int MIN(const int& x, const int& y) {
  return x <= y ? x : y;
}

inline int SCORE(const int& l, const int& r) {
  if (l == 0) {
    return ABS(x[r] - y[r]);
  }
  return ABS(y[l] - x[r]) + ABS(x[r] - y[r]);
}

int sol() {
  int res = INF;
  for (int i = 0; i < n; ++i) {
    res = MIN(res, dp[i]);
  }
  return res;
}

void debug(const int& p) {
  printf("Debug: %d -> %d\n", p-1, p);
  for (int i = 0; i < p; ++i) {
    printf("%d ", dp[i]);
  }
  printf("\n");
}

/*
 * score = | x[i] - y[i] |
 *
 * 1. when j = i-1
 * dp[i][j] = min {
 *              min { dp[i-1][k] + | y[k] - x[i] | } + score, where 1 <= k < i-1
 *              dp[i-1][0] + score }
 *
 * 2. when j = 0
 * dp[i][j] = dp[i-1][j] + | x[i] - y[i-1] | + score
 *
 * 3. when 1 <= j < i-1
 * dp[i][j] = dp[i-1][j] + | x[i] - y[i-1] | + score
 */
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d %d", &x[i], &y[i]);
    }

    // dp (zero-index indicate the first move)
    dp[0] = SCORE(0, 1);
    for (int i = 2; i <= n; ++i) {
      // use the left-most robot
      int v = INF;
      for (int j = 0; j < i-1; ++j) {
        v = MIN(v, dp[j] + SCORE(j, i));
      }
      dp[i-1] = v;
      // use the right-most robot
      for (int j = 0; j < i-1; ++j) {
        dp[j] += SCORE(i-1, i);
      }
      //debug(i);
    }
    printf("%d\n", sol());
  }
  return 0;
}
