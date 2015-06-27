/*
 * Problem: Gold Coins
 * http://poj.org/problem?id=2000
 */

#include <cmath>
#include <cstdio>

int main() {
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        double x = (sqrt(1 + 8.0 * n) - 1) / 2;
        int i = (int) floor(x);
        int sum = i * (i + 1) * (2 * i + 1) / 6;
        if (x - i > 1e-2) {
            int m = (1 + i) * i / 2;
            sum += (n - m) * (i + 1);
        }
        printf("%d %d\n", n, sum);
    }
    return 0;
}
