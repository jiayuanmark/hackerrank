#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

typedef long long LL;

const int MAXVAL = 2000005;
int tree[MAXVAL];

inline LL mmin(const LL& n1, const LL& n2) {
	return n1 < n2 ? n1 : n2;
}

inline LL mmax(const LL& n1, const LL& n2) {
	return n1 > n2 ? n1 : n2;
}

void update(int idx, int val) {
	while (idx <= MAXVAL) {
		tree[idx] += val;
		idx += (idx & -idx);
	}
}

int read(int idx) {
	int ret = 0;
	while (idx > 0) {
		ret += tree[idx];
		idx -= (idx & -idx);
	}
	return ret;
}

int main() {
	int n, m;
	cin >> n;

	int temp;
	memset(tree, 0, sizeof(tree));
	for (int i = 0; i < n; ++i) {
		cin >> temp;
		update(temp, 1);
	}

	LL x1, y1, x2, y2, sol = 0l;
	LL sqr1, sqr2;

	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> x1 >> y1 >> x2 >> y2;
		sqr1 = x1 * x1 + y1 * y1;
		sqr2 = x2 * x2 + y2 * y2;
		int inner = floor(sqrt(static_cast<double>(mmin(sqr1, sqr2))));
		int outer = floor(sqrt(static_cast<double>(mmax(sqr1, sqr2))));
		if (inner >= outer) continue;
		sol += (read(outer) - read(inner));
	}
	cout << sol << endl;

	return 0;
}
