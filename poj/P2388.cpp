/*
 * Problem: Who's in the Middle
 * http://poj.org/problem?id=2388
 */

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

int main() {
	int n;
	std::cin >> n;
	std::vector<int> milk;
	std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(),
	        std::back_inserter(milk));
	std::nth_element(milk.begin(), milk.begin() + milk.size() / 2, milk.end());
	std::cout << milk[milk.size() / 2] << std::endl;
	return 0;
}
