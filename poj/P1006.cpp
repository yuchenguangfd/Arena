/*
 * Problem: Biorhythms
 * http://poj.org/problem?id=1006
 */

#include <cstdio>

int main() {
    int a = 5544;
    int b = 14421;
    int c = 1288;
    int n = 21252;
    int caseID = 0;
    while (true) {
        int p, e, i, d;
        scanf("%d %d %d %d", &p, &e, &i, &d);
        if (p == -1 && e == -1 && i == -1 && d == -1) break;
        int ans = (p * a + e * b + i * c) % n - d;
        if (ans <= 0) ans += n;
        printf("Case %d"": the next triple peak occurs in %d"" days.\n", ++caseID, ans);
    }
    return 0;
}

