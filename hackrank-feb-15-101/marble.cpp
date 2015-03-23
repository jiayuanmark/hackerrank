#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

int main() {
    int t;
    cin >> t;
    
    LL l, b;
    while (t--) {
        cin >> l >> b;
        LL ans = ((l%3)*(b%3)) % 3;
        if (ans == 0)
            cout << "YES" << endl;
        else if (l > 3 && b > 3)
            cout << "NO " << ans << endl;
        else
            cout << "NO " << (l%3)*(b%3) << endl; 
    }
    return 0;
}