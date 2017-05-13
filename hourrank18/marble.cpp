#include <iostream>

using namespace std;

int main() {
  int m, n, a, b;
  cin >> m >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a >> b;
    if (m == b) {
      m = a;
    } else if (m == a) {
      m = b;
    }
  }
  cout << m << endl;
  return 0;
}