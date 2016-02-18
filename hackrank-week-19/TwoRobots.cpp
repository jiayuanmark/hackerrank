#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

static const int INF = 2 * 1e6;
static const int N = 1005;
int table[N][N];
int x[N], y[N];
int m, n;

void init(const int& m) {
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= m; ++j) {
            table[i][j] = INF;
        }
    }
}

int sol(const int& m) {
    int res = INF;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            res = min(res, INF);
        }
    }
    return res;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &m, &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &x[i], &y[i]);
        }

        init(m);
        for (int i = 1; i <= m; ++i) {
            table[i][y[0]] = table[y[0]][i] = abs(x[0] - y[0]);
        }

        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= m; ++j) {
                for (int k = 1; k <= m; ++k) {
                    if (j == y[i]) {
                        table[j][k] = mi1;
                    } else if (k == y[i])
                }
            }
        }


    }
    return 0;
}
