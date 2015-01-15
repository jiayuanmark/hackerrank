#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;

const int N = 200005;

LL tree[N];
LL a[N];

void set(int x, LL val) {
	tree[x] = val;
	a[x] = val;
}

void update(int x, LL val) {
	while (x <= N) {
		tree[x] += val;
		x += (x & -x);
	}
}

LL read(int x) {
	LL ret = 0l;
	while (x > 0) {
		ret += tree[x];
		x -= (x & -x);
	}
	return ret;
}

void updateRange(const int& l, const int& r) {
	LL temp, diff;
	for (int i = l; i <= r; i += 2) {
		diff = a[i+1] - a[i];
		temp = a[i];
		a[i] = a[i+1];
		a[i+1] = temp;
		update(i+1, -diff);
		update(i, diff);
	}
}

LL answerRange(const int& l, const int& r) {
	return (read(r) - read(l-1));
}

int main() {
	int n, q;
	cin >> n >> q;

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		update(i, a[i]);
	}

	int type, l, r;
	while (q--) {
		cin >> type >> l >> r;
		if (type == 1) {
			updateRange(l, r);
		}
		else {
			cout << answerRange(l, r) << endl;
		}
	}

	return 0;
}