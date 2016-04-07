#include <cstdio>
#include <vector>

using namespace std;

typedef long long LL;

vector<LL> a;

int solve(const int& lhs,
          const int& rhs,
          const LL& s,
          const int& cnt) {
  if (lhs >= rhs)
    return cnt;
  if (s % 2 == 1)
    return cnt;
  LL ss = s / 2, temp = 0L;
  int i;
  for (i = lhs; i <= rhs; ++i) {
    temp += a[i];
    if (temp > ss)
      return cnt;
    if (temp == ss) {
      return max(solve(lhs, i, ss, cnt+1), solve(i+1, rhs, ss, cnt+1));
    }
  }
  return cnt;
}


int main() {
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    a.resize(n);
    LL sum = 0L;
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &a[i]);
      sum += a[i];
    }
    printf("%d\n", solve(0, n-1, sum, 0));
  }
  return 0; 
}