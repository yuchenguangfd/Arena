/*
 * Problem: Dirichlet's Theorem on Arithmetic Progressions
 * http://poj.org/problem?id=3006
 */

#include <cmath>
#include <cstdio>

bool IsPrime(int n) {
    if(n <= 1) return false;
    if(n == 2) return true;
    if((n & 1) == 0) return false;
    int limit = (int)sqrt(static_cast<double>(n));
    for(int t = 3; t <= limit; t += 2)
        if(n % t == 0) {
            return false;
        }
    return true;
}

int main() {
    while (true) {
        int a, d, n;
        scanf("%d %d %d", &a, &d, &n);
        if (a == 0 && d == 0 && n == 0) break;
        int count = 0;
        for (int i = 0;; ++i) {
            int x = a + d * i;
            if (IsPrime(x)) {
                ++count;
                if (count == n) {
                    printf("%d\n", x);
                    break;
                }
            }
        }
    }
    return 0;
}
