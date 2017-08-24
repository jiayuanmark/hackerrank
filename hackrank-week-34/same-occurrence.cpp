#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

int n, q, x, y;
int a[8005], dp[8005][8005], pos[8005], val[8005];
unordered_map<int, int> value_m;
unordered_map<int, vector<int> > index_m;
unordered_map<int, int> deltas;

inline int choose2(const int& m) {
  return (m + 1) * m / 2;
}

inline void push(const int& p, const int& v, int& sz) {
  pos[sz] = p;
  val[sz] = v;
  ++sz;
}

int main() {
  cin >> n >> q;
  int cnt = 1;
  for (int i = 0; i < n; ++i) {
    cin >> a[i]; 
    if (value_m.count(a[i]) == 0) {
      value_m[a[i]] = cnt++;
    }
    a[i] = value_m[a[i]];
  }

  for (int i = 0; i < n; ++i) {
    index_m[a[i]].push_back(i);
  }

  memset(dp, -1, sizeof(dp));

  while (q--) {
    cin >> x >> y;
    if (value_m.count(x) == 0 && value_m.count(y) == 0) {
      cout << choose2(n) << endl;
      continue;
    }
    if (value_m.count(x) == 0 || value_m.count(y) == 0) {
      if (value_m.count(x) == 0) {
        x = value_m[y];
      } else {
        x = value_m[x];
      }
      if (dp[0][x] != -1) {
        cout << dp[0][x] << endl;
        continue;
      }
      int prev = 0;
      int &ans = dp[0][x];
      ans = 0;
      for (int i = 0; i < n; ++i) {
        if (a[i] == x) {
          ans += choose2(i - prev);
          prev = i+1;
        }
      }
      ans += choose2(n - prev);
      cout << ans << endl;
      continue;
    }
    x = value_m[x];
    y = value_m[y];
    if (dp[x][y] != -1) {
      cout << dp[x][y] << endl;
    } else if (x == y) {
      dp[x][y] = choose2(n);
      cout << dp[x][y] << endl; 
    } else {
      // combine indices
      int sz = 0;
      auto vi = index_m[x].begin(), vj = index_m[y].begin();
      while (vi != index_m[x].end() && vj != index_m[y].end()) {
        if (*vi < *vj) {
          push(*vi, 0, sz);
          ++vi;
        } else {
          push(*vj, 1, sz);
          ++vj;
        }
      }

      while (vi != index_m[x].end()) {
        push(*vi, 0, sz);
        ++vi;
      }
      while (vj != index_m[y].end()) {
        push(*vj, 1, sz);
        ++vj;
      }

      // calculate delta
      deltas.clear();
      int cx = 0, cy = 0;
      for (int i = 0; i + 1 < sz; ++i) {
        if (val[i] == 0)
          ++cx;
        if (val[i] == 1)
          ++cy;
        deltas[cx - cy] += (pos[i+1] - pos[i]);
      }
     
      // head
      deltas[0] += (pos[0] + 1);

      // tail
      if (val[sz-1] == 0)
        ++cx;
      if (val[sz-1] == 1)
        ++cy;
      deltas[cx - cy] += (n - pos[sz-1]);

      int ans = 0;
      for (auto d : deltas) {
        ans += d.second * (d.second - 1) / 2;
      }
      dp[x][y] = dp[y][x] = ans;
      cout << ans << endl;
    }
  }
  return 0;
}
