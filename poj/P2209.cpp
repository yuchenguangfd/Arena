/*
 * Problem: The King
 * http://poj.org/problem?id=2209
 */

#include <cstdio>

template <class T>
const T FastPower(const T& x, int n) {
    T result = x;
    --n;
    T p = x;
    while (n != 0) {
        if (n & 0x1) {
            result = result * p;
        }
        p = p * p;
        n >>= 1;
    }
    return result;
}

int main() {
	int numSon, exponent;
	scanf("%d %d", &numSon, &exponent);
	int sum = 0;
	for (int i = 0; i < numSon; ++i) {
		int mental;
		scanf("%d", &mental);
		int chance = FastPower(mental, exponent);
		if (chance > 0) {
		    sum += chance;
		}
	}
	printf("%d\n", sum);
	return 0;
}
