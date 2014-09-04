#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

typedef long long LL;

const int table[4][4] = {{0, 1, 2, 3}, {1, 0, 3, 2}, {2, 3, 0, 1}, {3, 2, 1, 0}};

LL n, k;
int s[1000005];

void mutate() {
	int first = s[0];
	for (LL i = 0; i < n-1; ++i) {
		s[i] = table[s[i]][s[i+1]];
	}
	s[n-1] = table[s[n-1]][first];
}



int main() {
	cin >> n >> k;
	char ch;
	for (LL i = 0; i < n; ++i) {
		cin >> ch;
		s[i] = (ch-'A');
	}

	for (LL i = 0; i < k; ++i) {
		mutate();
	}

	for (LL i = 0; i < n; ++i) {
		ch = 'A' + s[i];
		cout << ch;
	}
	cout << endl;

	return 0;
}
