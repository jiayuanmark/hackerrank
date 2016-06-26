#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>

using namespace std;

static const char hexChars[17] = "0123456789ABCDEF";
static const int N = 50005;

int K;
string ha, hb, hc;
int a[N], b[N];

inline int fromHex(char hex) {
	if (hex >= '0' && hex <= '9')
		return int(hex - '0');
	if (hex >= 'A' && hex <= 'F')
		return 10 + int(hex - 'A');
	return 10 + int(hex - 'a');
}

inline char toHex(int num) {
	return hexChars[num];
}

void normalize() {
	int n = max(max(ha.length(), hb.length()), hc.length());
	while (ha.length() < n) {
		ha = '0' + ha;
	}
	while (hb.length() < n) {
		hb = '0' + hb;
	}
	while (hc.length() < n) {
		hc = '0' + hc;
	}
}

int flipB(int ix, int target) {
	int res = 0;
	for (int i = 15; i >= 0; --i) {
		if (target & (1 << i)) {
			if (!(a[ix] & (1 << i)) && !(b[ix] & (1 << i))) {
				b[ix] |= (1 << i);
				++res;
			}
		} else {
			if (a[ix] & (1 << i)) {
				a[ix] ^= (1 << i);
				++res;
			}
			if (b[ix] & (1 << i)) {
				b[ix] ^= (1 << i);
				++res;
			}
		}
	}
	return res;
}

int padB(int ix, int target, int quota) {
	int res = 0;
	for (int i = 15; i >= 0; --i) {
		if (target & (1 << i)) {
			if ((res + 1) <= quota && (a[ix] & (1 << i)) && (b[ix] & (1 << i))) {
				++res;
				a[ix] ^= (1 << i);
			}

			if ((res + 2) <= quota && (a[ix] & (1 << i)) && !(b[ix] & (1 << i))) {
				res += 2;
				a[ix] ^= (1 << i);
				b[ix] ^= (1 << i);
			}

			if (res == quota)
				return res;
		}
	}
	return res;
}

void printSol() {
	int i;
	for (i = 0; i < ha.length() && a[i] == 0; ++i) {}
	if (i == ha.length()) {
		cout << 0 << endl;
	} else {
		for (; i < ha.length(); ++i) {
			cout << toHex(a[i]);
		}
		cout << endl;
	}
	for (i = 0; i < hb.length() && b[i] == 0; ++i) {}
	if (i == hb.length()) {
		cout << 0 << endl;
	} else {
		for (; i < hb.length(); ++i) {
			cout << toHex(b[i]);
		}
		cout << endl;
	}
}

void solve() {
	normalize();
	int n = ha.length();
	int bitCount = 0;
	for (int i = 0; i < n; ++i) {
		a[i] = fromHex(ha[i]);
		b[i] = fromHex(hb[i]);
		bitCount += flipB(i, fromHex(hc[i]));
		if (bitCount > K) {
			cout << -1 << endl;
			return;
		}
	}

	int rest = K - bitCount;
	for (int i = 0; i < n && rest != 0; ++i) {
		int nops = padB(i, fromHex(hc[i]), rest);
		rest -= nops;
	}
	printSol();
}

int main() {
	int q;
	cin >> q;
	while (q--) {
		cin >> K;
		cin >> ha >> hb >> hc;
		solve();
	}
	return 0;
}
