#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

string s;
int n;

static const ll M = 1000000007ll;

ll dp[200005][8];

ll inc(ll& v, const ll& d) {
  v = (v + d) % M;
  return v;
}

ll solve() {
  /*
  for (int i = 0; i < n; ++i) {
    int x = s[i] - '0';
    inc(dp[i][x % 8], 1ll);
    for (int j = 0; j < i; ++j) {
      for (int k = 0; k < 8; ++k) {
        inc(dp[i][(10 * k + x) % 8], dp[j][k]);
      }
    }
  }

  ll sol = 0ll;
  for (int i = 0; i < n; ++i) {
    inc(sol, dp[i][0]);
  }
  return sol;
  */
  inc(dp[0][0], 1ll);
  inc(dp[0][ (s[0] - '0') % 8 ], 1ll);
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < 8; ++j) {
      dp[i][j] = dp[i-1][j];
    }
    int x = s[i] - '0';
    for (int j = 0; j < 8; ++j) {
      inc(dp[i][ (10 * j + x) % 8 ], dp[i-1][j]);
    }
  }

  return inc(dp[n-1][0], M - 1);
}

int main() {
  cin >> n >> s;
  cout << solve() << endl;
  return 0;
}