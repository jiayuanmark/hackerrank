#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

static const int numOfStks = 3;

int n[numOfStks];
vector<int> stk[numOfStks];
int sum[numOfStks];

inline bool stop() {
	return (sum[0] == sum[1]) && (sum[1] == sum[2]);
}

inline int choose() {
	int mm = max(max(sum[0], sum[1]), sum[2]);
	for (int i = 0; i < numOfStks; ++i) {
		if (sum[i] == mm)
			return i;
	}
	return 0;
}

int main() {
	memset(sum, 0, sizeof(sum));

	cin >> n[0] >> n[1] >> n[2];

	for (int i = 0; i < numOfStks; ++i) {
		stk[i].resize(n[i]);
		for (int j = 0; j < n[i]; ++j) {
			cin >> stk[i][j];
			sum[i] += stk[i][j];
		}
		reverse(stk[i].begin(), stk[i].end());
	}

	while (!stop()) {
		int ix = choose();
		sum[ix] -= stk[ix].back();
		stk[ix].pop_back();
	}

	cout << sum[0] << endl;

	return 0;
}
