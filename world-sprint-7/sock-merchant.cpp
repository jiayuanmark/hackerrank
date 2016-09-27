#include <iostream>

using namespace std;

int color[200];

int main() {
  int n, c;
  cin >> n;
  while (n--) {
    cin >> c;
    ++color[c];
  }

  int sol = 0;
  for (int i = 1; i <= 100; ++i) {
    sol += (color[i] / 2);
  }
  cout << sol << endl;
  return 0;
}