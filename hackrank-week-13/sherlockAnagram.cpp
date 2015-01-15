#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

int cc[26];
string s;

string signature() {
	stringstream ss;
	for (int i = 0; i < 26; ++i) {
		ss << cc[i];
	}
	return ss.str();
}

int solve() {
	unordered_map<string, int> indx;
	int sol = 0;
	for (int ln = 1; ln < s.length(); ++ln) {
		memset(cc, 0, sizeof(cc));
		indx.clear();

		int i;
		for (i = 0; i < ln; ++i) {
			++cc[s[i]-'a'];
		}

		for (i = ln; i < s.length(); ++i) {
			string sig = signature();
			if (indx.count(sig) != 0) {
				sol += indx[sig];
			}
			indx[sig]++;
			++cc[s[i]-'a'];
			--cc[s[i-ln]-'a'];
		}

		string sig = signature();
		if (indx.count(sig) != 0) {
			sol += indx[sig];
		}
	}
	return sol;
}

int main() {
	int t;
	cin >> t;

	while (t--) {
		cin >> s;
		cout << solve() << endl;
	}

	return 0;
}
