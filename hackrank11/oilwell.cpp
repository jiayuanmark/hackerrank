#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


struct node {
	int x, y;
	node (const int& xx, const int& yy) : x(xx), y(yy) {}
};


inline void swap(node& n1, node& n2) {
	node tmp = n1;
	n1 = n2;
	n2 = tmp;
}

inline int dist(const node& n1, const node& n2) {
	return max(abs(n1.x-n2.x), abs(n1.y-n2.y)); 
}


vector<node> nvec;
int sol = -1;

void perm(const int& depth) {
	if (depth == nvec.size()) {
		int ans = 0;
		for (int i = 1; i < nvec.size(); ++i) {
			int dst = 0;
			for(int j = 0; j < i; ++j) {
				if (dist(nvec[i], nvec[j]) > dst)
					dst = dist(nvec[i], nvec[j]);
			}
			ans += dst;
		}
		if (sol == -1 || ans < sol) sol = ans;
	}
	for (int i = depth; i < nvec.size(); ++i) {
		swap(nvec[i], nvec[depth]);
		perm(depth+1);
		swap(nvec[i], nvec[depth]);
	}
}



int main() {
    int nrows, ncols;
    cin >> nrows >> ncols;
	
	// input    
    bool oil;
    for (int i = 1; i <= nrows; ++i) {
    	for (int j = 1; j <= ncols; ++j) {
    		cin >> oil;
    		if (oil) {
    			node n(i, j);
    			nvec.push_back(n);
    		}
    	}
    }

    // permutation
    perm(0);

    // output
    cout << sol << endl;


    return 0;
}
