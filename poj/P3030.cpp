/*
 * Problem: Nasty Hacks
 * http://poj.org/problem?id=3030
 */

#include <cstdio>

int main() {
    int numCase;
    scanf("%d", &numCase);
    while (numCase--) {
        int r, e, c;
        scanf("%d%d%d", &r, &e, &c);
        if (r > e - c) {
            printf("do not advertise\n");
        } else if (r < e - c) {
            printf("advertise\n");
        } else {
            printf("does not matter\n");
        }
    }
    return 0;
}
