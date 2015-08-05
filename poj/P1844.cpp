/*
 * Problem: Sum
 * http://poj.org/problem?id=1844
 */

#include <cstdio>

int main() {
    int sum;
    scanf("%d", &sum);
    for (int n = 0;; ++n) {
        int k = n * (n + 1) / 2;
        if (k >= sum && (k - sum) % 2 == 0) {
            printf("%d\n", n);
            break;
        }
    }
    return 0;
}
