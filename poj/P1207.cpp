/*
 * Problem: The 3n + 1 problem
 * http://poj.org/problem?id=1207
 */

#include <algorithm>
#include <cstdio>

int countCycle(int x) {
    int steps = 1;
    while(x != 1) {
        if(x % 2 == 1) {
            x = 3 * x + 1;
            ++steps;
        } else {
          x /= 2;
          ++steps;
        }
    }
    return steps;
}

int main() {
    int i, j;
    while(scanf("%d %d", &i, &j) != EOF) {
        int s = std::min(i, j);
        int t = std::max(i, j);
        int maxCycle = 0;
        for(int n = s; n <= t; ++n) {
            int k = countCycle(n);
            maxCycle = std::max(maxCycle, k);
        }
        printf("%d %d %d\n", i, j, maxCycle);
    }
    return 0;
}
