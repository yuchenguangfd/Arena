/*
 * Problem: Maya Calendar
 * http://poj.org/problem?id=1008
 */

#include <string>
#include <algorithm>
#include <iostream>

int main() {
    const std::string month1[19] = {"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin",
            "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax",
            "koyab", "cumhu", "uayet" };
    const std::string month2[20] = { "imix", "ik", "akbal", "kan", "chicchan", "cimi",
            "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem",
            "cib", "caban", "eznab", "canac", "ahau" };

    int numCase;
    std::cin >> numCase;
    std::cout << numCase << std::endl;
    while (numCase--) {
        int year, day, month;
        char sp;
        std::string month_str;
        std::cin >> day >> sp >> month_str >> year;
        month = std::find(month1, month1 + sizeof(month1), month_str) - month1;
        int pass_days = year * 365 + month * 20 + day;
        int num = pass_days % 13 + 1;
        std::string name = month2[pass_days % 20];
        year = pass_days / 260;
        std::cout << num << " " << name << " " << year << std::endl;
    }
    return 0;
}

