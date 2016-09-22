#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int R, C, N;
bool B[205][205], Bp[205][205];

void bomb() {
	memset(Bp, false, sizeof(Bp));
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (!B[i][j])
				continue;
			Bp[i][j] = true;
			if (i > 0) {
				Bp[i-1][j] = true;
			}
			if (i + 1 < R) {
				Bp[i+1][j] = true;
			}
			if (j > 0) {
				Bp[i][j-1] = true;
			}
			if (j + 1< C) {
				Bp[i][j+1] = true;
			}
		}
	}

	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			B[i][j] = !Bp[i][j];
		}
	}
}

void printB(char c1, char c2) {
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (B[i][j]) {
				cout << c1;
			} else {
				cout << c2;
			}
		}
		cout << endl;
	}
}

int main() {
	cin >> R >> C >> N;
	string tmp;
	for (int i = 0; i < R; ++i) {
		cin >> tmp;
		for (int j = 0; j < C; ++j) {
			B[i][j] = (tmp[j] == 'O');
		}
	}

	if (N % 2 == 0) {
		string row(C, 'O');
		for (int i = 0; i < R; ++i) {
			cout << row << endl;
		}
		return 0;
	}
	
	if (N % 4 == 3) {
		bomb();
	}

	printB('O', '.');
	return 0;	
}
