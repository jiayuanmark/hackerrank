#include <iostream>
#include <cmath>
#include <cstring>
#include <utility>
#include <vector>

using namespace std;

typedef long long LL;

int n, a[55];
vector<pair<LL, int> > divisor;

LL gcd(const LL& a, const LL& b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

LL lcm(const LL& a, const LL& b) {
	return (a * b) / gcd(a, b);
}

void computeLcm() {
	int bits = (1 << n) - 1;
	for (int i = 1; i <= bits; ++i) {
		LL mult = 1L;
		int mask = 1;
		for (int j = 0; j < n; ++j) {
			if (mask & i) {
				mult = lcm(mult, a[j]);
			}
			mask <<= 1;
		}
		divisor.push_back(make_pair(mult, __builtin_popcount(i)));
	}
}

LL up(const LL& l, const LL& i) {
	if (l % i == 0) return l / i;
	return (l+i) / i;
}


LL down(const LL& l, const LL& i) {
	return l / i;
}

LL solve(const LL& l, const LL& r) {
	LL res = 0L;
	for (int i = 0; i < divisor.size(); ++i) {
		LL div = divisor[i].first;
		LL val = down(r, div) - up(l, div) + 1;
		if (divisor[i].second % 2) {
			res += val;
		}
		else {
			res -= val;
		}
	}
	return res;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	computeLcm();

	int t; cin >> t; 
	LL l, r;
	while (t--) {
		cin >> l >> r;
		cout << solve(l, r) << endl;
	}
	return 0;
}
