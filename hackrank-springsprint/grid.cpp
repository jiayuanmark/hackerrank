#include <iostream>
#include <cstring>

using namespace std;

int m, n;
bool visited[15][15];
bool table[15][15];

int dfs(const int& r, const int& c) {
	if (visited[r][c] || !table[r][c])
		return 0;

	visited[r][c] = true;
	int cnt = 1;
	if (r > 0)   cnt += dfs(r-1, c);
	if (r < m-1) cnt += dfs(r+1,c);
	if (c > 0)   cnt += dfs(r, c-1);
	if (c < n-1) cnt += dfs(r, c+1);

	if (r > 0 && c > 0)
		cnt += dfs(r-1, c-1);
	if (r > 0 && c < n-1)
		cnt += dfs(r-1, c+1);
	if (r < m-1 && c > 0)
		cnt += dfs(r+1, c-1);
	if (r < m-1 && c < n-1)
		cnt += dfs(r+1, c+1);
	
	return cnt;
}


int main() {
	memset(visited, false, sizeof(visited));
	memset(table, false, sizeof(table));

	cin >> m >> n;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> table[i][j];
		}
	}

	int sol = 0;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (table[i][j] && !visited[i][j])
				sol = max(sol, dfs(i, j));
		}
	}

	cout << sol << endl;
	return 0;
}
