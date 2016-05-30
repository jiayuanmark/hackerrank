#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int peg[5];
int dp[12][12][12][12];

int f(int i, int j, int k, int l) {
	if (dp[i][j][k][l] != -1)
		return dp[i][j][k][l];
	int &res = dp[i][j][k][l];
	
}

int main() {
	int n, tmp;
	scanf("%d", &n);

	memset(peg, 0, sizeof(peg));
	for (int i = 0; i < n; ++i) {
		scanf("%d", &tmp);
		peg[tmp]++;
	}
	memset(dp, -1, sizeof(dp));
	dp[peg[1]][peg[2]][peg[3]][peg[4]] = 0;




	return 0;
}
