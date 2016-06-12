#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <utility>
#include <iostream>
#include <cmath>

using namespace std;

typedef long long LL;

int main() {
	int W, H, n;
	scanf("%d%d", &W, &H);
	int a = max(W, H);
	int b = min(W, H);

	scanf("%d", &n);
	string shape;
	int r, w, h;

	for (int i = 0; i < n; ++i) {
		cin >> shape;
		if (shape == "C") {
			scanf("%d", &r);
			if (2 * r <= b) {
				printf("YES\n");
			} else {
				printf("NO\n");
			}
		} else {
			scanf("%d%d", &w, &h);
			int p = max(w, h);
			int q = min(w, h);
			if (q > b) {
				printf("NO\n");
			} else if (p <= a) {
				printf("YES\n");
			} else {
				LL d1 = LL(p-q)*LL(p-q);
				LL d2 = LL(p+q)*LL(p+q);
				bool can = LL(a+b)*LL(a+b)*d1 + LL(a-b)*LL(a-b)*d2 >= 2*d1*d2;
				if (can) {
					printf("YES\n");
				} else {
					printf("NO\n");
				}
			}
		}
	}

	return 0;
}
