#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

typedef long long LL;

const int maxn = 100005;

vector<int> d[maxn];
vector<LL> pos[maxn]; 
LL sol[maxn];

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; i * j <= n; ++j) {
			d[i * j].push_back(i);
		}
	}

	int temp;
	for (LL i = 0; i < n; ++i) {
		scanf("%d", &temp);
		for (int j = 0; j < d[temp].size(); ++j)
			pos[d[temp][j]].push_back(i);
	}

	for (LL i = 1; i <= n; ++i) {
		vector<LL> ind = pos[i];
		LL lhs = ind[0];
		int idx = 1;

		while (true) {
			if (idx >= ind.size()) {
				sol[i] += (ind[idx-1] - lhs + 1) * (ind[idx-1] - lhs + 2) / 2;
				break;
			}

			if (ind[idx] == ind[idx-1] + 1)
				++idx;
			else {			
				sol[i] += (ind[idx-1] - lhs + 1) * (ind[idx-1] - lhs + 2) / 2;
				lhs = ind[idx];
				++idx;
			}
		}
	}



	int q, k;
	scanf("%d", &q);
	while (q--) {
		scanf("%d", &k);
		printf("%lld\n", sol[k]);
	}
	
	return 0;
}