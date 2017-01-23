#include <iostream>

using namespace std;

typedef long long ll;

ll solve(const ll& n) {
  ll sol = 0ll; 
  for (ll i = 1; i < n; i <<= 1) {
    if (!(n & i)) {
      sol += i;
    }
  }
  return sol;
}

int main() {
  ll q, n;
  cin >> q;
  while (q--) {
    cin >> n;
    cout << solve(n) << endl;
  }
  return 0;
}
