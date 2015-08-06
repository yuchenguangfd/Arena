/*
 * Problem: Probability One
 * http://poj.org/problem?id=3994
 */

#include <cstdio>

int main() {
    int numCase = 0;
    while (true) {
        int n0;
        scanf("%d", &n0);
        if (n0 == 0) break;
        printf("%d. %s %d\n", ++numCase, (n0 & 1) ? "odd" : "even", n0 / 2);
    }
    return 0;
}
