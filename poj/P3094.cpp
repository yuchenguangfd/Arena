/*
 * Problem: Quicksum
 * http://poj.org/problem?id=3094
 */

#include <string>
#include <cstdio>

int main() {
    const int MAX_BUFF_SIZE = 512;
    while (true) {
        char buff[MAX_BUFF_SIZE];
        fgets(buff, MAX_BUFF_SIZE, stdin);
        std::string packet(buff);
        if (packet == "#\n") break;
        int sum = 0;
        for (int i = 0; i < packet.length(); ++i) {
            if (packet[i] >= 'A' && packet[i] <= 'Z') {
                sum += (i + 1) * (packet[i] - 'A' + 1);
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}
