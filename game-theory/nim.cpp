#include <iostream>

using namespace std;

int main() {
	int t, n, s, tmp;
	cin >> t;
	while (t--) {
		cin >> n;
		cin >> s;
		for (int i = 1; i < n; ++i) {
			cin >> tmp;
			s ^= tmp;
		}
		if (s) {
			cout << "First" << endl;
		} else {
			cout << "Second" << endl;
		}
	}
	return 0;	
}
