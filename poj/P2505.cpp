/*
 * Problem: A multiplication game
 * http://poj.org/problem?id=2505
 * Author: YuChenguang
 */

#include <cstdio>

int main() {
	double N;
	while (scanf("%lf", &N) != EOF) {
		while (N > 18) N /= 18;
		if (N <= 9) {
			printf("Stan wins.\n");
		} else {
			printf("Ollie wins.\n");
		}
	}
	return 0;
}
