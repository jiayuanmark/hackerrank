#include <iostream>
#include <string>

using namespace std;

typedef long long LL;

const LL M = 100L;

LL x[101];

LL bigpow(LL a, LL b) {
	LL res = 1L;
	while (b) {
		if (b & 1) res = (res * a) % M;
		a = (a * a) % M;
		b >>= 1;
	}
	return res;
}

void sumofpowers(LL n) {
	x[0] = 0L;
	LL acc = 0L;
	for (LL i = 1; i <= 100; ++i) {
		acc = (acc + bigpow(i, n)) % M;
		x[i] = acc;
	}
}

LL solve(LL k, LL n) {
	sumofpowers(n);
	return ((x[100] * ((k/100) % M)) % M + x[k%100]) % M;
}

int main() {
	int t; cin >> t;
	LL k, n;
	while (t--) {
		cin >> k >> n;
		LL sol = solve(k, n);
		if (sol < 10) {
			cout << "0";
		}
		cout << sol << endl;
	}


	return 0;
}
