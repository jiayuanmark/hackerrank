#include <cstdio>
#include <cstring>

int n;
int sol[100005];

void solve() {
  if (n % 2) {
    int s = n / 2 + 1;
    for (int i = 0; i < n; i += 2) {
      sol[i] = s++;
    }
    s = n / 2;
    for (int i = 1; i < n; i += 2) {
      sol[i] = s--;
    }
  } else {
    int s = n / 2;
    for (int i = 0; i < n; i += 2) {
      sol[i] = s--;
    }
    s = n / 2 + 1;
    for (int i = 1; i < n; i += 2) {
      sol[i] = s++;
    }
  }
}


int main() {
  int t;
  scanf("%d", &t);

  while (t--) {
    scanf("%d", &n);
    solve();
    for (int i = 0; i < n; ++i) {
      printf("%d ", sol[i]);
    }
    printf("\n");
  }

  return 0;
}