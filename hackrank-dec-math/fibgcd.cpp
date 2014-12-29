#include <iostream>
#include <cmath>
#include <cstring>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long LL;

const LL MOD = (1e9 + 7);

inline void powerMod(LL m[4]) {
	LL temp[4];
	temp[0] = ((m[0]*m[0]) % MOD + (m[1]*m[2]) % MOD) % MOD;
	temp[1] = ((m[0]*m[1]) % MOD + (m[1]*m[3]) % MOD) % MOD;
	temp[2] = ((m[2]*m[0]) % MOD + (m[3]*m[2]) % MOD) % MOD;
	temp[3] = ((m[2]*m[1]) % MOD + (m[3]*m[3]) % MOD) % MOD;
	m[0] = temp[0];
	m[1] = temp[1];
	m[2] = temp[2];
	m[3] = temp[3];
}

inline void matVecMul(LL m[4], LL v[2]) {
	LL temp[2];
	temp[0] = ((m[0]*v[0])%MOD+(m[1]*v[1])%MOD) % MOD;
	temp[1] = ((m[2]*v[0])%MOD+(m[3]*v[1])%MOD) % MOD;
	v[0] = temp[0];
	v[1] = temp[1];
}

LL gcd(const LL& a, const LL& b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

LL fib(LL n) {
	LL mat[4] = {1,1,1,0};
	LL vec[2] = {0,1};
	while (n) {
		if (n & 1)
			matVecMul(mat, vec);
		n >>= 1;
		powerMod(mat);
	}
	return vec[0];
}


int main() {
	int n; cin >> n;
	LL a, f, sol = -1;
	while (n--) {
		cin >> a;
		f = fib(a);
		if (sol == -1) {
			sol = f;
		}
		else {
			sol = gcd(sol>f?sol:f, sol<f?sol:f);
		}
		if (sol == 1) {
			break;
		}
	}
	cout << sol << endl;
	return 0;
}