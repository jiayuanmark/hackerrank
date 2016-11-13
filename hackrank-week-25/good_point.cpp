#include <iostream>
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

using namespace std;

typedef pair<double, double> Point;

int n, m;

inline double distance(const Point& p1,
                       const Point& p2) {
  double dx = p1.first - p2.first;
  double dy = p1.second - p2.second;
  return sqrt(dx * dx + dy * dy);
}

class Shape {
public:
  virtual bool contains(const Point& p);
};

class Polygon : public Shape {
private:
  vector<Point> _vertices;

  inline int sgn(const double& v) {
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
  }

  inline double dot_product(const Point& p1,
                            const Point& p2) {
    return p1.first * p2.first + p1.second * p2.second;
  }

public:
  Polygon(const vector<Point>& vertices)
    : _vertices(vertices) {}

  bool contains(const Point& p) {
    int sn = 0;
    for (int i = 1; i < _vertices.size(); ++i) {
      Point l = make_pair(
        _vertices[i].first - _vertices[i-1].first,
        _vertices[i].second - _vertices[i-1].second);

      int res = sgn(dot_product(l, p));
      if (res == 0) continue;
      if (sn == 0) {
        sn = res;
      } else if (sn * res < 0) {
        return false;
      } else {
        sn = res;
      }
    }
    return
  }
};

class Ellipse : public Shape {
private:
  Point _f1, _f2;
  double _a;
public:
  Ellipse(const Point& f1,
          const Point& f2,
          const double& a)
    : _f1(f1), _f2(f2), _a(2 * a) {} 

  bool contains(const Point& p) {
    return distance(p, _f1) + distance(p, _f2) <= _a;
  }
}

int main() {
  cin >> n >> m;
  vector<Shape> shapes;
  int v, x, y;
  for (int i = 0; i < n; ++i) {
    cin >> v;
    vector<Point> vertices;
    for (int j = 0; j < v; ++j) {
      cin >> x >> y;
      vertices.push_back(make_pair(x, y));
    }
  }

  return 0;
}