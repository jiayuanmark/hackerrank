#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

static const ll M = 1000000007ll;
static const int MX = 500005;

string s;
ll fac[MX], ifac[MX];

ll inverse(ll a) {
  ll t = 0, newt = 1;
  ll r = M, newr = a;
  ll q;
  while (newr != 0) {
    q = r / newr;
    t -= q * newt;
    r -= q * newr;
    swap(t, newt);
    swap(r, newr);
  }
  if (t < 0) t += M;
  return t;
}

void precompute() {
  fac[0] = ifac[0] = 1ll;
  for (ll i = 1ll; i < MX; ++i) {
    fac[i] = (i * fac[i-1]) % M;
    ifac[i] = (inverse(i) * ifac[i-1]) % M;
  }
}

ll nchoosek(int n_, int k_) {
  return (((fac[n_] * ifac[k_]) % M) * ifac[n_-k_]) % M;
}

ll solve() {
  int ca = 0, cb = 0, cc = 0, cd = 0, n = s.length();
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'a') {
      ++ca;
    } else if (s[i] == 'b') {
      ++cb;
    } else if (s[i] == 'c') {
      ++cc;
    } else {
      ++cd;
    }
  }
  int m1 = min(ca, cb), m2 = min(cc, cd);
  ll res1 = nchoosek(ca + cb, m1), res2 = nchoosek(cc + cd, m2);
  return ((res1 * res2) % M + M - 1) % M;
}

int main() {
  int q;
  cin >> q;
  precompute();
  while (q--) {
    cin >> s;
    cout << solve() << endl;
  }
  return 0;
}