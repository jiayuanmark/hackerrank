#include <iostream>
#include <algorithm>

using namespace std;

int a, b, d;

int solve() {
  if (d % b == 0) {
    return d / b;
  } else {
    if (d / b >= 1) {
      return d / b + 1;
    } else {
      return d == a ? 1 : 2;
    }
  }
}

int main() {
  int q;
  cin >> q;
  while (q--) {
    cin >> a >> b >> d;
    cout << solve() << endl;
  }
  return 0;
}