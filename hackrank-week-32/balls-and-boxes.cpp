#include <iostream>

using namespace std;

int n, m;
int A[105], C[105], B[105][105];

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> A[i];
  }
  for (int i = 0; i < m; ++i) {
    cin >> C[i];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> B[i][j];
    }
  }
  
  return 0;
}
