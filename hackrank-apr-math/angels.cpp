#include <cstdio>
#include <cmath>

using namespace std;

int p[105][3];

double angle(const int& i,
						 const int& j,
						 const int& k) {
	int x1 = p[i][0] - p[j][0];
	int y1 = p[i][1] - p[j][1];
	int z1 = p[i][2] - p[j][2];
	int x2 = p[k][0] - p[j][0];
	int y2 = p[k][1] - p[j][1];
	int z2 = p[k][2] - p[j][2];

	int dot = x1 * x2 + y1 * y2 + z1 * z2;
	double d1 = sqrt(x1 * x1 + y1 * y1 + z1 * z1);
	double d2 = sqrt(x2 * x2 + y2 * y2 + z2 * z2);
	return acos(dot / (d1 * d2));
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d%d", &p[i][0], &p[i][1], &p[i][2]);
	}

	double sum = 0.0;
	int tot = n * (n-1) * (n-2) / 6;
	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			for (int k = j+1; k < n; ++k) {
				//printf("%d %d %d %0.10lf\n", i+1, j+1, k+1, angle(i, j, k));
				sum += angle(i, j, k);
			}
		}
	} 
	printf("%.15lf\n", sum / tot);

	return 0;
}