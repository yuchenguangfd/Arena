/*
 * Problem: Perfect Cubes
 * http://poj.org/problem?id=1543
 */

#include <cmath>
#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);
    for (int a = 2; a <= n; ++a) {
        for (int b = 2; b <= a; ++b) {
            for (int c = b; c <= a; ++c) {
                int x = a * a * a - b * b * b - c * c * c;
                if (x > 0) {
                    double tmp = pow(x, 1.0 / 3);
                    int d = (int) (tmp + 0.5);
                    if (d * d * d == x && d >= c)
                        printf("Cube = %d, Triple = (%d,%d,%d)\n", a, b, c, d);
                }
            }
        }
    }
    return 0;
}
