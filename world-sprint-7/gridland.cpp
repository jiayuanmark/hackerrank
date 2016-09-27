#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

using namespace std;

typedef long long LL;

LL n, m, k;
LL r, c1, c2;

map<LL, vector<pair<LL, LL> > > intervals;

inline LL Max(const LL& a, const LL& b) {
  return a > b ? a : b;
}

int main() {
  cin >> n >> m >> k;
  LL sol = n * m;
  while (k--) {
    cin >> r >> c1 >> c2;
    intervals[r].push_back(make_pair(c1, c2));
  }

  for (auto &interval : intervals) {
    vector<pair<LL, LL> > i = interval.second;
    sort(i.begin(), i.end());

    LL last = 0L;
    for (auto &t : i) {
      if (t.second <= last) {
        continue;
      } else if (t.first <= last) {
        sol -= (t.second - last);
      } else {
        sol -= (t.second - t.first + 1);
      }
      last = t.second;
    }
  }
  cout << sol << endl;
  return 0;
}