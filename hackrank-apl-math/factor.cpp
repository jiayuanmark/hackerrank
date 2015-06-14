#include <iostream>
#include <string>

using namespace std;

typedef long long LL;

const int maxp = 2000000;
int prime[maxp+1];
LL res = 0;

void sieve() {
	for (int i = 2; i * i <= maxp; ++i) {
		if (prime[i]) continue;
		for (int j = i; j * i <= maxp; ++j) {
			prime[j * i] = i;
		}
	}
}

void solve(int n) {
	//cout << "---" << endl;
	//cout << n << endl;
	while (prime[n] != 0) {
		//cout << prime[n] << endl;
		res += prime[n];
		n /= prime[n];
	}

	if (n != 0 && n != 1) {
		//cout << n << endl;
		res += n;
	}
}


int main () {
	int t, n;
	sieve();
	cin >> t;

	while (t--) {
		cin >> n;
		solve(n);
	}
	//cout << "---" << endl;
	cout << res << endl;

	return 0;
}