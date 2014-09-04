#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const long long MOD = 1000000007;

string Reverse(const string& s) {
	string ret(s);
	char* content = const_cast<char*>(ret.c_str());
	int N = s.length();
	for (int i = N/2-1; i >= 0; --i) {
		char temp = content[i];
		content[i] = content[N-1-i];
		content[N-1-i] = temp;
	}
	return ret;
}


string SingleMultiply(const string& revnum, const char& ch) {
	string ret = "";
	int carrier = 0;
	for (int i = 0; i < revnum.length(); ++i) {
		int temp = (revnum[i]-'0') * (ch-'0') + carrier;
		ret += static_cast<char>((temp%10)+'0');
		carrier = temp / 10;
	}
	if (carrier) ret += static_cast<char>(carrier+'0');
	return ret;
}


string LargeAddition(const string& n1, const string& n2) {
	string result = "";
	int carrier = 0;
	for (int i = 0; i < min(n1.length(), n2.length()); ++i) {
		int temp = (n1[i]-'0') + (n2[i]-'0') + carrier;
		result += static_cast<char>((temp%10)+'0');
		carrier = temp / 10;
	}
	string n = n1.length() > n2.length() ? n1 : n2;
	for (int i = min(n1.length(), n2.length()); i < n.length(); ++i) {
		int temp = (n[i]-'0') + carrier;
		result += static_cast<char>((temp%10)+'0');
		carrier = temp / 10;
	}
	if (carrier) result += static_cast<char>(carrier+'0');
	return result;
}

string LargeMultiply(const string& n1, const string& n2) {
	string r1 = Reverse(n1), r2 = Reverse(n2);
	string ret = SingleMultiply(r1, r2[0]);
	string pad = "0";
	for (int i = 1; i < r2.length(); ++i) {
		ret = LargeAddition(ret, pad + SingleMultiply(r1, r2[i]));
		pad += "0";
	}
	return Reverse(ret);
}


long long LargeModular(const string& num) {
	long long ret = 0;
	for (int i = 0; i < num.length(); ++i) {
		ret = ((ret*10) % MOD + (num[i]-'0')) % MOD;
	}
	return ret;
}

long long LargeExp(const long long& num, int p) {
	long long ret = 1, prod = num % MOD;
	while (p) {
		if (p & 1) ret = (ret * prod) % MOD;
		prod = (prod * prod) % MOD;
		p >>= 1;
	}
	return ret;
}


int main() {
	long long cache[10];
	int N; cin >> N;
	string A, B;

	for (int i = 0; i < N; ++i) {
		cin >> A >> B;

		long long base = LargeModular(A);
		cache[0] = 1;
		for (int k = 1; k < 10; ++k) {
			cache[k] = (cache[k-1] * base) % MOD;
		}
		
		long long ans = 1;
		for (int k = 0; k < B.length(); ++k) {
			ans = (LargeExp(ans, 10) * cache[B[k]-'0']) % MOD;
		}
		cout << ans << endl;
	}

    return 0;
}
