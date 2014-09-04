#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long LL;

LL a[100005];

LL solve(const int& n) {
	if (n % 2 == 0) return 0L;
	LL ans = 0L;
	for (int i = 0; i < n; ++i) {
		if (i % 2 == 0) ans ^= a[i]; 
	}
	return ans;
}


int main() {
	int t; cin >> t; 
	while (t--) {
		int n; cin >> n;
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
		}
		cout << solve(n) << endl;
	}
	return 0;
}