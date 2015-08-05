/*
 * Problem: Eva's Problem
 * http://poj.org/problem?id=1658
 */

#include <cstdio>

int main() {
    int numCase;
    scanf("%d", &numCase);
    while (numCase--) {
        int a1, a2, a3, a4, a5;
        scanf("%d %d %d %d", &a1, &a2, &a3, &a4);
        if (a1 + a3 == 2 * a2 && a2 + a4 == 2 * a3) {
            a5 = a4 * 2 - a3;
        } else {
            a5 = a4 * a4 / a3;
        }
        printf("%d %d %d %d %d\n", a1, a2, a3, a4, a5);
    }
    return 0;
}
