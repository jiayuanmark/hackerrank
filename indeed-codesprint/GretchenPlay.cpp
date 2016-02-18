#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

static const int SZ = 100005;

int assign[SZ];
int scene[SZ];

int cnt[SZ + 1];

int read(int idx) {
  int res = 0;
  while (idx > 0) {
    res += cnt[idx];
    idx -= (idx & -idx);
  }
  return res;
}

void update(int idx, const int& v) {
  while (idx <= SZ) {
    cnt[idx] += v;
    idx += (idx & -idx);
  }
}

int main() {
    int M, N, Q;
    cin >> M >> N >> Q;

    for (int i = 0; i < N; ++i) {
      cin >> assign[i];
      scene[assign[i]]++;
    }

    for (int i = 0; i < M; ++i) {
      update(scene[i] + 1, 1);
    }

    int a, n, m, p;
    while (Q--) {
      cin >> a;
      if (a == 1) {
        cin >> n >> m;
        update(scene[assign[n]]+1, -1);
        update(scene[assign[n]], 1);
        
        scene[assign[n]]--;
        assign[n] = m;

        update(scene[assign[n]]+1, -1);
        update(scene[assign[n]]+2, 1);
        
        scene[assign[n]]++;
      } else {
        cin >> p;
        cout << read(p) << endl;
      }
    }

    return 0;
}
