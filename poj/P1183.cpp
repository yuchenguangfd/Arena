/*
 * Problem: 反正切函数的应用
 * http://poj.org/problem?id=1183
 */

#include <cstdio>

int main() {
    int a;
    scanf("%d", &a);
    unsigned int tmp = a * a + 1;
    for (int i = a; i >= 1; --i) {
        if (tmp % i == 0) {
            unsigned int min = tmp / i + i + 2 * a;
            printf("%d\n", min);
            break;
        }
    }
    return 0;
}
