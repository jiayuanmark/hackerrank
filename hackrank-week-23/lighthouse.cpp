#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int n;
string grid[55];

inline double dst(int i, int j, int k, int l) {
  double d1 = double(i - k);
  double d2 = double(j - l);
  return sqrt(d1 * d1 + d2 * d2);
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
  }

  int sol = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == '*') {
        continue;
      }

      int rad = min(min(i, n - 1 - i), min(j, n - 1 - j));
      for (int k = 0; k < n; ++k) {
        for (int l = 0; l < n; ++l) {
          if (grid[k][l] == '.') {
            continue;
          }
          rad = min(rad, (int)ceil(dst(i, j, k, l) - 1.0));
        }
      }
      sol = max(sol, rad);
    }
  }
  cout << sol << endl;

  return 0;
}