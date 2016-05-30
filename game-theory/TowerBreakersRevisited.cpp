#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

int g[1000005];

int grundy(int x) {
	if (g[x] != -1)
		return g[x];

	set<int> st;
	st.insert(0);
	for (int y = 2; y * y <= x; ++y) {
		if (x % y == 0) {
			st.insert(grundy(y));
			st.insert(grundy(x / y));
		}
	}
	int &res = g[x];
	res = 0;
	while (st.count(res) != 0) {
		++res;
	}
	return res;
}

void init() {
	memset(g, -1, sizeof(g));
	g[1] = 0;
}

int main() {
	init();
	int t, n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		int X = 0, tmp;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &tmp);
			X ^= grundy(tmp);
		}
		if (X) {
			printf("1\n");
		} else {
			printf("2\n");
		}
	}
	return 0;	
}
