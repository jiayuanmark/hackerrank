#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;

static const int D = 21;
static const ll M = 1000000007ll;
static const ll base[4] = {2, 3, 5, 7};
static const double ln2 = log2(2.0);
static const double ln3 = log2(3.0);
static const double ln5 = log2(5.0);
static const double ln7 = log2(7.0);

ll factor(int num, int f) {
  ll res = 0;
  while (num != 0) {
    if (num % f == 0) {
      ++res;
      num /= f;
    } else {
      break;
    }
  }
  return res;
}

struct BigInt {
  ll p[4];
  bool zero;

  BigInt() : zero(true) {
    memset(p, 0, sizeof(p));
  }
  
  BigInt(const int& num) {
    zero = (num == 0);
    for (int i = 0; i < 4; ++i) {
      p[i] = factor(num, base[i]);
    }
  }
};

inline BigInt operator*(const BigInt& lhs, const BigInt& rhs) {
  if (lhs.zero) {
    return lhs;
  }
  if (rhs.zero) {
    return rhs;
  }

  BigInt res(1);
  for (int i = 0; i < 4; ++i) {
    res.p[i] = lhs.p[i] + rhs.p[i];
  }
  return res;
}

inline BigInt bmax(const BigInt& lhs, const BigInt& rhs) {
  if (lhs.zero) {
    return rhs;
  }
  if (rhs.zero) {
    return lhs;
  }
  ll d1 = lhs.p[0] - rhs.p[0];
  ll d2 = lhs.p[1] - rhs.p[1];
  ll d3 = lhs.p[2] - rhs.p[2];
  ll d4 = lhs.p[3] - rhs.p[3];
  double tmp = (d1 * ln2 + d2 * ln3 + d3 * ln5 + d4 * ln7);
  return tmp < 0 ? rhs : lhs;
}

inline ll to_long(const BigInt& b) {
  ll res = 1l;
  for (int i = 0; i < 4; ++i) {
    ll t = b.p[i], b = base[i];
    while (t) {
      if (t & 1) {
        res = (res * b) % M;
      }
      b = (b * b) % M;
      t >>= 1;
    }
  }
  return res;
}

int n, x, s, f, m;
BigInt mat[D][D], res[D][D], tmp[D][D];

inline void square_mat() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      tmp[i][j] = BigInt();
      for (int k = 0; k < n; ++k) {
        tmp[i][j] = bmax(tmp[i][j], mat[i][k] * mat[k][j]);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    memcpy(&mat[i], &tmp[i], sizeof(tmp[0]));
  }
}

inline void multiply_mat() {
  memset(tmp, 0, sizeof(tmp));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      tmp[i][j] = BigInt();
      for (int k = 0; k < n; ++k) {
        tmp[i][j] = bmax(tmp[i][j], res[i][k] * mat[k][j]);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    memcpy(&res[i], &tmp[i], sizeof(tmp[0]));
  }
}

void solve() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        res[i][j] = BigInt(1);
      } else {
        res[i][j] = BigInt(0);
      }
    }
  }
  while (m) {
    if (m & 1) {
      multiply_mat();
    }
    square_mat();
    m >>= 1;
  }
  cout << (to_long(res[s][f]) * x) % M << endl;
}

int main() {
  cin >> n >> x >> s >> f >> m;
  int tmp;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> tmp;
      mat[i][j] = BigInt(tmp);
    }
  }
  solve();
  return 0;
}