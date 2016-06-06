#include <iostream>

using namespace std;

int B[1005];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> B[i];
	}


		int sol = 0;
		bool done;
		for (int ctr = 0; ctr < 2 * n; ++ctr) {
			done = true;
			for (int i = 0; i < n; ++i) {
				if (B[i] % 2) {
					done = false;
					B[i] += 1;
					if (i + 1 >= n) {
						B[i-1] += 1;
					} else {
						B[i+1] += 1;
					}
					sol += 2;
					break;
				}
			}
			if (done) {
				break;
			}
		}
		if (done) {
			cout << sol << endl;
		} else {
			cout << "NO" << endl;
		}
	return 0;
}