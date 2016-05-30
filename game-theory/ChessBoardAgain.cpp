#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

int g[20][20];

int grundy(int x, int y) {
  int &res = g[x][y];
  if (res != -1) {
    return res;
  }
  if (x <= 2 && y <= 2) {
    res = 0;
    return res;
  }

  set<int> st;
  if (x > 2 && y > 1) {
    st.insert(grundy(x-2, y-1));
  }
  if (y > 2 && x > 1) {
    st.insert(grundy(x-1, y-2));
  }
  if (y < 15 && x > 2) {
    st.insert(grundy(x-2, y+1));
  }
  if (x < 15 && y > 2) {
    st.insert(grundy(x+1, y-2));
  }
  
  res = 0;
  while (st.count(res) != 0) {
    ++res;
  }
  return res;
}

int main() {
  memset(g, -1, sizeof(g));

  int t, k, x, y;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &k);
    int X = 0;
    while (k--) {
      scanf("%d%d", &x, &y);
      X ^= grundy(x, y);
    }
    if (X) {
      printf("First\n");
    } else {
      printf("Second\n");
    }
  }
  return 0; 
}
