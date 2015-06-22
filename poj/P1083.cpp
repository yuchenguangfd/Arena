/*
 * Problem: Moving Tables
 * http://poj.org/problem?id=1083
 */

#include <algorithm>
#include <vector>
#include <cstdio>

void Inc(int& i) { ++i; }

int main() {
    int numCase;
    scanf("%d", &numCase);
    while (numCase--) {
        std::vector<int> count(256);
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            int s, t;
            scanf("%d %d", &s, &t);
            s = (s + 1) / 2;
            t = (t + 1) / 2;
            if (s > t) {
                std::swap(s, t);
            }
            std::for_each(&count[s], &count[t+1], Inc);
        }
        int max = *(std::max_element(count.begin(), count.end()));
        printf("%d\n", max * 10);
    }
    return 0;
}
