#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef long long LL;

static const int N = 100005;

int a[N], tree[N+1];

void update(int idx) {
  while (idx <= N) {
    tree[idx]++;
    idx += (idx & -idx);
  }
}

int read(int idx) {
  int res = 0;
  while (idx > 0) {
    res += tree[idx];
    idx -= (idx & -idx);
  }
  return res;
}

int main() {
  int t, n;
  scanf("%d", &t);
  while (t--) {
    // zero
    memset(tree, 0, sizeof(tree));
    // read input
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    // build mapping
    vector<int> temp(a, a + n);
    sort(temp.begin(), temp.end());
    unordered_map<int,int> s;
    int num = 1;
    for (auto &v : temp) {
      if (s.count(v) == 0) {
        s[v] = num++;
      }
    }

    // solve
    LL res = 0L;
    update(s[a[0]]);
    for (int i = 1; i < n; ++i) {
      int cnt = read(s[a[i]]);
      //printf("count of <= %d: %d (index %d)\n", a[i], cnt, s[a[i]]);
      res += (i - cnt);
      update(s[a[i]]);
    }
    printf("%lld\n", res);
  }
  return 0;
}