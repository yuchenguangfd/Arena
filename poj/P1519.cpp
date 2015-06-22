/*
 * Problem: Digital Roots
 * http://poj.org/problem?id=1519
 */

#include <string>
#include <numeric>
#include <sstream>
#include <iostream>

int AddDigital(int sum, char ch) {
    return sum + (ch - '0');
}

std::string ToString(int num) {
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

int main() {
	while (true) {
	    std::string num;
	    std::getline(std::cin, num);
		if (num == "0") break;
		int sum = std::accumulate(num.begin(), num.end(), 0, AddDigital);
		while (sum >= 10) {
		    num = ToString(sum);
			sum = std::accumulate(num.begin(), num.end(), 0, AddDigital);
		}
		std::cout << sum << std::endl;
	}
	return 0;
}
