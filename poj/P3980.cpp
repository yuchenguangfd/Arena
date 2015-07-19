/*
 * Problem: 取模运算
 * http://poj.org/problem?id=3980
 */

#include <stdio.h>

int main() {
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF) {
        printf("%d\n", a % b);
    }
    return 0;
}
