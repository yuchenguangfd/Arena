/*
 * Problem: 排列
 * http://poj.org/problem?id=1833
 */

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

int main() {
	int numCase;
	scanf("%d",&numCase);
	while (numCase--) {
		int n, k;
		scanf("%d %d",&n, &k);
		std::vector<int> list(n);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &list[i]);
		}
		for (int i = 0; i < k; ++i) {
			std::next_permutation(list.begin(), list.end());
		}
		for (int i = 0; i < n; ++i) {
		    std::cout << list[i] << ((i==n-1)?'\n':' ');
		}
	}
	return 0;
}
