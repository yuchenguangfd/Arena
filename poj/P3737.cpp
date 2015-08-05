/*
 * Problem: UmBasketella
 * http://poj.org/problem?id=3737
 */

#include <cmath>
#include <cstdio>

int main() {
    const double PI = 3.141592653589793;
    double S, R, H, V;
    while (scanf("%lf", &S) != EOF) {
        R = sqrt(S / PI) / 2;
        H = sqrt(2 * S / PI);
        V = PI * R * R * H / 3.0;
        printf("%.2f\n%.2f\n%.2f\n",V, H, R);
    }
    return 0;
}
