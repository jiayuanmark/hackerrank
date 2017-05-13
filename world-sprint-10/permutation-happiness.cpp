#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

static const ll M = 1000000007ll;

int q, n, k;
ll dp[3005][3005];

void precompute() {
  dp[1][1] = 1ll;
  ll p1, p2;
  for (int i = 2; i <= 3000; ++i) {
    for (int j = 1; j * 2 <= i + 1; ++j) {
      p1 = (dp[i-1][j] * (2 * j)) % M;
      p2 = (dp[i-1][j-1] * ll(i - 2 * (j-1))) % M;
      dp[i][j] = (p1 + p2) % M;
    }
  }
}

int main() {
  precompute();
  cin >> q;
  while (q--) {
    cin >> n >> k;
    ll res = 0ll;
    for (int i = 0; i <= n - k; ++i) {
      res = (res + dp[n][i]) % M;
    }
    cout << res << endl;
  }
  return 0;
}