/*
 * Problem: Crossed ladders
 * http://poj.org/problem?id=2507
 */

#include <cmath>
#include <cstdio>

template <class FunctionType, class AnswerType>
AnswerType BinaryAnswer(const FunctionType& func, AnswerType low, AnswerType high, AnswerType eps) {
	AnswerType mid;
	while (high - low > eps) {
		mid = (low + high) / 2;
		if (func(low, mid, high) > 0) {
			low = mid;
		} else {
			high = mid;
		}
	}
	return mid;
}

template <class T>
inline const T& Min(const T& a, const T& b) {
    return (a < b)? a : b;
}

struct Function {
    double x;
    double y;
    double c;
    bool operator() (double low, double mid, double high) const {
        double f1 = sqrt((x*x-low*low)*(y*y-low*low)) - c*(sqrt(y*y-low*low)+sqrt(x*x-low*low));
        double f2 = sqrt((x*x-mid*mid)*(y*y-mid*mid)) - c*(sqrt(y*y-mid*mid)+sqrt(x*x-mid*mid));
        return f1 * f2 > 0.0;
	}
};

int main() {
	while (true) {
        Function func;
	    if (scanf("%lf%lf%lf", &func.x, &func.y, &func.c) == EOF) break;
		printf("%0.3f\n", BinaryAnswer<Function, double>(func, 0, Min(func.x, func.y), 1e-10));
	}
	return 0;
}
