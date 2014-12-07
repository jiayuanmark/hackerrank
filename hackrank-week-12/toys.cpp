#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

bool w[10005];

int main() {
	// input
	int n; cin >> n;
	memset(w, false, sizeof(w));
	int temp;
	for (int i = 0; i < n; ++i) {
		cin >> temp;
		w[temp] = true;
	}

	// scan
	int sol = 0, ptr = 0;
	while (ptr < 10005) {
		if (w[ptr]) {
			++sol;
			ptr += 5; 
		}
		else {
			ptr += 1; 
		}
	}
	cout << sol << endl;

	return 0;
}
