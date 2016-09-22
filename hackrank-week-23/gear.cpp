#include <iostream>
#include <algorithm>

using namespace std;


int main() {
  int q, n;
  cin >> q;
  while (q--) {
    cin >> n;
    if (n % 2) {
      cout << "No" << endl;
    } else {
      cout << "Yes" << endl;
    }
  }

  return 0;
}