#include <iostream>

using namespace std;

int q, n, k, x;
double d;

inline double Max(const double& a, const double& b) {
  return a > b ? a : b;
}

bool solve() {
  double fee = 0.0;
  double p;
  for (int i = 0; i < n; ++i) {
    cin >> p;
    fee += Max(k, p * x / 100.0);
  }
  return fee <= d;
}

int main() {
  cin >> q;
  while (q--) {
    cin >> n >> k >> x >> d;
    if (solve()) {
      cout << "fee" << endl;
    } else {
      cout << "upfront" << endl;
    }
  }
  return 0;
}