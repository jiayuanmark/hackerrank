#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>

using namespace std;

typedef long long ll;

static const int C = 25;

double small[(1 << C) + 5];
unordered_map<ll, double> big[30];

inline bool has(const int& n, const ll& s) {
  if (n < C) {
    return small[s | (1ll << n)] >= 0.0;
  } else {
    return big[n].count(s) != 0;
  }
}

inline double get(const int& n, const ll& s) {
  if (n < C) {
    return small[s | (1ll << n)];
  } else {
    return big[n][s];
  }
}

inline void put(const int& n, const ll& s, const double& v) {
  if (n < C) {
    small[s | (1ll << n)] = v;
  } else {
    big[n][s] = v;
  }
}

inline ll convert(const string& s) {
  ll res = 0ll;
  int n = s.length();
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'W') {
      res |= (1 << (n - 1 - i));
    }
  }
  return res;
}

inline ll drop(const ll& s,
               const ll& p) {
  ll x = (1ll << p);
  ll hi_msk = x ^ -x;
  ll lo_msk = ~x & (x-1);
  return ((s & hi_msk) >> 1) | (s & lo_msk);
}

inline ll read(const ll& s,
              const ll& p) {
  return (s & (1 << p)) ? 1 : 0;
}

double dfs(const ll& s,
           const int& n,
           const int& k) {
  if (k == 0 || s == 0)
    return 0.0;

  if (has(n, s))
    return get(n, s);
  
  double e = 0.0, a = 1.0 / n, tmp;
  for (int i = 0; i < n / 2; ++i) {
    ll s1 = drop(s, i);
    ll s2 = drop(s, n - 1 - i);

    tmp = a * max(read(s, i) + dfs(s1, n-1, k-1),
      read(s, n-1-i) + dfs(s2, n-1, k-1));

    e += 2. * tmp;
  }

  
  if (n % 2) {
    ll ss = drop(s, n / 2);
    e += a * (read(s, n / 2) + dfs(ss, n-1, k-1));
  }

  put(n, s, e);
  return e;
}

int main() {
  int n, k;
  string s;
  memset(small, -1.0, sizeof(small));
  cin >> n >> k;
  cin >> s;
  cout << setprecision(10) << dfs(convert(s), n, k) << endl;
  return 0;  
}
