/*
 * Problem: Unhappy Jinjin
 * http://poj.org/problem?id=2656
 */

#include <vector>
#include <cstdio>

template <class Iterator>
const typename std::iterator_traits<Iterator>::value_type&
    MaxInRange(Iterator begin, Iterator end, Iterator& maxPos) {
    maxPos = begin;
    for (++begin; begin != end; ++begin) {
        if (*maxPos < *begin) {
            maxPos = begin;
        }
    }
    return *maxPos;
}

int main() {
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        std::vector<int> times(n);
        for (int i = 0; i < n; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            times[i] = a + b;
        }
        std::vector<int>::iterator maxPos;
        int maxTime = MaxInRange(times.begin(), times.end(), maxPos);
        if (maxTime <= 8) {
            printf("0\n");
        } else {
            printf("%d\n", (int)(maxPos - times.begin()) + 1);
        }
    }
    return 0;
}
