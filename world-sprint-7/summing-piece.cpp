#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

static const int N = 1000005;
static const LL M = 1e9 + 7L;

int n;
LL ex[N], c[N];

void calc_ex() {
  ex[0] = ex[1] = 1L;
  for (int i = 2; i <= n; ++i) {
    ex[i] = (ex[i-1] * 2) % M;
  }
}

inline void inc(LL& acc, const LL& i) {
  acc = (acc + i) % M;
}

inline LL mul(const LL& a, const LL& b) {
  return (a * b) % M;
}

int main() {
  cin >> n;  
  calc_ex();

  int limit = n / 2 - (n % 2 ? 0 : 1);
  for (int i = 0; i <= limit; ++i) {
    // calculate c[i] and c[n-1-i]
    for (int l = 1; l <= n; ++l) {
      for (int j = max(0, i - l + 1); j <= i && j + l <= n; ++j) {
        inc(c[i], mul(mul(l, ex[j]), ex[n - j - l]));
      }
    }
    if (!c[n-1-i]) {
      c[n-1-i] = c[i];
    }
  }

  // calc solution
  LL sol = 0L, tmp;
  for (int i = 0; i < n; ++i) {
    cin >> tmp;
    //cout << c[i] << endl;
    inc(sol, mul(tmp, c[i]));
  }
  cout << sol << endl;

  return 0;
}