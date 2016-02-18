#include <iostream>
#include <stack>
#include <utility>

using namespace std;

int main() {
  int n;
  cin >> n;

  int p, sol = 0;
  stack<pair<int, int> > st;
  for (int i = 0; i < n; ++i) {
    cin >> p;
    
    if (st.empty()) {
      st.push(make_pair(p, 0));
    } else {
      if (p > st.top().first) {
        st.push(make_pair(p, 1));
        sol = max(sol, 1);
        //cout << p << ": " << 1 << endl; 
        continue;
      }

      int mx = 0;
      while (!st.empty()) {
        pair<int, int> t = st.top();
        if (p > t.first) {
          break;
        }
        mx = max(mx, t.second);
        st.pop();
      }
      
      if (st.empty()) {
        st.push(make_pair(p, 0));
        //cout << p << ": " << 0 << endl; 
      } else {
        st.push(make_pair(p, mx+1));
        //cout << p << ": " << mx+1 << endl;
        sol = max(sol, mx+1);
      }
    }
  }
  cout << sol << endl;

  return 0;
}