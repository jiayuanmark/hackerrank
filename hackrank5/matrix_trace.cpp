#include <cstdio>

long long MOD = 1000000007;

long long solve(long long N, long long K) {
   long long res = 1;
   for (long long i = 1; i <= K; ++i) {
        res *= N--;
        res /= K;
     }
    return res % MOD;
}

long long min(const long long &n1, const long long &n2) {
   return n1 < n2 ? n1 : n2;
}

int main() {
   int T;
   scanf("%d", &T);

   long long M, N;
   for (int i = 0; i < T; ++i) {
      scanf("%llu %llu", &M, &N);
      printf("%llu", solve(M+N-2, min(M, N)-1));
   }
   return 0;
}