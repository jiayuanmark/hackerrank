#include <cstdio>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static const bool notprime[] = { 1, 1, 0, 0, 1, 0, 1, 0, 1, 1 };

int n;
int B[35][35];
vector<int> px, py;
int g[35][35][35][35];

int grundy(int x1, int x2, int y1, int y2) {
	printf("%d %d %d %d\n", x1, x2, y1, y2);
	
	if (x1 >= x2 || y1 >= y2)
		return 0;

	if (g[x1][x2][y1][y2] != -1)
		return g[x1][x2][y1][y2];

	set<int> st;
	for (int i = 0; i < px.size(); ++i) {
		if (px[i] >= x1 && px[i] < x2) {
			if (py[i] >= y1 && py[i] <= y2) {
				st.insert(grundy(x1, px[i]-1, y1, y2) ^ grundy(x1, px[i], y1, y2));
			}
		}

		if (px[i] > x1 && px[i] <= x2) {
			if (py[i] >= y1 && py[i] <= y2) {
				st.insert(grundy(x1, px[i], y1, y2) ^ grundy(x1, px[i]+1, y1, y2));
			}
		}

		if (px[i] >= x1 && px[i] <= x2) {
			if (py[i] >= y1 && py[i] < y2) {
				st.insert(grundy(x1, x2, y1, py[i]-1) ^ grundy(x1, x2, py[i], y2));
			}
		}
		
		if (px[i] >= x1 && px[i] <= x2) {
			if (py[i] > y1 && py[i] <= y2) {
				st.insert(grundy(x1, x2, y1, py[i]) ^ grundy(x1, x2, py[i]+1, y2));
			}
		}
	}

	int &res = g[x1][x2][y1][y2];
	res = 0;
	while (st.count(res) != 0) {
		++res;
	}
	return res;
}

bool solve() {
	memset(g, -1, sizeof(g));
	return grundy(0, n-1, 0, n-1);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		px.clear();
		py.clear();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%d", &B[i][j]);
				if (notprime[B[i][j]]) {
					px.push_back(i);
					py.push_back(j);
				}
			}
		}
		if (solve()) {
			printf("First\n");
		} else {
			printf("Second\n");
		}
	}
	return 0;
}
