#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <utility>
#include <iostream>
#include <cmath>

using namespace std;

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
			if (p <= a && q <= b) {
				printf("YES\n");
			} else {
				int ssum = p * p + q * q;
				double cmp = double(2 * p * q * a) + (p*p - q*q) * sqrt(ssum - a * a);
				cmp /= ssum;
				if (p > a && b - cmp >= 0) {
					printf("YES\n");
				} else {
					printf("NO\n");
				}
			}
		}
	}

	return 0;
}