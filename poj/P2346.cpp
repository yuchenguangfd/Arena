/*
 * Problem: Lucky tickets
 * http://poj.org/problem?id=2346
 */

#include <cstdio>

int main() {
    const int ans[] = {0, 10, 670, 55252, 4816030, 432457640};
    int n;
    scanf("%d", &n);
    printf("%d\n", ans[n/2]);
    return 0;
}
