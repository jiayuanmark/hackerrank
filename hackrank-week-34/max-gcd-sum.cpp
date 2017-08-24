#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int n, tmp, A, B;
bool cntA[1000005], cntB[1000005];
map<int, int> mark;

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> tmp;
    cntA[tmp] = true;
    A = max(A, tmp);
  }

  for (int i = 0; i < n; ++i) {
    cin >> tmp;
    cntB[tmp] = true;
    B = max(B, tmp);
  }

  for (int d = 1; d <= A; ++d) {
    for (int i = 1; i * d <= A; ++i) {
      if (cntA[i * d]) {
        mark[d] = max(mark[d], i * d);
      }
    }
  }

  int gcd = 0, ans = 0; 
  for (auto iter = mark.begin(); iter != mark.end(); ++iter) {
    int d = iter->first;
    for (int i = 1; i * d <= B; ++i) {
      if (cntB[i * d]) {
        if (d > gcd) {
          gcd = d;
          ans = iter->second + i * d;
        } else if (d == gcd) {
          ans = max(iter->second + i * d, ans);
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}