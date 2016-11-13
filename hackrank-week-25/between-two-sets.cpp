#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static const int P[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
static const int SZ = sizeof(P) / sizeof(P[0]);

vector<int> factor(int n) {
  vector<int> res(SZ, 0);
  int ix = 0;
  while (n != 1) {
    while (n % P[ix] == 0) {
      ++res[ix];
      n /= P[ix];
    }
    ++ix;
  }
  return res;
}

vector<int> af, bf;

void Max(const vector<int>& f) {
  for (int i = 0; i < SZ; ++i) {
    af[i] = max(af[i], f[i]);
  }
}

void Min(const vector<int>& f) {
  for (int i = 0; i < SZ; ++i) {
    bf[i] = min(bf[i], f[i]);
  }
}

int main() {
  int n, m, a, b;
  cin >> n >> m;

  cin >> a;
  af = factor(a);
  for (int i = 1; i < n; ++i) {
    cin >> a;
    Max(factor(a));
  }

  cin >> b;
  bf = factor(b);
  for (int i = 1; i < m; ++i) {
    cin >> b;
    Min(factor(b));
  }

  int res = 1;
  for (int i = 0; i < SZ; ++i) {
    if (af[i] > bf[i]) {
      cout << "0" << endl;
      return 0;
    }
    if (bf[i] != 0 && bf[i] >= af[i]) {
      res *= (bf[i] - af[i] + 1);
    }
  }
  cout << res << endl;
  return 0;
}