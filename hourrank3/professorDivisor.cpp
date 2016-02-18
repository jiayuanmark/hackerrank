#include <iostream>

using namespace std;

typedef long long LL;

LL f(const LL& v) {
  LL res = 1;
  LL i;
  for (i = 1; i * i < v; ++i) {
    if (v % i == 0) {
      res *= v; 
    }
  }
  if (i * i == v) {
    res *= i;
  }
  return res;
}

LL solve(const LL& x) {
  for (LL i = 1; i <= x; ++i) {
    if (x % i == 0 && f(i) == x)
      return i;
  }
  return -1;
}

int main() {
  int t;
  cin >> t;
  LL x;
  while (t--) {
    cin >> x;
    cout << solve(x) << endl; 
  }
  return 0;
}