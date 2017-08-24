#include <iostream>
#include <cmath>
#include <queue>
#include <utility>

using namespace std;

queue<int> Q;
int n, s, t;
int g, seed, p;
int r[10000005], d[10000005];

int main() {
  cin >> n >> s >> t;
  cin >> r[0] >> g >> seed >> p;
  for (int i = 0; i < n; ++i) {
    if (i > 0) {
      r[i] = (r[i-1] * g + seed) % p;
    }
    d[i] = -1;
  }

  d[s] = 0;
  Q.push(s);
  while (!Q.empty()) {
    int p = Q.front();
    Q.pop();
    if (p == t) {
      cout << d[t] << endl;
      return 0;
    }
    for (int i = p - r[p]; i <= p + r[p]; ++i) {
      int ix = (i + n) % n;
      if (ix == p) {
        continue;
      }
      if (d[ix] == -1 || d[p] + 1 < d[ix]) {
        d[ix] = d[p] + 1;
        Q.push(ix);
      }
    }
  }
  cout << "-1" << endl;

  return 0;
}