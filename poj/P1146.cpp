/*
 * Problem: ID Codes
 * http://poj.org/problem?id=1146
 */

#include <algorithm>
#include <string>
#include <cstdio>

int main() {
    char buff[64];
    while (true) {
        scanf("%s", buff);
        std::string curr(buff);
        if (curr == "#") break;
        std::string next = curr;
        bool flag = false;
        do {
            flag = std::next_permutation(next.begin(), next.end());
        } while (flag && next == curr);
        if (!flag) {
            printf("No Successor\n");
        } else {
            printf("%s\n", next.c_str());
        }
    }
    return 0;
}
