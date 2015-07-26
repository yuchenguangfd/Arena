/*
 * Problem: ICPC Score Totalizer Software
 * http://poj.org/problem?id=3325
 */

#include <numeric>
#include <algorithm>
#include <vector>
#include <cstdio>

int main() {
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        std::vector<int> score(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &score[i]);
        }
        int avg = (std::accumulate(score.begin(), score.end(), 0)
                - *(std::min_element(score.begin(), score.end()))
                - *(std::max_element(score.begin(), score.end()))) / (n - 2);
        printf("%d\n", avg);
    }
    return 0;
}
