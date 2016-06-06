#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
	int k, m, n;
	scanf("%d%d%d", &k, &m, &n);

	vector<int> shoes(m, 0);
	int a;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a);
		++shoes[a];
	}

	vector<pair<int, int> > rank(m);
	for (int i = 0; i < m; ++i) {
		rank[i] = make_pair(shoes[i], -i);
	}
	sort(rank.begin(), rank.end());

	for (int i = 0; i < k; ++i) {
		printf("%d\n", -rank[m-1-i].second);
	}
	return 0;
}