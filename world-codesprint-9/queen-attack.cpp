#include <iostream>
#include <utility>
#include <unordered_set>

using namespace std;

static const int DX[8] = {-1,-1,-1,0,1,1,1,0};
static const int DY[8] = {-1,0,1,1,1,0,-1,-1};

typedef long long ll;

int n, k, qx, qy;
unordered_set<ll> vis;

inline ll encode(const int& x, const int& y) {
  return ll(x) * ll(n) + ll(y);
}

inline bool valid(const int& x, const int& y) {
  if (x < 0 || x >= n)
    return false;
  if (y < 0 || y >= n)
    return false;
  return true;
}

int main() {
  cin >> n >> k;
  cin >> qx >> qy;
  --qx;
  --qy;
  int tx, ty;
  for (int i = 0; i < k; ++i) {
    cin >> tx >> ty;
    vis.insert(encode(tx-1, ty-1));
  }

  int sol = 0;
  for (int i = 0; i < 8; ++i) {
    int nx = qx + DX[i], ny = qy + DY[i];
    for (; valid(nx, ny) ; nx += DX[i], ny += DY[i]) {
      if (vis.count(encode(nx, ny)) != 0)
        break;
      ++sol;
    }
  }

  cout << sol << endl;
  return 0;
}