#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <utility>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> Pair;

int main() {
	int n;
	scanf("%d", &n);

	priority_queue<Pair> Q;
	int type;
	LL p, t;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &type);
		if (type == 1) {
			scanf("%lld%lld", &p, &t);
			Q.push(make_pair(p, t));
		} else {
			scanf("%lld", &t);
			while (!Q.empty()) {
				Pair cur = Q.top();
				if (cur.second <= t - 60) {
					Q.pop();
				} else {
					break;
				}
			}
			if (Q.empty()) {
				printf("-1\n");
			} else {
				printf("%lld\n", Q.top().first);
			}
		}
	}

	return 0;
}