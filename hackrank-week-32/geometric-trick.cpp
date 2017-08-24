#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int n;
string s;
vector<ll> ix[3];

int main() {
  cin >> n >> s;
  for (int i = 0; i < n; ++i) {
    ix[s[i] - 'a'].push_back(ll(i+1));
  }

  vector<ll>::iterator it;
  vector<ll> *m1, *m2;
  if (ix[0].size() < ix[2].size()) {
    m1 = &ix[0];
    m2 = &ix[2];
  } else {
    m1 = &ix[2];
    m2 = &ix[0];
  }

  ll sol = 0ll;
  for (auto j : ix[1]) {
    ll mid = j * j;

    for (auto i : *m1) {
      if (i > mid)
        break;
      it = lower_bound(m2->begin(), m2->end(), mid / i);
      if (*it * i == mid) {
        ++sol;
      }
    }
  }
  cout << sol << endl;
  return 0;
}