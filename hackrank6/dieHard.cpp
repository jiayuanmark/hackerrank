#include <iostream>
#include <queue>
#include <utility>
#include <cstring>
#include <algorithm>

using namespace std;

typedef pair<int, int> tup;

bool visited[1001][1001];
int T, a, b, c;

void solve() {
    memset(visited, false, sizeof(visited));
    
    if (a == c || b == c) {
        cout << "YES" << endl;
        return;
    }
    
    queue<tup> q;
    visited[a][0] = true;
    visited[0][b] = true;
    q.push(make_pair(a, 0));
    q.push(make_pair(0, b));
    
    while (!q.empty()) {
        tup head = q.front();
        q.pop();
        int ll = head.first, rr = head.second;
        if (ll == c || rr == c)
        {
            cout << "YES" << endl;
            return;
        }

        if (ll == 0 && rr == 0)
            continue;

        // Fill
        if (ll == 0) {
            if (!visited[a][rr]) {
                visited[a][rr] = true;
                q.push(make_pair(a, rr));
            }
            if (!visited[min(rr, a)][0]) {
                visited[min(rr, a)][0] = true;
                q.push(make_pair(min(rr, a), 0));
            }
        }
        
        if (rr == 0) {
            if (!visited[ll][b]) {
                visited[ll][b] = true;
                q.push(make_pair(ll, b));
            }
            if (!visited[0][min(ll, b)]) {
                visited[0][min(ll, b)] = true;
                q.push(make_pair(0, min(ll, b)));
            }
        }
        
        // Left to right
        int lr = min(ll, max(b - rr, 0));
        if (!visited[ll-lr][rr+lr]) {
            visited[ll-lr][rr+lr] = true;
            q.push(make_pair(ll-lr, rr+lr));
        }
        
        // Right to left
        int rl = min(rr, max(a - ll, 0));
        if (!visited[ll+rl][rr-rl]) {
            visited[ll+rl][rr-rl] = true;
            q.push(make_pair(ll+rl, rr-rl));
        }

        // Empty
        if (!visited[0][rr]) {
            visited[0][rr] = true;
            q.push(make_pair(0, rr));
        }

        if (!visited[ll][0]) {
            visited[ll][0] = true;
            q.push(make_pair(ll, 0));
        }
    }
    
    cout << "NO" << endl;
}


int main() {
    cin >> T;
    while (T--) {
        cin >> a >> b >> c;
        solve();
    }
    return 0;
}