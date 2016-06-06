#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

inline LL Max(LL a, LL b) {
	return a > b ? a : b;
}

int main() {
	int t, n;
	cin >> t;
	
	while (t--) {
		cin >> n;
		vector<LL> h(n);
		LL sum = 0;
		for (int i = 0; i < n; ++i) {
			cin >> h[i];
			sum += h[i];
		}
		sort(h.begin(), h.end());
		LL s = 1, sol = 0;
		for (int i = 0; i < n; ++i) {
			sol = Max(sol, s * sum);
			++s;
			sum -= h[i];
		}
		cout << sol << endl;
	}
	return 0;
}