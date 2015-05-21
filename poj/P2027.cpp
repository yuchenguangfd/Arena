/*
 * Problem: No Brainer
 * http://poj.org/problem?id=2027
 */

#include <cstdio>

int main() {
	int numCase;
	scanf("%d", &numCase);
	while(numCase--) {
		int a, b;
		scanf("%d %d",&a,&b);
		if (a < b) {
			printf("NO BRAINS\n");
		} else {
			printf("MMM BRAINS\n");
		}
	}
	return 0;
}
