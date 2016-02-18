#include <iostream>
#include <cstring>

using namespace std;

int n, m;
int x, d;
int arr[50005];

void solve() {
  memset(arr, 0, sizeof(arr));

  int lhs = 1, rhs = n;
  for (int i = 0; i < m; ++i) {
    if (i % 2 == 0) {
      x = lhs;
      d = arr[lhs];
  	  arr[lhs++]++;
  	} else {
  	  x = rhs;
  	  d = arr[rhs];
  	  arr[rhs--]++;
  	}
    if (lhs > rhs) {
  		lhs = 1;
  		rhs = n;
  	}
  }
}


int main() {
  int t;
  cin >> t;
  while (t--) {
  	cin >> n >> m;
  	solve();
  	cout << x << " " << d << endl;
  }
}