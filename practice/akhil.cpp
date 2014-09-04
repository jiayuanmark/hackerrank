#include <iostream>

using namespace std;

typedef long long LL;

LL pow(LL n, LL m) {
	LL mul = 10, ret = 1;
	while (n) {
		if (n % 2) ret = (ret * mul) % m;
		mul = (mul * mul) % m;
		n >>= 1;
	}
	return ret;
}

LL solve(LL n, LL m) {
	if (n == 1) {
		return 1;
	}
	if (n == 2) {
		return (11 % m);
	}
	if (n == 3) {
		return (111 % m);
	}
	LL sub = solve(n/2, m), ret;
	if (n % 2) {
		LL temp = ((pow(n/2, m) * sub) % m + sub) % m;
		return (((temp * 10) % m + 1) % m);
	}
	else {
		return (((pow(n/2, m) * sub) % m + sub) % m);
	}
}

int main() {
	LL t;
	cin >> t;

	while (t--) {
		LL n, m;
		cin >> n >> m;
		cout << solve(n, m) << endl;
	}
	return 0;	
}
