#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

static const int MX = 100005;

bool div3[MX];
ll cnt3[MX];

inline bool even(const char& c) {
  return (c == '0') || (c == '2') || (c == '4') || 
         (c == '6') || (c == '8');
}

int main() {
  string s;
  cin >> s;
  int n = s.length();

  ll sol = 0ll, acc = 0ll;
  for (int i = 0; i < n; ++i) { 
    acc += (s[i] - '0');
    acc %= 3;
    div3[i] = (acc == 0);
  }

  ll c = 0ll;
  for (int i = 0; i < n; ++i) {
    cnt3[i] = c;
    if (div3[i]) {
      ++c;
    }
  }

  for (int i = 0; i < n; ++i) {
    if (even(s[i]) && div3[i]) {
      sol += (cnt3[i] + 1ll);
    }
  }

  c = 0ll;
  for (int i = n-1; i >= 0; --i) {
    
  }

  cout << sol << endl;
  return 0;
}