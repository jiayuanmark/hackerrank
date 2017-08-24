#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

int n;
ll k, arr[105];

int main() {
  cin >> n;
  vector<pair<ll, ll> > stock_pool(n);
  for (int i = 0; i < n; ++i) {
    cin >> stock_pool[i].first;
    stock_pool[i].second = i + 1;
  }
  sort(stock_pool.begin(), stock_pool.end());

  cin >> k;
  ll sol = 0, q;
  for (int i = 0; i < n && k > 0; ++i) {  
    q = min(k / stock_pool[i].first, stock_pool[i].second);
    k -= q * stock_pool[i].first;
    sol += q;
  }
  cout << sol << endl;

  return 0;
}