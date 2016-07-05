#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

typedef long long LL;

vector<pair<int, int> > edges;

int c[50];

int main() {
  int n, m;
  cin >> n >> m;
  
  for (int i = 0; i < n; ++i) {
    cin >> c[i];
  }

  int u, v;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v;
    edges.push_back(make_pair(u-1, v-1));
  }

  int sol = 0, ctr = 0;
  for (LL i = 0L; i < LL(1ll << n); ++i) {
    bool valid = true;
    for (auto &e : edges) {
      if ((i & (1ll << e.first)) && (i & (1ll << e.second))) {
        valid = false;
        break;
      }
    }
    if (!valid)
      continue;
    
    int tmp = 0;
    for (int j = 0; j < n; ++j) {
      if (i & (1ll << j)) {
        tmp += c[j];
      }
    }
    if (tmp > sol) {
      sol = tmp;
      ctr = 1;
    } else if (tmp == sol) {
      ++ctr;
    }
  }
  cout << sol << " " << ctr << endl;

  return 0; 
}
