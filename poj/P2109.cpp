/*
 * Problem: Power of Cryptography
 * http://poj.org/problem?id=2109
 */

#include <cmath>
#include <cstdio>

int main() {
    double n, p;
    while (scanf("%lf%lf", &n, &p) != EOF) {
        printf("%0.0f\n", pow(p, 1.0 / n));
    }
    return 0;
}
