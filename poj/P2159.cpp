/*
 * Problem: Ancient Cipher
 * http://poj.org/problem?id=2159
 */

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class CountChar {
public:
    CountChar(std::vector<int>& freq) : mFreq(freq) { }
    void operator() (char ch) {
        ++mFreq[ch - 'A'];
    }
private:
    std::vector<int>& mFreq;
};

int main() {
    std::string str1, str2;
	std::cin >> str1 >> str2;
	std::vector<int> freq1(26), freq2(26);
	CountChar countChar1(freq1), countChar2(freq2);
	std::for_each(str1.begin(), str1.end(), countChar1);
	std::for_each(str2.begin(), str2.end(), countChar2);
	std::sort(freq1.begin(), freq1.end());
	std::sort(freq2.begin(), freq2.end());
	if (std::equal(freq1.begin(), freq1.end(), freq2.begin())) {
	    std::cout << "YES\n";
	} else {
	    std::cout << "NO\n";
	}
	return 0;
}
