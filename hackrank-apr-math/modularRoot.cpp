#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

LL modexp(LL b, LL p, LL m) {
  if (b == 0 && p == 0)
    return 1;
  if (b == 0)
    return 0;
  LL res = 1, mul = b % m;
  while (p) {
    if (p & 1) {
      res = (res * mul) % m;
    }
    mul = (mul * mul) % m;
    p >>= 1;
  }
  return res;
}

LL modinverse(const LL& a, const LL& m) {
  LL r = m, newr = a;
  LL t = 0, newt = 1;
  LL q, temp;
  while (newr != 0) {
    q = r / newr;
    temp = r - q * newr;
    r = newr;
    newr = temp;
    temp = t - q * newt;
    t = newt;
    newt = temp;
  }
  return t < 0 ? t + m : t;
}

LL modabs(LL n, LL m) {
  if (n < 0)
    n = n % m;
  return (n + m) % m;
}

LL gcd(LL a, LL b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

vector<int> brute(int k, int n, int p) {
  k = k % (p-1);
  vector<int> res;
  for (int i = 0; i < p; ++i) {
    if (modexp(i, k, p) == n) {
      res.push_back(i);
    }
  }
  return res;
}

vector<int> smart(int k, int n, int p) {
  if (gcd(k, p-1) == 1) {
    int root = modexp(n, modinverse(k, p-1), p);
    vector<int> res;
    res.push_back(root);
    return res;
  }
  return brute(k, n, p);
}

int findgenerator(int p) {
  vector<int> divisors;
  int pp = p - 1;
  for (int d = 1; d * d <= pp; ++d) {
    if (pp % d == 0) {
      divisors.push_back(d);
    }
    if (d * d != pp && pp / d < pp) {
      divisors.push_back(pp / d);
    }
  }

  for (int gg = 1; gg < p; ++gg) {
    bool isgenerator = true;
    for (auto &d : divisors) {
      if (modexp(gg, d, p) == 1) {
        isgenerator = false;
        break;
      }
    }
    if (isgenerator)
      return gg;
  }
  return -1;
}

static const int N = 5000005;
int exptable[N], logtable[N];

void precompute(int p) {
  int g = findgenerator(p);
  //printf("Generator: %d\n", g);
  int res = 1;
  for (int i = 0; i < p; ++i) {
    exptable[i] = res;
    logtable[res] = i;
    res = (res * g) % p; 
  }
}

vector<int> solve(int k, int n, int p) {
  vector<int> res;

  int N = logtable[n];
  k = k % (p-1);
  int G = gcd(k, p-1);
  if (N % G != 0)
    return res;
  int pp = (p - 1) / G; 
  int v = ((N / G) * modinverse(k / G, pp)) % pp;

  for (int gi = 0; gi < G; ++gi) {
    res.push_back(exptable[v + gi * pp]);
  }
  sort(res.begin(), res.end());
  return res;
}

void print(const vector<int>& sol) {
  if (sol.size() == 0) {
    printf("NONE\n");
    return;
  }
  for (int i = 0; i < sol.size(); ++i) {
    if (i == 0) {
      printf("%d", sol[i]);
    } else {
      printf(" %d", sol[i]);
    }
  }
  printf("\n");
}

int main() {
  int p, Q;
  scanf("%d%d", &p, &Q);
  precompute(p);
  while (Q--) {
    int k, n;
    scanf("%d%d", &k, &n);
    n = modabs(n, p);
    if (n == 0) {
      printf("0\n");
      continue;
    }
    print(solve(k, n, p));
  }
  return 0;
}