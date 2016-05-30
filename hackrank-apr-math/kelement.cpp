#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int N = 2000001;
static const LL MOD = 1e9 + 7;
LL fac[N];

LL inverse(const LL& a) {
	LL r = MOD, newr = a;
	LL t = 0, newt = 1;
	LL q, temp;
	while (newr != 0) {
		q = r / newr;
		temp = r - q * newr;
		r = newr;
		newr = temp;
		temp = t - q * newt;
		t = newt;
		newt = temp;
	}
	return t < 0 ? t + MOD : t;
}

void process() {
	fac[1] = 1;
	for (LL i = 2; i < N; ++i) {
		fac[i] = (fac[i-1] * i) % MOD;
	}
}

LL solve(const LL& n, const LL& k) {
	if (k == n || k == 0)
		return 1;
	LL res = ((fac[n] * inverse(fac[n - k])) % MOD * inverse(fac[k])) % MOD;
	return res;
}

int main() {
	process();
	int t;
	scanf("%d", &t);
	LL n, k;
	while (t--) {
		scanf("%lld%lld", &n, &k);
		printf("%lld\n", solve(n-1, k-1));
	}
	return 0;
}