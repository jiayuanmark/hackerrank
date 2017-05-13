#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

static const int MX = 100005;
static const ll MOD = 1000000007ll;
static const int SMALL = 23;

ll sol;
int n;
vector<int> graph[MX];

ll solve_small() {
  assert(n <= SMALL);
  sol = 0ll;
  for (int msk = 0; msk < (1 << n); ++msk) {
    int bitcount = __builtin_popcount(msk);
    if (bitcount == 1 || bitcount == n - 1)
      continue;
    bool valid = true;
    for (int u = 0; u < n; ++u) {
      bool success = false;
      for (auto &v : graph[u]) {
        if (((msk >> u) & 1) == ((msk >> v) & 1)) {
          success = true;
          break;
        }
      }
      if (!success) {
        valid = false;
        break;
      }
    }
    if (valid) {
      sol = (sol + 1ll) % MOD;
    }
  }
  return sol;
}

int main() {
  cin >> n;
  int u, v;
  for (int i = 0; i < n-1; ++i) {
    cin >> u >> v;
    graph[u-1].push_back(v-1);
    graph[v-1].push_back(u-1);
  }

  if (n <= SMALL) {
    cout << solve_small() << endl;
  } else {
    cout << 0 << endl;
  }
  return 0;
}
