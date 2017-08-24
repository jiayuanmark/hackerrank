#include <iostream>
#include <algorithm>

using namespace std;

static const int UP = 1001;
static const int LO = -1;

int q, k, n, A[50];

int dfs(int lhs, int rhs, int cnt) { 
  if (cnt == 0) {
    return 0;
  }
  int mi = UP, profit = 0;
  for (int i = lhs; i <= rhs; ++i) {
    mi = min(mi, A[i]);
    profit = max(A[i] - mi, profit);
  }

  for (int i = lhs+1; i < rhs; ++i) {
    profit = max(profit, dfs(lhs, i, cnt - 1) + dfs(i, rhs, 1));
  }
  return profit;
}

int main() {
  cin >> q;
  while (q--) {
    cin >> k >> n;
    for (int i = 0; i < n; ++i) {
      cin >> A[i];
    }
    cout << dfs(0, n-1, k) << endl;
  }
  return 0;
}