/*
 * Problem: Goldbach's Conjecture
 * http://poj.org/problem?id=2262
 */

#include <cmath>
#include <cstdio>

bool IsPrime(int n) {
    if(n <= 1) return false;
    if(n == 2) return true;
    if((n & 1) == 0) return false;
    int limit = (int)sqrt(static_cast<double>(n));
    for(int t = 3; t <= limit; t += 2) {
        if(n % t == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        int limit = n / 2;
        for (int i = 3; i <= limit; i += 2) {
            if (IsPrime(i) && IsPrime(n - i)) {
                printf("%d = %d + %d\n", n, i, n - i);
                break;
            }
        }
    }
    return 0;
}
