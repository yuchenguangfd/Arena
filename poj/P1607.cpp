/*
 * Problem: Deck
 * http://poj.org/problem?id=1607
 */

#include <cstdio>

double harmonicNumber(int n) {
	double sum = 0.0;
	for(int i = 1; i <= n; ++i)
		sum += 1.0/i;
	return sum;
}

int main(){
	printf("Cards  Overhang\n");
	int n;
	while (scanf("%d", &n) != EOF) {
		printf("%5d%10.3f\n",n, harmonicNumber(n) / 2.0);
	}
	return 0;
}
