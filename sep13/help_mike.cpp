#include <iostream>

using namespace std;

inline int max(const int &num1, const int &num2) {
	return num1 > num2 ? num1 : num2;
}

int main() {
	long long T, N, K, ans;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		cin >> N >> K;

		long long mul = 2 * N / K;

		ans = 0;
		long long item, upper, lower;
		for (int i = 1; i <= mul; ++i) {
			item = i * K;
			
			if (item % 2 == 0)
				upper = item / 2 - 1;
			else
				upper = item / 2;

			lower = max(1, item - N);
			ans = ans + (upper - lower + 1);
		}
		cout << ans << endl;
	}

	return 0;
}
