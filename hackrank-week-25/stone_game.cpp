#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

typedef long long LL;

vector<LL> s;
unordered_map<LL, LL> g;

LL grundy(LL x) {
  if (x == 1) {
    return 0;
  }

  if (g.count(x) != 0) {
    return g[x];
  }

  vector<LL> v;
  v.push_back(-1);
  for (auto &f : s) {
    if (x % f == 0) {
      if (f % 2) {
        v.push_back(grundy(x / f));
      } else {
        v.push_back(0);
      }
    }
  }

  sort(v.begin(), v.end());
  for (int i = 1; i < v.size(); ++i) {
    if (v[i] - v[i-1] > 1) {
      g[x] = v[i-1] + 1;
      return g[x];
    }
  }
  g[x] = v.back() + 1;
  return g[x];
}

int main() {
  LL n, tmp;
  int m;
  cin >> n >> m;

  for (int i = 0; i < m; ++i) {
    cin >> tmp;
    if (n % tmp == 0) {
      s.push_back(tmp);
    }
  }

  if (grundy(n)) {
    cout << "First" << endl;
  } else {
    cout << "Second" << endl;
  }
  return 0;
}