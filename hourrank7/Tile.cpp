#include <cstdio>

using namespace std;

typedef long long LL;

static const LL M = 1e9 + 7;

LL solve(const LL& n) {
  LL res = ((n * (n - 1) % M) / 2 + n) % M;
  for (LL i = 2; i < n; ++i) {
    LL cnt = n / i;
    LL pad = n % i;
    if (cnt >= 1) {
      res = (res + ((cnt * (cnt + 1) % M) / 2 * pad % M)) % M;
    }
    if (cnt >= 2) {
      res = (res + (cnt * (cnt - 1) % M) / 2 * (i - pad)) % M;
    }
  }
  return res;
}

int main() {
  int t;
  LL n;
  scanf("%d", &t);
  while (t--) {
    scanf("%lld", &n);
    printf("%lld\n", solve(n));
  }
  return 0;
}