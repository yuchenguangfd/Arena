/*
 * Problem: Anagram
 * http://poj.org/problem?id=1256
 */

#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>

class OrderOfLetters {
public:
    bool operator()(char x, char y) {
        char a = tolower(x);
        char b = tolower(y);
        if (a != b) {
            return a < b;
        } else {
            return x < y;
        }
    }
};

int main() {
    int numCase;
    std::cin >> numCase;
    while (numCase--) {
        std::string word;
        std::cin >> word;
        std::sort(word.begin(), word.end(), OrderOfLetters());
        do {
            std::cout << word << std::endl;
        } while (std::next_permutation(word.begin(), word.end(), OrderOfLetters()));
    }
    return 0;
}
