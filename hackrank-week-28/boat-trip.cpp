#include <iostream>

using namespace std;

int main() {
  int n, c, m, p, l;
  cin >> n >> c >> m;
  l = m * c;
  for (int i = 0; i < n; ++i) {
    cin >> p;
    if (p > l) {
      cout << "No" << endl;
      return 0;
    }
  }
  cout << "Yes" << endl;
  return 0;
}
