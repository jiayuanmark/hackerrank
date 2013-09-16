#include <cstdio>
#include <cstring>

using namespace std;

char S[1000005];
int ones[1000005];

inline long long max(const long long& num1, const long long& num2) {
	return num1 > num2 ? num1 : num2;
}

inline long long min(const long long& num1, const long long& num2) {
	return num1 < num2 ? num1 : num2;
}


int main() {
	long long K, N;
	scanf("%lld %s", &K, S);
	N = strlen(S);

	long long num = 0;
	ones[0] = 0;
	for (long long i = 0; i < N; ++i) {
		if (S[i] == '1') ++num;
		ones[i] = num;
	}

	if (2 * N <= 5 * num) {
		printf("%lld\n", K * N);
		return 0;
	}

	long long LL = N * min(1, K), ans = 0, count;
	for (long long i = 0; i + ans < LL; ++i) {
		for (long long j = max(i+1, i+ans-1); j < LL; ++j) {
			count = num * (j / N - (i-1) / N) + ones[j%N];
			count -= (i == 0 ? 0:ones[(i-1)%N]);
			if (2 * (j-i+1) <= 5 * count)
				ans = max(ans, j-i+1);
		}
	}
	printf("%lld\n", ans);


	return 0;
}
