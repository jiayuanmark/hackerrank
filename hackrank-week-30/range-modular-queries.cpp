#include <iostream>

using namespace std;

int n, q;
int a[40005];

int main() {
  cin >> n >> q;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  int lhs, rhs, x, y;
  while (q--) {
    cin >> lhs >> rhs >> x >> y;
    int cnt = 0;
    for (int i = lhs; i <= rhs; ++i) {
      if (a[i] % x == y) {
        ++cnt;
      }
    }
    cout << cnt << endl;
  }
  return 0;
}