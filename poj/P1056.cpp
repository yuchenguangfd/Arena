/*
 * Problem: IMMEDIATE DECODABILITY
 * http://poj.org/problem?id=1056
 */

#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

bool StartWith(const std::string& src, const std::string& prefix) {
    if (src.size() < prefix.size()) return false;
    for (std::string::size_type i = 0; i < prefix.size(); ++i) {
        if (src[i] != prefix[i]) {
            return false;
        }
    }
    return true;
}


int main() {
    int caseId = 0;
    while (true) {
        char buff[16];
        if (scanf("%s", buff) == EOF) break;
        std::vector<std::string> codeSet;
        codeSet.push_back(std::string(buff));
        while (true) {
            scanf("%s", buff);
            std::string code(buff);
            if (code == "9") break;
            codeSet.push_back(code);
        }
        bool decodable = true;
        for (int i = 0; decodable && i < codeSet.size(); ++i) {
            for (int j = 0; decodable && j < codeSet.size(); ++j) {
                if (i != j && StartWith(codeSet[i], codeSet[j])) {
                    decodable = false;
                }
            }
        }
        if (decodable) {
            printf("Set %d is immediately decodable\n", ++caseId);
        } else {
            printf("Set %d is not immediately decodable\n", ++caseId);
        }
    }
    return 0;
}
