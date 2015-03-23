#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>

using namespace std;

bool orderFunc(const pair<int, double> &lhs, const pair<int, double> &rhs) {
	return (lhs.first / (1. - lhs.second)) > (rhs.first / (1. - rhs.second));
}

int main() {
	int n;
	cin >> n;
	int t; double p;

	vector<pair<int,double> > tasks;
	for (int i = 0; i < n; ++i) {
		cin >> t >> p;
		tasks.push_back(make_pair(t, p));
	}

	sort(tasks.begin(), tasks.end(), orderFunc);

	double sol = tasks[0].first;
	for (int i = 1; i < n; ++i) {
		sol = (sol * tasks[i].second) + tasks[i].first;
	}
	printf("%0.6f\n", sol);

	return 0;
}
