#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int R, C, r, c;
string grid[1005], pat[1005];
int hist[1005][1005];

bool solve(const int& sum) {
	for (int i = 0; i+r-1 < R; ++i) {
		for (int j = 0; j+c-1 < C; ++j) {
			int bot = i+r-1, rht = j+c-1;
			int check = hist[bot][rht];
			if (i >= 1) {
				check -= hist[i-1][rht];
			}
			if (j >= 1) {
				check -= hist[bot][j-1];
			}
			if (i >= 1 && j >= 1) {
				check += hist[i-1][j-1];
			}

			if (check == sum) {
				bool match = true;
				for (int k = 0; k < r; ++k) {
					for (int l = 0; l < c; ++l) {
						if (grid[i+k][j+l] != pat[k][l]) {
							match = false;
							break;
						}
					}
					if (!match) break;
				}
				if (match) return true;
			}
		}
	}
	return false;
}

int main() {
	int t; cin >> t;
	while (t--) {
		memset(hist, 0, sizeof(hist));

		// Grid
		cin >> R >> C;
		for (int i = 0; i < R; ++i) {
			cin >> grid[i];
			for (int j = 0; j < C; ++j) {
				hist[i][j] += (grid[i][j] - '0');
				if (i >= 1) {
					hist[i][j] += hist[i-1][j];
				}
				if (j >= 1) {
					hist[i][j] += hist[i][j-1];
				}
				if (i >= 1 && j >= 1) {
					hist[i][j] -= hist[i-1][j-1];
				}
			}
		}


		// Pattern
		int sum = 0;
		cin >> r >> c;
		for (int i = 0; i < r; ++i) {
			cin >> pat[i];
			for (int j = 0; j < c; ++j) {
				sum += (pat[i][j] - '0');
			}
		}

		// Solve
		bool res = solve(sum);
		if (res) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}