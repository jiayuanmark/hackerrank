#include <iostream>
#include <algorithm>

using namespace std;

int q, n;
int a[100005];

bool sorted() {
  for (int i = 1; i < n; ++i) {
    if (a[i-1] > a[i])
      return false;
  }
  return true;
}


int main() {
  cin >> q;
  while (q--) {
    cin >> n;
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    for (int i = 1; i < n; ++i) {
      if (a[i-1] - a[i] == 1) {
        swap(a[i-1], a[i]);
      }
    }
    if (sorted()) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
  return 0;
}