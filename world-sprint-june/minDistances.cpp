#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	int n;
	cin >> n;

	map<int, int> ix;
	bool dup = false;
	int sol = n, tmp;
	for (int i = 0; i < n; ++i) {
		cin >> tmp;
		if (ix.count(tmp) != 0) {
			dup = true;
			sol = min(sol, i - ix[tmp]);
		}
		ix[tmp] = i;
	}

	if (dup) {
		cout << sol << endl;
	} else {
		cout << -1 << endl;
	}

	return 0;
}
