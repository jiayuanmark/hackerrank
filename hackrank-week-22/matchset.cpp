#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

int main() {
  int n;
  cin >> n;
  vector<LL> x(n), y(n);
  for (int i = 0; i < n; ++i) {
    cin >> x[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> y[i];
  }
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());

  LL delta = 0L, d = 0L, temp = 0L;
  for (int i = 0; i < n; ++i) {
    temp = x[i] - y[i];
    if (temp > 0) {
      d += temp;
    }
    delta += temp;
  }

  if (delta == 0) {
    cout << d << endl;
  } else {
    cout << -1 << endl;
  }
  return 0;
}