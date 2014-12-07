#include <iostream>
#include <cmath>

using namespace std;

typedef long long LL;

LL bigPowMod(LL a, LL b, LL x) {
	LL res = 1L, mult = a % x;
	while (b) {
		if (b & 1) {
			res = (res * mult) % x; 
		}
		mult = (mult * mult) % x;
		b >>= 1;
	}
	return res;
}

LL inverseMod(LL a, LL x) {
	LL t = 0, newt = 1;
	LL r = x, newr = a;
	LL q, temp;
	while (newr) {
		q = r / newr;
		
		temp = t - q * newt;
		t = newt;
		newt = temp;

		temp = r % newr;
		r = newr;
		newr = temp;
	}
	if (t < 0) {
		t = t + x;
	}
	return t;
}

int main () {
	int t; cin >> t;
	LL a, b, x;
	while (t--) {
		cin >> a >> b >> x;
		if (b == 0) {
			cout << "1" << endl;
		}
		else {
			LL sol = bigPowMod(a, abs(b), x);
			if (b > 0) cout << sol << endl;
			else cout << inverseMod(sol, x) << endl;
		}
	}
	return 0;
}
