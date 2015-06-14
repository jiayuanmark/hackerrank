#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef long long LL;

const int N = 300005;
LL tcnt[N];

void update(int idx, LL val) {
  while (idx <= N) {
    tcnt[idx] += val;
    idx += (idx & -idx);
  }
}

LL read(int idx) {
  LL ret = 0;
  while (idx > 0) {
    ret += tcnt[idx];
    idx -= (idx & -idx);
  }
  return ret;
}

int main() {
  int n, lhs, rhs;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> lhs >> rhs;
    update(lhs+1, 1);
    update(rhs+2, -1);
  }

  LL sol = 0;
  for (int i = n; i >= 1; --i) {
    if (((LL)i) <= read(i))
      sol = max(sol, (LL)i);
  }
  cout << sol << endl;
  return 0;
}