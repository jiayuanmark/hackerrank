#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>

using namespace std;

static const int N = 550000;

typedef pair<int, int> pii;

int n, a[N], s[N];

inline bool isLeaf(const int& x) {
  return x >= n-1;
}

inline int parent(const int& x) {
  return (x - 1) / 2;
}

bool fill(const pii& data, const int& start) {
  int dep = data.first, i;
  for (i = start; dep != 0 && i < 2 * n - 1; 
        i = (i * 2) + 1, ++dep) {
    //cout << i << endl;
    s[i] = data.second;
  }
  return dep == 0 && isLeaf(i);
}

int main() {
  cin >> n;
  map<int, int> f;
  for (int i = 0; i < 2 * n - 1; ++i) {
    cin >> a[i];
    f[a[i]]++;
  }

  priority_queue<pii, vector<pii>, std::greater<pii> > heap;
  for (auto &t : f) {
    heap.push(make_pair(-t.second, t.first));
  }

  vector<pii> pvec;
  for (int pos = 0; !heap.empty(); pos += 2) {
    int p = parent(pos);
    
    pii t;
    while (!heap.empty()) {
      t = heap.top();
      heap.pop();
      if (p == pos || s[p] < t.second) {
        break;
      }
      pvec.push_back(t);
    }

    if (p != pos && s[p] > t.second) {
      cout << "NO" << endl;
      return 0;
    }

    //cout << t.first << " " << t.second << endl;
    if (!fill(t, pos)) {
      cout << "NO" << endl;
      return 0;
    }

    while (!pvec.empty()) {
      heap.push(pvec.back());
      pvec.pop_back();
    }
  }

  cout << "YES" << endl;
  for (int i = 0; i < 2 * n - 1; ++i) {
    cout << s[i] << " ";
  }
  cout << endl;
  return 0;
}
