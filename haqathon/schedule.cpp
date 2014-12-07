#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstring>
#include <utility>

using namespace std;

int n;
pair<int, double> task[101]; 
bool used[101];

double sol = 0.0;

void dfs(const int& k, const double& val) {
	if (k == n) {
		sol = min(sol, val);
		return;
	}
	for (int i = 0; i < n; ++i) {
		if (!used[i]) {
			used[i] = true;
			dfs(k+1, val * task[i].second + task[i].first);
			used[i] = false;
		}
	}
}

int main() {
	cin >> n;
	int t; double p;
	for (int i = 0; i < n; ++i) {
		cin >> t >> p;
		sol += t;
		task[i] = make_pair(t, p);
	}

	memset(used, false, sizeof(used));
	for (int i = 0; i < n; ++i) {
		used[i] = true;
		dfs(1, task[i].first);
		used[i] = false;
	}
	printf("%0.6f\n", sol);

	return 0;
}