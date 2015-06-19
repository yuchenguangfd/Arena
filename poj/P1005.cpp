/*
 * Problem: I Think I Need a Houseboat
 * http://poj.org/problem?id=1005
 */

#include <cmath>
#include <cstdio>

const double PI = 3.14159265358979;

struct Point2D64F {
    double x, y;
    Point2D64F(double px = 0.0, double py = 0.0) :
            x(px), y(py) {
    }
};

inline double distance(const Point2D64F& p1, const Point2D64F& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

inline double areaOfCircle(double radius) {
    return radius * radius * PI;
}

int main() {
    int numCase;
    scanf("%d", &numCase);
    for (int caseID = 1; caseID <= numCase; ++caseID) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        double dist = distance(Point2D64F(x, y), Point2D64F());
        double area = areaOfCircle(dist);
        int ans = static_cast<int>(area / 100) + 1;
        printf("Property %d: This property will begin eroding in year %d.\n",
                caseID, ans);
    }
    printf("END OF OUTPUT.\n");
    return 0;
}
