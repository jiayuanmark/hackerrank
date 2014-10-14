#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

vector<LL> strange;

LL pow10(LL n) {
	LL ret = 1L, mult = 10L;
	while (n) {
		if (n & 1) {
			ret = ret * mult;
		}
		mult = mult * mult;
		n >>= 1;
	}
	return ret;
}

int main() {
	for (LL i = 0; i <= 9; ++i) {
		strange.push_back(i);
	}

	for (LL i = 2; i <= 18; ++i) {
		LL lo = pow10(i-1);
		LL hi = lo * 10 - 1;
		int pos = lower_bound(strange.begin(), strange.end(), lo / i) - strange.begin();
		vector<LL> level;
		bool over = false;
		LL sclr = i;
		while (true) {
			for (int i = pos; i < strange.size(); ++i) {
				LL val = strange[i] * sclr;
				if (val > hi) {
					over = true;
					break;
				}
				level.push_back(val);
			}
			if (over) break;
			sclr *= i; 
		}
		strange.insert(strange.end(), level.begin(), level.end());
	}

	int t; cin >> t;
	LL l, r;
	vector<LL>::iterator liter, riter;
	while (t--) {
		cin >> l >> r;
		liter = lower_bound(strange.begin(), strange.end(), l);
		riter = upper_bound(strange.begin(), strange.end(), r);
		cout << riter - liter << endl;
	}
	return 0;
}