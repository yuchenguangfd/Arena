/*
 * Problem: THE DRUNK JAILER
 * http://poj.org/problem?id=1218
 */

#include <cmath>
#include <cstdio>

int main() {
	int numCase;
	scanf("%d", &numCase);
	while (numCase--) {
		int n;
		scanf("%d", &n);
		int ans = sqrt(static_cast<double>(n));
		printf("%d\n", ans);
	}
	return 0;
}
