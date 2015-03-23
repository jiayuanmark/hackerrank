#include <string>
#include <iostream>

using namespace std;

int cnt[200005];

int main() {
	string s;
	cin >> s;

	for (int i = s.length()-1; i >= 0; --i) {
		if (s[i] == 'I')
			cnt[i] = cnt[i+1] + 1;
		else
			cnt[i] = 0;
	}

	int cur = s.length()+1, mi = s.length()+1;
	for (int i = 0; i < s.length(); ++i) {
		cout << cur - cnt[i] << " ";
		mi = min(mi, cur - cnt[i] - 1);
		if (cnt[i] == 0)
			cur = mi;
	}
	cout << cur << endl;

	return 0;
}
