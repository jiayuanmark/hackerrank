#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector<int> d;

inline int gcd(const int& a, const int& b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

void solve() {
	d.clear();
	scanf("%d%d", &n, &k);
	int temp;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &temp);
		if (temp % k == 0)
			d.push_back(temp / k);
	}

	if (d.size() == 0) {
		printf("NO\n");
		return;
	} 

	int sol = d[0];
	for (int i = 1; i < d.size(); ++i) {
		sol = gcd(max(sol, d[i]), min(sol, d[i]));
	}

	if (sol == 1)
		printf("YES\n");
	else
		printf("NO\n");
}

int main() {
	int t;
	scanf("%d", &t);

	while (t--) {
		solve();
	}

	return 0;
}