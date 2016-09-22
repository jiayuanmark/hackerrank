#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long long LL;

int main() {
  LL x, y, a, b;
  cin >> x >> y >> a >> b;

  LL l = a*a + b*b, d1 = a*x + b*y, d2 = -b*x + a*y;
  cout << setprecision(10) << double(d1) / l << endl;
  cout << setprecision(10) << double(d2) / l << endl;

  return 0;
}