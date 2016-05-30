#include <cstdio>

using namespace std;

typedef long long LL;

LL c[105];

int main() {
	int t, n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		LL X = 0L;
		for (int i = 0; i < n; ++i) {
			scanf("%lld", &c[i]);
			if (i != 0 && c[i] % 2 == 1) {
				X ^= i;
			}
		}
		if (X) {
			printf("First\n");
		} else {
			printf("Second\n");
		}
	}
	return 0;	
}
