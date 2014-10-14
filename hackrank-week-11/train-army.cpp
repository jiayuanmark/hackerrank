#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int N = 500;

int graph[N][N];
bool visited[N];
int parent[N];
int source, sink;

inline void addEdge(const int& u, const int& v) {
	graph[u][v] = 1;
}

inline void removeEdge(const int& u, const int v) {
	graph[u][v]--;
}

bool findAugmentPath() {
	memset(visited, false, sizeof(visited));
	memset(parent, -1, sizeof(parent));

	queue<int> q;
	q.push(source);
	visited[source] = true;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		if (u == sink)
			return true;

		for (int v = 0; v <= sink; ++v) {
			if (graph[u][v] > 0 && !visited[v]) {
				visited[v] = true;
				parent[v] = u;
				q.push(v);
			}
		}
	}
	return false;
}

int maxFlow() {
	int maxflow = 0;
	while (true) {
		bool aug = findAugmentPath();
		if (!aug) break;
		++maxflow;
		// Update residual network
		for (int cur = sink; parent[cur] != -1; cur = parent[cur]) {
			// Add reverse edge
			addEdge(cur, parent[cur]);
			// Remove forward edge
			removeEdge(parent[cur], cur);
		}
	}
	return maxflow;
}

int main () {
	memset(graph, -1, sizeof(graph));
	
	int n, t;
	cin >> n >> t;
	source = 0;
	sink = n + t + 1;
	
	for (int i = 1; i <= n; ++i) {
		cin >> graph[source][i];
		graph[i][sink] = 1;
	}

	int a, b, from, to;
	for (int i = 1; i <= t; ++i) {
		cin >> a;
		while (a--) {
			cin >> from;
			graph[from][n+i] = 1;
		}
		cin >> b;
		while (b--) {
			cin >> to;
			graph[n+i][to] = 1;
		}
	}

	cout << maxFlow() << endl;

	return 0;
}
