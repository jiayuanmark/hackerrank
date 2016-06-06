#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <utility>

using namespace std;

typedef long long LL;

inline LL Min(LL a, LL b) {
	return a < b ? a : b;
}

int main() {
	LL n, w, l, h;
	scanf("%lld%lld%lld%lld", &n, &w, &l, &h);

	LL a1 = w * l, a2 = w * h, a3 = h * l;
	LL sol = 2 * n * (a1 + a2 + a3);
	vector<LL> p;
	p.push_back(a1);
	p.push_back(a2);
	p.push_back(a3);
	for (LL i = 1; i <= n; ++i) {
		for (LL j = 1; i * j <= n; ++j) {
			LL k = n / (i * j);
			if (k * i * j < n) {
				++k;
			}
			sort(p.begin(), p.end());
			do {
				sol = Min(sol, 2 * (p[0] * i * j + p[1] * i * k + p[2] * j * k));
			} while (next_permutation(p.begin(), p.end()));
		}
	}
	printf("%lld\n", sol);
	return 0;
}