#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;

static const ll M = 1000000007ll;
static const int MX = 100005;

int n, k;
ll a[MX];
int b[64];

ll nchoosek(int n_, int k_) {
  vector<ll> c(k_ + 1, 0ll);
  c[0] = 1;
  for (int i = 1; i <= n_; ++i) {
    for (int j = min(i, k_); j > 0; --j) {
      c[j] = (c[j] + c[j-1]) % M;
    }
  }
  return c[k_];
}

void solve() {
  vector<ll> cand(n), chosen;
  for (int i = 0; i < n; ++i) {
    cand[i] = a[i];
  }

  for (int p = 63; p >= 0; --p) {
    chosen.clear();
    for (auto &e : cand) {
      if ((e >> ll(p)) & 1) {
        chosen.push_back(e);
      }
    }
    if (chosen.size() >= k) {
      swap(chosen, cand);
    }
  }

  ll res = cand[0];
  int cnt = cand.size();
  for (int i = 1; i < cnt; ++i) {
    res &= cand[i];
  }

  cout << res << endl;
  cout << nchoosek(cnt, min(k, cnt-k)) << endl;
}

int main() {
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  solve();
  return 0;
}