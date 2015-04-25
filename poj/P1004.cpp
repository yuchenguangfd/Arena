/*
 * Problem: Financial Management
 * http://poj.org/problem?id=1004
 */

#include <iterator>
#include <cstdio>
#include <cassert>

template <class Iterator>
const typename std::iterator_traits<Iterator>::value_type
	Average(Iterator begin, Iterator end) {
	assert(begin != end);
	typename std::iterator_traits<Iterator>::value_type sum = *begin;
	int count = 1;
	for (++begin; begin != end; ++begin) {
		sum = sum + *begin;
		++count;
	}
	return sum / count;
}

int main() {
   const int SIZE = 12;
   float balance[SIZE];
   for (int i = 0; i < SIZE; ++i) {
	   scanf("%f", &balance[i]);
   }
   printf("$%.2f\n", Average(balance, balance+SIZE));
   return 0;
}
