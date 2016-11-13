#include <iostream>
#include <cstring>
#include <string>

using namespace std;

string b;
int c[30];

int main() {
  int g, n;
  cin >> g;
  while (g--) {
    cin >> n;
    cin >> b;
    memset(c, 0, sizeof(c));
    bool space = false;
    for (int i = 0; i < n; ++i) {
      if (b[i] == '_') {
        space = true;
      } else {
        ++c[b[i]-'A'];
      }
    }

    bool fail = false;
    if (!space) {
      for (int i = 0; i < n; ++i) {
        if (i > 0 && b[i] == b[i-1])
          continue;
        if (i < n - 1 && b[i] == b[i+1])
          continue;
        cout << "NO" << endl;
        fail = true;
        break;
      }
    } else {
      for (int i = 0; i < 26; ++i) {
        if (c[i] == 1) {
          cout << "NO" << endl;
          fail = true;
          break;
        }
      }
    }
    
    if (!fail) {
      cout << "YES" << endl;
    }
  }
  return 0;
}