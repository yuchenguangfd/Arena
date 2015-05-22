/*
 * Problem: Count on Canton
 * http://poj.org/problem?id=1969
 */
#include <cstdio>

int main() {
    while (true) {
        int n;
        if (scanf("%d", &n) == EOF) break;
        int i = 1;
        while (i * (i + 1) / 2 < n) ++i;
        --i;
        int m = n - i * (i + 1) / 2;
        ++i;
        int a, b;
        if (i % 2 == 0) {
            a = m;
            b = i + 1 - m;
        } else {
            a = i + 1 - m;
            b = m;
        }
        printf("TERM %d IS %d/%d\n", n, a, b);
    }
    return 0;
}
