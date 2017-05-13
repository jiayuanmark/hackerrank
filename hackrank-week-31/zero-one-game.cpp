#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int g, n;
bool s[100005];

bool solve() {
  int cnt = 0;
  vector<bool> buf;
  buf.push_back(s[0]);
  for (int i = 1; i < n-1; ++i) {
    if (s[i] && !buf.back() && !s[i+1]) {
      ++cnt;
    } else {
      buf.push_back(s[i]);
    }
  }
  buf.push_back(s[n-1]);

  for (int i = 1; i < buf.size() - 1; ++i) {
    if (!buf[i-1] && !buf[i+1]) {
      ++cnt;
    }
  }
  return cnt % 2;
}

int main() {
  cin >> g;
  while (g--) {
    cin >> n;
    for (int i = 0; i < n; ++i) {
      cin >> s[i];
    }
    if (solve()) {
      cout << "Alice" << endl;
    } else {
      cout << "Bob" << endl;
    }
  }
  return 0;
}