#include <iostream>

using namespace std;

typedef long long LL;

LL s[105];

int main() {
	int t, n;
	cin >> t;
	while (t--) {
		cin >> n;
		LL X = 0;
		int twoOrLarger = 0;
		for (int i = 0; i < n; ++i) {
			cin >> s[i];
			X ^= s[i];
			if (s[i] > 1) {
				++twoOrLarger;
			}
		}
		if (twoOrLarger == 0) {
			if (n % 2) {
				cout << "Second" << endl;
			} else {
				cout << "First" << endl;
			}
		} else {
			if (X) {
				cout << "First" << endl;
			} else {
				cout << "Second" << endl;
			}
		}
	}
	return 0;	
}
