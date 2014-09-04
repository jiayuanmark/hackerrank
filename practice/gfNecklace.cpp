#include <cstdio>
#include <cstring>

using namespace std;

typedef unsigned long long int LL;

const LL rem = 1000000007;

LL m[3][3];
LL v[3];

void init() {
	memset(m, 0, sizeof(m));
	m[0][0] = 1;
	m[0][2] = 1;
	m[1][0] = 1;
	m[2][1] = 1;

	v[0] = 4;
	v[1] = 3;
	v[2] = 2;
}

void expMatrix() {
	LL temp[3][3];
	memset(temp, 0, sizeof(temp));
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				temp[i][j] = (temp[i][j] + ((m[i][k] * m[k][j]) % rem)) % rem;
			}
		}
	}
	memcpy(m, temp, sizeof(temp));
}


void mulMatrix() {
	LL temp[3];
	memset(temp, 0, sizeof(temp));
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			temp[i] = (temp[i] + ((m[i][j] * v[j]) % rem)) % rem;
		}
	}
	memcpy(v, temp, sizeof(temp));
}


LL compute(LL n) {
	if (n == 1) {
		return 2;
	}

	if (n == 2) {
		return 3;
	}

	if (n == 3) {
		return 4;
	}

	init();
	n -= 3;
	while (n) {
		if (n % 2) mulMatrix();
		expMatrix();
		n >>= 1;
	}
	return v[0];
}


int main() {
	//int t;
	//scanf("%d", &t);
	//while (t--) {
		LL n;
		scanf("%lld", &n);
		printf("%lld\n", compute(n));
	//}
	return 0;
}