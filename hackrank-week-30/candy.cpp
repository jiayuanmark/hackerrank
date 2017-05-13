#include <iostream>

using namespace std;

int main() {
  int n, t, c, s = 0;
  cin >> n >> t;
  int b = n;
  for (int i = 0; i < t; ++i) {
    cin >> c;
    if (i == t - 1)
      break;
    b -= c;
    if (b < 5) {
      s += (n - b);
      b = n;
    }
  }
  cout << s << endl;
  return 0;
}