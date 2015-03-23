#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

typedef long long LL;

LL solve () {
	int n;
	LL m, temp, sol = 0l;
	cin >> n >> m;
	set<LL> left;
	LL pred = 0l;
	for (int i = 0; i < n; ++i) {
		cin >> temp;
		pred = (pred + temp) % m;
		sol = max(sol, pred);
		set<LL>::iterator it = left.lower_bound(pred+1);
		if (it != left.end()) {
			sol = max(sol, m + pred - (*it));
		}
		left.insert(pred);
	}
	return sol;
}


int main () {
	int t;
	cin >> t;

	while (t--) {
		cout << solve() << endl;
	}
	return 0;
}
