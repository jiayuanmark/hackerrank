#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

int main() {
  int k, n;
  cin >> k >> n;

  vector<LL> rds(k);
  LL tmp = 0;
  for (int i = 0; i < k; ++i) {
    cin >> tmp;
    rds[i] = tmp * tmp;
  }
  sort(rds.begin(), rds.end());

  LL x, y, sol = 0L;
  vector<LL>::iterator it;
  for (int i = 0; i < n; ++i) {
    cin >> x >> y;
    tmp = x * x + y * y;
    it = lower_bound(rds.begin(), rds.end(), tmp);
    if (it == rds.end())
      continue;
    //cout << k - (it - rds.begin()) << endl;
    sol += (k - (it - rds.begin()));
  }
  cout << sol << endl;

  return 0;
}