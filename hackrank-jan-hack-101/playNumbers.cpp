#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

vector<LL> num;

inline LL myabs(const LL& num) {
	return num > 0 ? num : -num;
}

int main () {
	int n, q;
	scanf("%d", &n);
	
	LL temp, sol = 0l;
	for (int i = 0; i < n; ++i) {
		scanf("%lld", &temp);
		num.push_back(temp);
		sol += myabs(temp);
	}

	sort(num.begin(), num.end());
	
	LL p = 0l;
	vector<LL> pred;
	for (int i = 0; i < num.size(); ++i) {
		p += num[i];
		pred.push_back(p);
	}

	LL inc = 0l;
	scanf("%d", &q);
	
	vector<LL>::iterator zero, ofs, it;
	for (int i = 0; i < q; ++i) {
		scanf("%lld", &temp);
		inc += temp;

		LL diff = 0l;
		int lft, rht;
		if (inc > 0) {
			zero = lower_bound(num.begin(), num.end(), 0);
			ofs = lower_bound(num.begin(), num.end(), -inc);
			lft = ofs - num.begin();
			rht = zero - num.begin();
			diff += 2 * (pred[rht-1] - (lft == 0 ? 0 : pred[lft-1]));
			diff += (zero - ofs) * inc;
			diff += (num.end() - zero) * inc;
			diff -= (ofs - num.begin()) * inc;
		}
		else if (inc < 0) {
			LL mv = -inc;
			zero = upper_bound(num.begin(), num.end(), 0);
			ofs = upper_bound(num.begin(), num.end(), mv);
			lft = zero - num.begin();
			rht = ofs - num.begin();
			diff -= 2 * (pred[rht-1] - (lft == 0 ? 0 : pred[lft-1]));
			diff += (ofs - zero) * mv;
			diff += (zero - num.begin()) * mv;
			diff -= (num.end() - ofs) * mv;
		}
		printf("%lld\n", sol + diff);
	}


	return 0;
}
