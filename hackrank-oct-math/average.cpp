#include <cstdio>

typedef long long LL;

const LL M = 1000000007L;

int main () {
	LL n; scanf("%lld", &n);
	LL res; scanf("%lld", &res);

	LL temp;
	for (LL i = 1; i < n; ++i) {
		scanf("%lld", &temp);
		res = (res + (((temp * res) % M + temp) % M)) % M; 
	}

	printf("%lld\n", res);

	return 0;
}
