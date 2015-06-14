#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int n;
vector<pair<int, int> > people;

bool chk(const int& num) {
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    if (cnt >= num) return true;
    if (num - 1 >= people[i].first
        && num - 1 <= people[i].second) {
      ++cnt;
    }
  }
  return (cnt >= num);
}

int main() {
  int lhs, rhs;
  
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> lhs >> rhs;
    people.push_back(make_pair(lhs, rhs));
  }

  int lo = 1, hi = n;
  while (lo < hi) {
    int mid = lo + (hi - lo + 1) / 2;
    if (chk(mid)) {
      lo = mid;
    }
    else {
      hi = mid - 1;
    }
  }
  cout << lo << endl;

  return 0;
}