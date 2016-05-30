#include <iostream>

using namespace std;

typedef long long LL;

LL c[105];

int main() {
	int t, n, k;
	cin >> t;
	while (t--) {
		cin >> n >> k;
		LL X = 0L;
		for (int i = 0; i < n; ++i) {
			cin >> c[i];
			X ^= c[i];
		}
		if (X) {
			cout << "First" << endl;
		} else {
			cout << "Second" << endl;
		}
	}

	return 0;
}
