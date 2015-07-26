/*
 * Problem: Ride to School
 * http://poj.org/problem?id=1922
 */

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdio>

int main() {
    const double DISTANCE = 4.50;
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        double minTime = DBL_MAX;
        for (int i = 0; i < n; ++i) {
            double v, t;
            scanf("%lf %lf", &v, &t);
            if (t >= 0) {
                minTime = std::min(DISTANCE * 3600 / v + t, minTime);
            }
        }
        printf("%.0lf\n", ceil(minTime));
    }
    return 0;
}
