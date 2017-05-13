#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

static const int M = 100005;

int n, m;
int u[M], v[M], a[M], b[M], res[M];

class UnionFind {

private:
  int parent[M], size[M];

public:
  UnionFind() {
    for (int i = 0; i < n; ++i) {
      parent[i] = -1;
      size[i] = 1;
    }
  }

  int find(int i) {
    if (parent[i] == -1) {
      return i;
    }
    return find(parent[i]);
  }

  void merge(int i, int j) {
    int pi = find(i), pj = find(j);
    if (pi == pj) {
      return;
    }
    if (size[pi] < size[pj]) {
      parent[pi] = pj;
      size[pj] += size[pi]; 
    } else {
      parent[pj] = pi;
      size[pi] += size[pj];
    }
  }
};

bool mst(const double& C) {
  vector<pair<double, int> > edges;
  for (int i = 0; i < m; ++i) {
    edges.push_back(make_pair(double(a[i]) - C * double(b[i]), i));
  }
  sort(edges.rbegin(), edges.rend());
  
  UnionFind uf;
  double sum = 0.0;
  for (int i = 0, j = 0; i < m; ++i) {
    int x = u[edges[i].second], y = v[edges[i].second];
    if (uf.find(x) == uf.find(y)) {
      continue;
    }
    uf.merge(x, y);
    sum += edges[i].first;
    res[j++] = edges[i].second;
    if (j == n-1) {
      break;
    }
  }
  return sum >= 0.0;
}

inline double Abs(const double& v) {
  return v > 0.0 ? v : -v;
}

pair<int, int> search() {
  double lo = 0.0, hi = 100.0, mid;
  while (Abs(hi - lo) >= 1e-5) {
    mid = lo + (hi - lo) / 2.0;
    bool good = mst(mid);
    if (good) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  int ac = 0, bc = 0;
  for (int i = 0; i < n-1; ++i) {
    ac += a[res[i]];
    bc += b[res[i]];
  }
  return make_pair(ac, bc);
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    cin >> u[i] >> v[i] >> a[i] >> b[i];
  }
  pair<int, int> res = search();
  int g = __gcd(res.first, res.second);
  cout << (res.first / g) << "/" << (res.second / g) << endl;
  return 0;
}
