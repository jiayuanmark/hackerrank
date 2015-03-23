#include <iostream>
#include <cstring>

using namespace std;

int bld[2000][2000], dp[2000][2000], cpt[2000];

int main() {
	memset(bld, 0, sizeof(bld));
	memset(dp, 0, sizeof(dp));
	memset(cpt, 0, sizeof(cpt));

	int h, n, ii;
	cin >> n >> h >> ii;

	int cnt, temp;
	for (int i = 0; i < n; ++i) {
		cin >> cnt;
		while (cnt--) {
			cin >> temp;
			++bld[temp][i]; 
		}
	}

	for (int i = 0; i <= h; ++i) {
		for (int j = 0; j < n; ++j) {
			dp[i][j] = (i > 0 ? dp[i-1][j] : 0);
			if (i >= ii) {
				dp[i][j] = max(dp[i][j], cpt[i-ii]);
			}
			dp[i][j] += bld[i][j];
			cpt[i] = max(dp[i][j], cpt[i]);
		}
	}

	cout << cpt[h] << endl;
	return 0;
}
