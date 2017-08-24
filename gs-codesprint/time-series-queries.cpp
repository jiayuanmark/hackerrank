#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

static const int MX = 100005;
typedef long long ll;

int n, q;

int main() {
  cin >> n >> q;
  vector<ll> t(n), p(n);
  for (int i = 0; i < n; ++i) {
    cin >> t[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
  }

  vector<ll> lhs(n), rhs(n);
  ll tmp = 0;
  for (int i = 0; i < n; ++i) {
    tmp = lhs[i] = max(tmp, p[i]);
  }

  tmp = 0;
  for (int i = n-1; i >= 0; --i) {
    tmp = rhs[i] = max(tmp, p[i]);
  }

  int tp; ll v;
  vector<ll>::iterator it;
  while (q--) {
    cin >> tp >> v;
    if (tp == 1) {
      it = lower_bound(lhs.begin(), lhs.end(), v);
      if (it == lhs.end()) {
        cout << "-1" << endl;
      } else {
        cout << t[it - lhs.begin()] << endl;
      }
    }
    if (tp == 2) {
      it = lower_bound(t.begin(), t.end(), v);
      if (it == t.end()) {
        cout << "-1" << endl;
      } else {
        cout << rhs[it - t.begin()] << endl;
      }
    }
  }


  return 0;
}