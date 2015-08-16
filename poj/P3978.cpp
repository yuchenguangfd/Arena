/*
 * Problem: Primes
 * http://poj.org/problem?id=3978
 */

#include <cstdio>
#include <cmath>

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

int main(int argc, char **argv) {
    while (true) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a == -1 && b == -1) break;
        int countPrime = 0;
        for (int n = a; n <= b; ++n) {
            if (IsPrime(n))    ++countPrime;
        }
        printf("%d\n", countPrime);
    }
}
