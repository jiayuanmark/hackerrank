#include <iostream>
#include <algorithm>

using namespace std;

bool win[105];

void precompute() {
  win[0] = false;
  win[1] = false;
  for (int i = 2; i <= 100; ++i) {
    if (!win[i-2] || (i >= 3 && !win[i-3]) || (i >= 5 && !win[i-5])) {
      win[i] = true;
    } else {
      win[i] = false;
    }
  }
}


int main() {
  precompute();
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    if (win[n]) {
      cout << "First" << endl;
    } else {
      cout << "Second" << endl;
    }
  }
  return 0;
}