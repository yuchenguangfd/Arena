/*
 * Problem: Beavergnaw
 * http://poj.org/problem?id=2405
 */

#include <cmath>
#include <cstdio>

int main() {
    const double PI = 3.14159265358979;
	while (true) {
		double D, V;
		scanf("%lf %lf", &D, &V);
		if (D == 0 && V == 0) break;
		double d = pow(pow(D, 3.0) - 6.0 * V / PI, 1.0 / 3) ;
		printf("%.3f\n", d);
	}
	return 0;
}
