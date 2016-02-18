#include <cstdio>
#include <cstring>

int n, m;
int x, d;

void solve() {
  int r = m % n;
  
  if (r == 0) {
    x = n / 2 + 1;
    d = m / n - 1;
    return;
  }
  d = m / n;
  if (n % 2) {
    if (d % 2) {
      if (r % 2)
        x = n - (r / 2);
      else
        x = r / 2;
    } else {
      if (r % 2)
        x = 1 + (r / 2);
      else
        x = n - (r / 2) + 1;
    }
  } else {
    if (r % 2)
      x = 1 + (r / 2);
    else
      x = n - (r / 2) + 1;
  }
}


int main() {
  int t;
  scanf("%d", &t);

  while (t--) {
    scanf("%d%d", &n, &m);
    solve();
    printf("%d %d\n", x, d);
  }

  return 0;
}