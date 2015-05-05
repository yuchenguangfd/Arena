/*
 * Problem: Transportation
 * http://poj.org/problem?id=1040
 */

#include <vector>
#include <cstdio>

void Search(int capacity, int n, const std::vector<int>& begin,
        const std::vector<int>& end, const std::vector<int>& passengers,
        int dep, int sum, std::vector<int>& stationPassengers, int& best) {
    if (dep == n) {
        best = (sum > best)? sum : best;
        return;
    }
    bool canTake = true;
    for (int pos = begin[dep]; canTake && pos < end[dep]; ++pos) {
        if (stationPassengers[pos] + passengers[dep] > capacity) {
            canTake = false;
            break;
        }
    }
    if (canTake) {
        for (int pos = begin[dep]; pos < end[dep]; ++pos) {
            stationPassengers[pos] += passengers[dep];
        }
        int tmp = sum;
        for (int i = dep; i < n; ++i) {
            tmp += (end[i] - begin[i]) * passengers[i];
        }
        if (tmp > best) {
            Search(capacity, n, begin, end, passengers,
                    dep + 1, sum + (end[dep] - begin[dep]) * passengers[dep],
                    stationPassengers, best);
        }
        for (int pos = begin[dep]; pos < end[dep]; ++pos) {
            stationPassengers[pos] -= passengers[dep];
        }
    }
    Search(capacity, n, begin, end, passengers, dep + 1,
            sum, stationPassengers, best);
}

int main() {
    while (true) {
        int capacity, m, n;
        scanf("%d %d %d", &capacity, &m, &n);
        if (capacity == 0 && m == 0 && n == 0) break;
        std::vector<int> begin(n), end(n), passengers(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d", &begin[i], &end[i], &passengers[i]);
        }
        std::vector<int> stationPassengers(m);
        int best = 0;
        Search(capacity, n, begin, end, passengers, 0, 0,
                stationPassengers, best);
        printf("%d\n", best);
    }
    return 0;
}
