#include <iostream>
#include <string>

using namespace std;



int main() {
	int t, n;
	cin >> t;
	
	while (t--) {
		cin >> n;
		for (int i = 0; i * 2 <= n; ++i) {
			cout << i << " " << n-i << endl;
			if (i * 2 != n) {
				cout << n-i << " " << i << endl;
			}
		}
	}

	return 0;
}
