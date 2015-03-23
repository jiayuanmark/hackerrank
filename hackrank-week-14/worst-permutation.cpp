#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 100005;

int num[N], pos[N];
priority_queue<int> q;

int main() {
	int n, k;
	cin >> n >> k;

	for (int i = 0; i < n; ++i) {
		cin >> num[i];
		pos[num[i]] = i;
		q.push(num[i]);
	}

	int pt = 0;
	while (!q.empty() && k != 0) {
		int mx = q.top();
		q.pop();
		if (pos[mx] == pt) {
			++pt;
			continue;
		}
		--k;
		int temp = num[pt];
		num[pt] = mx;
		num[pos[mx]] = temp;
		pos[temp] = pos[mx];
		++pt;
	}

	for (int i = 0; i < n-1; ++i) {
		cout << num[i] << " ";
	}
	cout << num[n-1] << endl;


	return 0;
}
