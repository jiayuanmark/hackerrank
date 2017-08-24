#include <iostream>
#include <iomanip>

using namespace std;

inline int digit_sum(const int& d) {
  return (d / 100 + (d % 100) / 10 + (d % 10));
}

int main() {
  int x, lo, hi;
  cin >> x;
  x++;
  lo = x % 1000;
  hi = x / 1000;
  for (; hi <= 999; ++hi) {
    int tmp = digit_sum(hi);
    for (; lo <= 999; ++lo) {
      if (digit_sum(lo) == tmp) {
        cout << hi << setfill('0') << setw(3) << lo << endl;
        return 0;
      }
    }
    lo = 0;
  }
  return 0;
}