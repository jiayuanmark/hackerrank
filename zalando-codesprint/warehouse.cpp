#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int W, B, P;
int warehouse[20][15];
int query[15], check[15];

bool verify() {
	for (int i = 0; i < P; ++i) {
		if (query[i] > check[i])
			return false;
	}
	return true;
}

void solve() {
	int sol = W + 1;
	for (int i = 1; i < (1 << W); ++i) {
		memset(check, 0, sizeof(check));
		for (int j = 0; j < W; ++j) {
			if (i & (1 << j)) {
				for (int k = 0; k < P; ++k) {
					check[k] += warehouse[j][k];
				}
			}
		}
		if (verify()) {
			sol = min(sol, __builtin_popcount(i));
		}
	}
	if (sol == W + 1) {
		printf("-1\n");
	} else {
		printf("%d\n", sol);
	}
}

int main() {
	scanf("%d%d%d", &W, &B, &P);
	for (int i = 0; i < W; ++i) {
		for (int j = 0; j < P; ++j) {
			scanf("%d", &warehouse[i][j]);
		}
	}

	for (int i = 0; i < B; ++i) {
		for (int j = 0; j < P; ++j) {
			scanf("%d", &query[j]);
		}
		solve();
	}
	return 0;
}