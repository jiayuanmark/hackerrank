#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

typedef long long LL;

vector<pair<int, int> > edges;

int n, m, k, c[50];
LL val[1 << 20], mval[1 << 20], mcnt[1 << 20];

LL weight(LL msk) {
  LL res = 0ll;
  for (LL i = 0; i < n; ++i) {
    if (msk & (1ll << i)) {
      res += c[i];
    }
  }
  return res;
}

void init() {
  for (int i = 0; i < (1 << 20); ++i) {
    val[i] = -1;
  }
}

bool independent(LL msk) {
  for (auto &e : edges) {
    if ((msk & (1ll << e.first)) && (msk & (1ll << e.second))) {
      return false;
    }
  }
  return true;
}

void fill(const int i, const int cur, const int msk) {
  if (i == k) {
    if (val[cur] > mval[msk]) {
      mval[msk] = val[cur];
      mcnt[msk] = 1;
    } else if (val[cur] == mval[msk]) {
      ++mcnt[msk];
    }
    return;
  }
  fill(i+1, cur, msk);
  if (msk & (1 << i)) {
    fill(i+1, cur | (1 << i), msk);
  }
}

void print_msk(LL msk) {
  cout << "{";
  for (LL i = 0; i < n; ++i) {
    if (msk & (1ll << i)) {
      cout << i << ","; 
    }
  }
  cout << "}";
}

int main() {
  cin >> n >> m;
  
  for (int i = 0; i < n; ++i) {
    cin >> c[i];
  }

  if (n == 1) {
    cout << c[0] << " " << 1 << endl;
    return 0;
  }

  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    edges.push_back(make_pair(u-1, v-1));
  }

  k = n / 2;
  init();
  for (LL i = 0; i < (1 << k); ++i) {
    if (independent(i)) {
      val[i] = weight(i);
    }
  }

  for (int i = 0; i < (1 << k); ++i) {
    fill(0, 0, i);
  }

  LL soln = -1, ctrn = 0L;
  for (LL i = 0; i < (1ll << (n-k)); ++i) {
    LL msk = (i << k);
    if (!independent(msk)) {
      continue;
    }

    LL left_msk = (1ll << k) - 1;
    for (auto &e : edges) {
      if ((msk & (1ll << e.first)) &&
          e.second < k &&
          (left_msk & (1ll << e.second))) {
        left_msk ^= (1ll << e.second); 
      }
      if ((msk & (1ll << e.second)) &&
          e.first < k &&
          (left_msk & (1ll << e.first))) {
        left_msk ^= (1ll << e.first);
      }
    }

    LL sol = mval[left_msk] + weight(msk);
    //print_msk(left_msk);
    //cout << " ";
    //print_msk(msk);
    //cout << " " << mval[left_msk] << " " << weight(msk) << endl;
    if (sol > soln) {
      soln = sol;
      ctrn = mcnt[left_msk];
    } else if (sol == soln) {
      ctrn += mcnt[left_msk];
    }
  }
  cout << soln << " " << ctrn << endl;

  return 0; 
}
