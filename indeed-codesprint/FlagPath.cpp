#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

static const int N = 100005;

vector<int> graph[N];

int main() {
    int n, e, p;
    cin >> n >> e >> p;

    int u, v;
    for (int i = 0; i < e; ++i) {
    	cin >> u >> v;
    	graph[u].push_back(v);
    	graph[v].push_back(u);
    }

    


    return 0;
}
