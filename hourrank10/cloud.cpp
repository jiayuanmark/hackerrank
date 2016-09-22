#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool c[30];

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		cin >> c[i];
	}

	int e = 100, i = 0;
	while (true) {
		i = (i + k) % n;
		--e;
		if (c[i]) {
			e -= 2;
		}
		if (i == 0)
			break;
	}
	cout << e << endl;

	return 0;	
}
