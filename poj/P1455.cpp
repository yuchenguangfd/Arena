/*
 * Problem: Crazy tea party
 * http://poj.org/problem?id=1455
 */

#include <algorithm>
#include <iterator>
#include <iostream>

int Solve(int n) {
    int k = n / 2;
    return (k * k - n * k + n * (n - 1) / 2);
}

int main() {
	int numCases;
	std::cin >> numCases;
	std::transform(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(),
	        std::ostream_iterator<int>(std::cout, "\n"), Solve);
	return 0;
}
