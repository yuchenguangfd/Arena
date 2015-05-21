/*
 * Problem: Bode Plot
 * http://poj.org/problem?id=1045
 */

#include <cmath>
#include <cstdio>

int main() {
    float U, R, C;
    scanf("%f %f %f", &U, &R, &C);
    int numCase;
    scanf("%d", &numCase);
    while(numCase--) {
        float w;
        scanf("%f" , &w);
        float ans = U * R / sqrt(R*R + 1.0/(w*w*C*C));
        printf("%.3f\n", ans);
    }
    return 0;
}
