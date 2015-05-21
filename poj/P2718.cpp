/*
 * Problem: Smallest Difference
 * http://poj.org/problem?id=2718
 */

#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>

bool NextPermutation(int *array, int n) {
    if (n <= 1) return false;
    int j;
    for (j = n - 2; j >= 0 && array[j+1] <= array[j]; --j) { }
    if (j < 0) {
        int mid = n / 2;
        for (int i = 0; i < mid; ++i) {
            int temp = array[i];
            array[i] = array[n - 1 - i];
            array[n - 1 - i] = temp;
        }
        return false;
    }
    int k;
    for(k = n-1; array[k] <= array[j]; --k) { }
    int temp = array[j];
    array[j] = array[k];
    array[k] = temp;
    for(k = j+1; k <= (j + n) / 2; ++k) {
        int temp = array[k];
        array[k] = array[n + j - k];
        array[n+j-k] = temp;
    }
    return true;
}

inline int Abs(int x) {
    return (x < 0) ? -x : x;
}

int main(){
    const int base10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    std::string line;
    int numCase;
    std::cin >> numCase;
    std::getline(std::cin, line);
    for (int caseId = 0; caseId < numCase; ++caseId) {
        std::getline(std::cin, line);
        std::istringstream sin(line);
        std::vector<int> digits;
        int dig;
        while (sin >> dig) {
            digits.push_back(dig);
        }
        int n = digits.size();
        int best = 0x7fffffff;
        do {
            int splitPos = n / 2;
            int num1 = 0;
            for (int i = 0; i < splitPos; ++i) {
                num1 = num1 * 10 + digits[i];
            }
            int num2 = 0;
            for (int i = splitPos; i < n; ++i) {
                num2 = num2 * 10 + digits[i];
            }
            if (splitPos >= 2 && num1 < base10[splitPos-1]) continue;
            if (n-splitPos >= 2 && num2 < base10[n - splitPos - 1]) continue;
            if (Abs(num1 - num2) < best) {
                best = Abs(num1 - num2);
            }
        } while (NextPermutation(digits.data(), n));
        std::cout << best << std::endl;
    }
    return 0;
}
