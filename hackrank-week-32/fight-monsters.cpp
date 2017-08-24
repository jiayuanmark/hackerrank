#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, hit, t;
  cin >> n >> hit >> t;
  vector<int> h(n);
  for (int i = 0; i < n; ++i) {
    cin >> h[i];
    if (h[i] % hit) {
      h[i] = h[i] / hit + 1;
    } else {
      h[i] /= hit;
    }
  }
  sort(h.begin(), h.end());
  int sol = 0;
  for (int i = 0; i < n; ++i) {
    if (h[i] > t) {
      break;
    }
    t -= h[i];
    ++sol;
  }
  cout << sol << endl;
  return 0;
}