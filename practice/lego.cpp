#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007;
int t;
LL n, m;
LL f[1005], g[1005];

LL pow(LL num, LL p) {
	LL ret = 1;
	while (p) {
		if (p % 2) {
			ret = (ret * num) % MOD;
		}
		num = (num * num) % MOD;
		p >>= 1;
	}
	return ret;
}


LL solve(const LL &n, const LL &m) {
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	
	f[0] = 1;
	for (int i = 1; i <= m; ++i) {
		if (i >= 1) f[i] = (f[i]+f[i-1]) % MOD;
		if (i >= 2) f[i] = (f[i]+f[i-2]) % MOD;
		if (i >= 3) f[i] = (f[i]+f[i-3]) % MOD;
		if (i >= 4) f[i] = (f[i]+f[i-4]) % MOD;
	}

	for (int i = 1; i <= m; ++i) {
		f[i] = pow(f[i], n);
	}

	for (int i = 1; i <= m; ++i) {
		g[i] = f[i];
		for (int j = 1; j < i; ++j) {
			LL temp = (g[j] * f[i-j]) % MOD;
			g[i] = (g[i]-temp + MOD) % MOD;
		}
	}
	return g[m];
}






int main() {
	cin >> t;
	while (t--) {
		cin >> n >> m;
		cout << solve(n, m) << endl;
	}

	return 0;
}
