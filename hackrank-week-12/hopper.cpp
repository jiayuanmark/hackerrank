#include <iostream>

using namespace std;

int h[100010];

int main() {
	int n; cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> h[i];
	}

	int sol = 0;
	for (int i = n-1; i >= 0; --i) {
		int temp = h[i] + sol;
		sol = temp / 2 + (temp % 2 == 0 ? 0 : 1);
	}
	cout << sol << endl;

	return 0;
}