#include <iostream>
#include <string>
#include <cmath>

using namespace std;

typedef unsigned long long int LL;

inline LL compute(LL n) {
	return (n * (n+1)/2) * (2*n+1) / 3;
}

LL binarySearch(LL lo, LL hi, const LL& x) {
	while (lo < hi) {
		LL mid = lo + (hi - lo + 1) / 2;
		LL sum = compute(mid);
		if (sum == x) return mid;
		if (sum > x) hi = mid - 1;
		else lo = mid;
	}
	return lo;
}

int main() {
	int t; cin >> t;
	while (t--) {
		LL x; cin >> x;
		cout << binarySearch(1, sqrtl(x), x) << endl;
	}	

	return 0;
}
