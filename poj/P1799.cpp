/*
 * Problem: Yeehaa!
 * http://poj.org/problem?id=1799
 */

#include <cstdio>
#include <cmath>

int main() {
    const double PI = 3.14159265358979;
	int numCases;
	scanf("%d", &numCases);
	for (int caseID = 1; caseID <= numCases; ++caseID) {
		int n;
		double R;
		scanf("%lf %d", &R, &n);
		double r = R / (1.0 + 1.0 / sin(PI / n));
		printf("Scenario #%d:\n%0.3f\n\n", caseID, r);
	}
	return 0;
}
