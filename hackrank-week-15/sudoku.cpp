#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int D = 9;
const int DD = 3;
int sudoku[D][D];
int chk[D+1];

struct swp {
  int x1, y1, x2, y2;
  swp (int xx1, int yy1, int xx2, int yy2) 
   : x1(xx1), y1(yy1), x2(xx2), y2(yy2) {}
};

void read () {
  for (int i = 0; i < D; ++i) {
    for (int j = 0; j < D; ++j) {
      cin >> sudoku[i][j];
    }
  }
}

bool verify () {
  // row check
  for (int r = 0; r < D; ++r) {
    memset(chk, 0, sizeof(chk));
    for (int c = 0; c < D; ++c) {
      if (chk[sudoku[r][c]])
        return false;
      chk[sudoku[r][c]] = 1;
    }
  }

  // column check
  for (int c = 0; c < D; ++c) {
    memset(chk, 0, sizeof(chk));
    for (int r = 0; r < D; ++r) {
      if (chk[sudoku[r][c]])
        return false;
      chk[sudoku[r][c]] = 1;
    }
  }

  // square check
  for (int i = 0; i < DD; ++i) {
    for (int j = 0; j < DD; ++j) {
      memset(chk, 0, sizeof(chk));
      for (int r = i * DD; r < (i+1) * DD; ++r) {
        for (int c = j * DD; c < (j+1) * DD; ++c) {
          if (chk[sudoku[r][c]])
            return false;
          chk[sudoku[r][c]] = 1;
        }
      }
    }
  }
  return true;
}

vector<swp> solve() {
  set<pair<int, int> > st;

  // row check
  for (int r = 0; r < D; ++r) {
    memset(chk, 0, sizeof(chk));
    for (int c = 0; c < D; ++c) {
      if (chk[sudoku[r][c]]) {
        st.insert(make_pair(r+1, c+1));
        st.insert(make_pair(r+1, chk[sudoku[r][c]]));
      }
      else {
        chk[sudoku[r][c]] = c+1;
      }
    }
  }

  // column check
  for (int c = 0; c < D; ++c) {
    memset(chk, 0, sizeof(chk));
    for (int r = 0; r < D; ++r) {
      if (chk[sudoku[r][c]]) {
        st.insert(make_pair(r+1, c+1));
        st.insert(make_pair(chk[sudoku[r][c]], c+1));
      }
      else {
        chk[sudoku[r][c]] = r+1;
      }
    }
  }

  // square check
  for (int i = 0; i < DD; ++i) {
    for (int j = 0; j < DD; ++j) {
      memset(chk, 0, sizeof(chk));
      int rofs = i * DD, cofs = j * DD;
      for (int r = rofs; r < rofs + DD; ++r) {
        for (int c = cofs; c < cofs + DD; ++c) {
          if (chk[sudoku[r][c]]) {
            st.insert(make_pair(r+1, c+1));
            st.insert(make_pair(chk[sudoku[r][c]] / D + 1, chk[sudoku[r][c]] % D + 1));
          }
          else {
            chk[sudoku[r][c]] = D * r + c;
          }
        }
      }
    }
  }

  vector<pair<int, int> > pos;
  for (set<pair<int, int> >::iterator it = st.begin(); it != st.end();
    ++it) {
    pos.push_back(*it);
  }
  sort(pos.begin(), pos.end());

  vector<swp> sol;
  for (int i = 0; i < pos.size(); ++i) {
    for (int j = i+1; j < pos.size(); ++j) {
      if (sudoku[pos[i].first-1][pos[i].second-1] == sudoku[pos[j].first-1][pos[j].second-1])
        continue;
      swap(sudoku[pos[i].first-1][pos[i].second-1], sudoku[pos[j].first-1][pos[j].second-1]);
      if (verify ()) {
        sol.push_back(swp(pos[i].first, pos[i].second, pos[j].first, pos[j].second));
      }
      swap(sudoku[pos[i].first-1][pos[i].second-1], sudoku[pos[j].first-1][pos[j].second-1]);
    }
  }
  return sol;
}


int main () {
  int t;
  cin >> t;

  for (int tt = 1; tt <= t; ++tt) {
    read();
    cout << "Case #" << tt << ":" << endl;
    if (verify()) {
      cout << "Serendipity" << endl;
    }
    else {
      vector<swp> soln = solve();
      for (int i = 0; i < soln.size(); ++i) {
        cout << "(" << soln[i].x1 << "," << soln[i].y1 << ") <-> (";
        cout << soln[i].x2 << "," << soln[i].y2 << ")" << endl;
      }
    }
  }

  return 0;
}