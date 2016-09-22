#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());
  int s = 0;
  for (int i = 0; i < n-1; ++i) {
    s += a[i];
  }
  if (n == 1) {
    cout << "2" << endl;
  } else if (n == 2) {
    cout << (a[0] == a[1] ? "2" : "1") << endl;
  } else if (s > a[n-1]) {
    cout << "0" << endl;
  } else {
    cout << "1" << endl;
  }

  return 0;
}