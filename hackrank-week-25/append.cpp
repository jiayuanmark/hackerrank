#include <iostream>
#include <string>

using namespace std;

int main() {
  string s, t;
  int k;
  cin >> s >> t >> k;

  int n = s.length(), m = t.length();
  int p;
  for (p = 0; p < n && p < m; ++p) {
    if (s[p] != t[p]) break;
  }
  int n1 = n - p, m1 = m - p;

  if (n1 + m1 > k) {
    cout << "No" << endl;
    return 0;
  }
  if (k >= n + m) {
    cout << "Yes" << endl;
    return 0;
  }

  if (!((k - (n1 + m1)) % 2)) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
  return 0;
}