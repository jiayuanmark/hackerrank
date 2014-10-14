#include <iostream>
#include <string>
#include <cstring>

using namespace std;

typedef long long LL;

const int md = 100003;

LL n, k;
int dp[3][100010];
int C[100010];
LL fact[100010];

inline LL ulimit(const LL& n) {
	return (n / 2 + (n % 2)); 
}

LL solveSmall(const LL& n, const LL& k) {
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	dp[0][1] = 1;
	for (LL i = 1; i <= n; ++i) {
		for (LL j = 0; j <= min(ulimit(i), k); ++j) {
			dp[i%3][j] = dp[(i+2)%3][j];
			if (i >= 2 && j >= 1) {
				dp[i%3][j] = (dp[i%3][j] + dp[(i+1)%3][j-1]) % md;
			}
		}
	}
	return dp[n%3][k];
}

void precomputeFactorial() {
	fact[0] = 1L;
	for (int i = 1; i < md; ++i) {
		fact[i] = (fact[i-1] * i) % md;
	}
}

LL dpbinom(const LL& m, const LL& n) {
	memset(C, 0, sizeof(C));
	C[0] = 1;
	for (int i = 1; i <= m; ++i) {
		for (int j = n; j >= 1; --j) {
			C[j] = (C[j] + C[j-1]) % md;
		}
	}
	return C[n];
}

LL powmod(const LL& base, LL expo) {
	LL ret = 1, mult = base;
	while (expo) {
		if (expo & 1) {
			ret = (ret * mult) % md;
		}
		mult = (mult * mult) % md;
		expo >>= 1;
	}
	return ret;
}

LL closebinom(const LL& m, const LL& n) {
	if (n > m) return 0;
	LL numer = fact[m];
	LL denom = (fact[m-n] * fact[n]) % md;
	denom = powmod(denom, md-2);
	return (numer * denom) % md;
}

LL solve(LL n, LL k) {
	n = n - k + 1;
	LL ret = 1L;
	while (n || k) {
		ret = (ret * closebinom(n % md, k % md)) % md;
		n /= md;
		k /= md;
	}
	return ret;
}


int main() {
	precomputeFactorial();
	int t; cin >> t;
	while (t--) {
		cin >> n >> k;
		if (k > ulimit(n)) {
			cout << "0" << endl;
		}
		else {
			cout << solve(n, k) << endl;
		}
	}

	return 0;
}