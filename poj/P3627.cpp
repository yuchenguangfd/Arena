/*
 * Problem: Bookshelf
 * http://poj.org/problem?id=3627
 */

#include <algorithm>
#include <vector>
#include <cstdio>

int main() {
	int n, heightShelf;
	scanf("%d %d", &n, &heightShelf);
	std::vector<int> heights(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &heights[i]);
	}

	std::sort(heights.begin(), heights.end());

	int sum = 0;
	int count;
	for (count = n - 1; sum < heightShelf && count >= 0; --count) {
		sum += heights[count];
	}
	printf("%d\n", n - count - 1);
	return 0;
}
