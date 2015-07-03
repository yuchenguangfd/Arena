/*
 * Problem: 487-3279
 * http://poj.org/problem?id=1002
 */

#include <map>
#include <string>
#include <cstdio>

inline int AlphToDigit(char ch) {
    switch (ch) {
        case 'A': case 'B': case 'C': return 2;
        case 'D': case 'E': case 'F': return 3;
        case 'G': case 'H': case 'I': return 4;
        case 'J': case 'K': case 'L': return 5;
        case 'M': case 'N': case 'O': return 6;
        case 'P': case 'Q': case 'R': case 'S': return 7;
        case 'T': case 'U': case 'V': return 8;
        case 'W': case 'X': case 'Y': case 'Z': return 9;
    }
    return 0;
}

int TelToInt(std::string& tel) {
    int num = 0;
    for (int i = 0; i < tel.length(); ++i) {
        if (tel[i] == '-') continue;
        if (tel[i] >= '0' && tel[i] <= '9') {
            num = num * 10 + (tel[i] - '0');
        } else {
            num = num * 10 + AlphToDigit(tel[i]);
        }
    }
    return num;
}

std::string IntToTel(int x) {
    int digits[7];
    for (int i = 7; i >= 1; --i) {
        digits[i] = x % 10;
        x /= 10;
    }
    std::string tel;
    tel.reserve(16);
    for (int i = 1; i <= 3; ++i) {
        tel += static_cast<char>('0' + digits[i]);
    }
    tel += '-';
    for (int i = 4; i <= 7; ++i) {
        tel += static_cast<char>('0' + digits[i]);
    }
    return tel;
}

int main() {
    int n;
    scanf("%d", &n);
    std::map<int, int> dict;
    for (int i = 0; i < n; ++i) {
        char buff[64];
        scanf("%s", buff);
        std::string tel(buff);
        int num = TelToInt(tel);
        dict[num]++;
    }
    bool dupl = false;
    for (std::map<int, int>::iterator iter = dict.begin(); iter != dict.end(); ++iter) {
        if (iter->second > 1) {
            std::string tel = IntToTel(iter->first);
            printf("%s %d\n", tel.c_str(), iter->second);
            dupl = true;
        }
    }
    if (!dupl) {
        printf("No duplicates.\n");
    }
    return 0;
}
