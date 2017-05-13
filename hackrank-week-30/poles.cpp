#include <iostream>

using namespace std;

typedef long long LL;

static const int MX = 5005;
static const LL INF = (1L << 62L);

int N, K;
LL w[MX], x[MX], dp[MX][MX];

inline LL Min(const LL& v1, const LL& v2) {
  return v1 < v2 ? v1 : v2;
}

int main() {
  cin >> N >> K;
  for (int i = 0; i < N; ++i) {
    cin >> x[i] >> w[i];
  }

  K -= 1;
  for (int i = 1; i < N; ++i) {
    // choose i, k -> k+1
    for (int j = 0; j < K-1; ++j) {
      dp[j+1][i] = INF;
      for (int k = 0; k < i; ++k) {
        dp[j+1][i] = Min(dp[j+1][i], dp[j][k]);
      }
    }

    // not choose i
    for (int j = 0; j < K; ++j) {
      for (int k = 0; k < i; ++k) {
        dp[j][k] += w[i] * (x[i] - w[k]);
      }
    }
  }

  LL sol = INF;
  for (int i = 0; i < N; ++i) {
    sol = min(sol, dp[K-1][i]);
  }
  cout << sol << endl;

  return 0;
}