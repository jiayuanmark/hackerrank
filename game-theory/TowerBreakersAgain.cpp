#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

int g[100005];

int grundy(int x) {
	if (g[x] != -1)
		return g[x];

	set<int> st;
	st.insert(0);
	for (int z = 2; z < x; ++z) {
		if (x % z == 0 && ((x / z) % 2)) {
			st.insert(grundy(z));
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
		int X = 0, h;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &h);
			X ^= grundy(h);
		}
		if (X) {
			printf("1\n");
		} else {
			printf("2\n");
		}
	}
	return 0;	
}
