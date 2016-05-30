#include <iostream>
#include <cstring>

using namespace std;

int win[20][20];

int dfs(int x, int y) {
  int &res = win[x][y];
  if (res != -1) {
    return res;
  }
  if (x <= 2 && y <= 2) {
    res = 0;
    return res;
  }
  if (x > 2 && y > 1 && !dfs(x-2, y-1)) {
    res = 1;
    return res;
  }
  if (y > 2 && x > 1 && !dfs(x-1, y-2)) {
    res = 1;
    return res;
  }
  if (y < 15 && x > 2 && !dfs(x-2, y+1)) {
    res = 1;
    return res;
  }
  if (x < 15 && y > 2 && !dfs(x+1, y-2)) {
    res = 1;
    return res;
  }
  res = 0;
  return res;
}

int main() {
  memset(win, -1, sizeof(win));
  int t, x, y;
  cin >> t;
  while (t--) {
    cin >> x >> y;
    if (dfs(x, y)) {
      cout << "First" << endl;
    } else {
      cout << "Second" << endl;
    }
  }
  return 0; 
}
