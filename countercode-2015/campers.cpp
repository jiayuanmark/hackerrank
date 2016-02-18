#include <cstdio>

bool arr[2000005];

int main() {
  int n, k, temp;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < k; ++i) {
    scanf("%d", &temp);
    arr[temp] = true;
  }

  for (int i = 1; i <= n; ++i) {
    if (arr[i])
      continue;
    if (i - 1 >= 1 && arr[i-1])
      continue;
    if (i + 1 <= n && arr[i+1])
      continue;
    arr[i] = true;
    ++k;
  }

  printf("%d\n", k);
  return 0;
}