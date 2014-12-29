#include <iostream>
#include <cmath>

using namespace std;

typedef long long LL;

LL powmod(LL a, LL p, LL m) {
	LL ret = 1, mul = a % m;
	while (p) {
		if (p & 1) {
			ret = (ret * mul) % m;
		}
		mul = (mul * mul) % m;
		p >>= 1;
	}
	return ret;
}


int main() {
	int t; cin >> t;
	LL a, m;
	while (t--) {
		cin >> a >> m;
		if (a == 0)
			cout << "YES" << endl;
		else if (m == 2 || powmod(a, m >> 1, m) == 1)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}