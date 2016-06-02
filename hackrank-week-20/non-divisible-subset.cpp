#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

vector<int> mk[105];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  
  int temp;
  for (int i = 0; i < n; ++i) {
  	scanf("%d", &temp);
  	mk[temp % k].push_back(temp);
  }

  int sol = 0;
  for (int i = 1; i * 2 < k; ++i) {
  	sol += max(mk[i].size(), mk[k - i].size());
  }
  if (k % 2 == 0 && mk[k / 2].size() > 0) {
    ++sol;
  }
  if (mk[0].size() > 0 || mk[k].size() > 0) {
    ++sol;
  }
  printf("%d\n", sol);
  return 0;
}