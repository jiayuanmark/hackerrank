#include <iostream>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  if (m % n == 0) {
    cout << 0 << endl;
  } else {
    cout << n - (m % n) << endl;
  }
  return 0;
}