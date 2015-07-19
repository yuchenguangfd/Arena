/*
 * Problem: 分数加减法
 * http://poj.org/problem?id=3979
 */

#include <string>
#include <algorithm>
#include <iostream>

struct Rational {
    int numerator;
    int denominator;
    Rational(int n = 0, int d = 1) : numerator(n), denominator(d) {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }
    const Rational Reduce() {
        int a = std::abs(numerator);
        int b = denominator;
        while (b != 0) {
            int r = a % b;
            a = b;
            b = r;
        }
        return Rational(numerator/a, denominator/a);
    }
};

inline const Rational operator+ (const Rational& lhs, const Rational& rhs) {
    Rational res(lhs.numerator*rhs.denominator + lhs.denominator*rhs.numerator
               , lhs.denominator*rhs.denominator);
    return res.Reduce();
}

inline const Rational operator- (const Rational& lhs, const Rational& rhs) {
    Rational res(lhs.numerator*rhs.denominator - lhs.denominator*rhs.numerator
               , lhs.denominator*rhs.denominator);
    return res.Reduce();
}

inline std::ostream& operator<< (std::ostream& os, const Rational& rhs) {
    os << rhs.numerator;
    if (rhs.denominator != 1) {
        os << "/" << rhs.denominator;
    }
    return os;
}

int main() {
	std::string line;
	while (std::cin >> line) {
		Rational a(line[0]-'0', line[2]-'0');
		Rational b(line[4]-'0', line[6]-'0');
		Rational c;
		char op = line[3];
		if (op == '+') {
		    c = a + b;
		} else if (op == '-') {
		    c = a - b;
		}
		std::cout << c << std::endl;
	}
	return 0;
}
