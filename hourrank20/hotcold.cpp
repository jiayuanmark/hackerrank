#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  int c1, c2, h1, h2;
  cin >> c1 >> c2 >> h1 >> h2;
  if (max(c1, c2) <= min(h1, h2)) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
  return 0;
}