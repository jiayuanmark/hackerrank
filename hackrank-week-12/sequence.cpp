#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

set<int> graph[1000003];
int indeg[1000003];
bool visited[1000003];
set<int> vertex;
vector<int> sol;

struct node {
	int id, deg;
	node(const int& i, const int& d) : 
		id(i), deg(d) {}
};

bool operator<(const node& a, const node& b) {
	if (a.deg != b.deg) return a.deg > b.deg;
	return a.id > b.id;
}

int main() {
	// input
	memset(indeg, 0, sizeof(indeg));
	
	int n; cin >> n;
	int k;
	for (int i = 0; i < n; ++i) {
		cin >> k;
		int u = -1, v;
		for (int j = 0; j < k; ++j) {
			cin >> v;
			if (u != -1 && graph[u].count(v) == 0) {
				graph[u].insert(v);
				++indeg[v];
			}
			u = v;
			vertex.insert(v);
		}
	}

	// topological sort
	set<int>::iterator it;
	priority_queue<node> q;
	for (it = vertex.begin(); it != vertex.end(); ++it) {
		node n(*it, indeg[*it]);
		q.push(n);
	}

	memset(visited, false, sizeof(visited));
	while (!q.empty()) {
		int deg = q.top().deg;
		int id = q.top().id;
		q.pop();
		if (visited[id]) continue;
		visited[id] = true;
		sol.push_back(id);
		
		for (it = graph[id].begin(); it != graph[id].end(); ++it) {
			if ((--indeg[*it]) == 0) {
				node n(*it, 0);
				q.push(n);
			}
		}
	}

	// output
	for (int i = 0; i < sol.size(); ++i) {
		if (i != sol.size()-1)
			cout << sol[i] << " ";
		else cout << sol[i] << endl;
	}

	return 0;
}
