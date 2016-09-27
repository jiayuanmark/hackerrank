#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string s;
int n, c[30];

bool check(int c1, int c2) {
  int last = -1;
  for (int i = 0; i < n; ++i) {
    int c = s[i] - 'a';
    if (c != c1 && c != c2) {
      //
    } else if (last == -1) {
      last = c;
    } else if (last == c) {
      return false;
    } else {
      last = c;
    }
  }
  return true;
}

int main() {
  cin >> n >> s;
  for (int i = 0; i < n; ++i) {
    c[s[i] - 'a']++;
  }

  int sol = 0;
  for (int i = 0; i < 26; ++i) {
    for (int j = i+1; j < 26; ++j) {
      if (c[i] == 0 || c[j] == 0)
        continue;
      //if (c[i] + c[j] == n)
      //  continue;
      if (abs(c[i] - c[j]) > 1)
        continue;

      if (check(i, j)) {
        sol = max(sol, c[i] + c[j]);
      }
    }
  }
  cout << sol << endl;
  return 0;
}