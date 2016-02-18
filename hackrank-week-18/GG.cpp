#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

typedef long long LL;

int n;
LL m;
string s;
int num[3005];

LL sol = 0;

void perm(const int& l) {
  if (l == n) {
    sol = (sol + 1) % m;
    return;
  }

  for (int i = l; i < n; ++i) {
    if (l != 0 && s[l-1] == 'G' && num[l-1] < num[i])
      continue;
    if (l != 0 && s[l-1] == 'L' && num[l-1] > num[i])
      continue;
    swap(num[i], num[l]);
    perm(l + 1);
    swap(num[i], num[l]);
  }
}

int main() {
  cin >> n >> m;
  cin >> s;

  for (int i = 0; i < n; ++i) {
    num[i] = i;
  }

  perm(0);

  cout << sol << endl;
  return 0;
}