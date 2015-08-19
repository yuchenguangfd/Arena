/*
 * Problem: How many Fibs?
 * http://poj.org/problem?id=2413
 */

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class BigInteger {
public:
    BigInteger();
    BigInteger(int i);
    BigInteger(const std::string& s);
    BigInteger(const BigInteger& orig);
    virtual ~BigInteger();
    BigInteger& operator= (const BigInteger& rhs);
    friend BigInteger operator+ (const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator== (const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator< (const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator<= (const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator> (const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator>= (const BigInteger& lhs, const BigInteger& rhs);
public:
    static const int DIGIT_PER_NUMBER = 4;
    static const int RADIX = 10000;
    std::vector<int> mNumbers;
};

BigInteger::BigInteger() : mNumbers(1) { }

BigInteger::BigInteger(int val) {
    if (val == 0) {
        mNumbers.resize(1);
        mNumbers[0] = 0;
        return;
    }
    int nums[4];
    int count = 0;
    while (val > 0) {
        nums[count] = val % RADIX;
        val /= RADIX;
        count++;
    }
    mNumbers.resize(count);
    std::copy(nums, nums + count, mNumbers.begin());
}

BigInteger::BigInteger(const std::string& s) {
    int n = s.size();
    mNumbers.reserve((n + DIGIT_PER_NUMBER - 1) / DIGIT_PER_NUMBER);
    for(int i = n - 1; i >= 0;) {
        int weight = 1, temp = 0;
        while (weight < RADIX && i >= 0) {
          temp += (s[i] - '0') * weight;
          weight *= 10;
          --i;
      }
      mNumbers.push_back(temp);
    }
    while (mNumbers.size() > 1 && *mNumbers.rbegin() == 0) {
        mNumbers.pop_back();
    }
}

BigInteger::BigInteger(const BigInteger& orig) : mNumbers(orig.mNumbers) { }

BigInteger::~BigInteger() { }

BigInteger& BigInteger::operator= (const BigInteger& rhs) {
    if (this == &rhs) return *this;
    mNumbers = rhs.mNumbers;
    return *this;
}

BigInteger operator+ (const BigInteger& lhs, const BigInteger& rhs) {
    int maxLength = std::max(lhs.mNumbers.size(), rhs.mNumbers.size());
    int minLength = std::min(lhs.mNumbers.size(), rhs.mNumbers.size());
    BigInteger result;
    result.mNumbers.resize(maxLength + 1);
    int carry = 0;
    for (int i = 0; i < minLength; ++i) {
        result.mNumbers[i] = lhs.mNumbers[i] + rhs.mNumbers[i] + carry;
        carry = result.mNumbers[i] / BigInteger::RADIX;
        result.mNumbers[i] %= BigInteger::RADIX;
    }
    if (minLength < maxLength) {
        const std::vector<int>& remains = (lhs.mNumbers.size() > minLength) ? lhs.mNumbers : rhs.mNumbers;
        for(int i = minLength; i < maxLength; ++i)  {
            result.mNumbers[i] = remains[i] + carry;
            carry = result.mNumbers[i] / BigInteger::RADIX;
            result.mNumbers[i] %= BigInteger::RADIX;
        }
    }
    if (carry != 0) {
        result.mNumbers[maxLength] = carry;
    } else {
        result.mNumbers.resize(maxLength);
    }
    return result;
}

bool operator== (const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.mNumbers.size() != rhs.mNumbers.size()) return false;
    for (int i = 0; i < lhs.mNumbers.size(); ++i) {
        if (lhs.mNumbers[i] != rhs.mNumbers[i]) return false;
    }
    return true;
}

bool operator< (const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.mNumbers.size() != rhs.mNumbers.size()) {
        return lhs.mNumbers.size() < rhs.mNumbers.size();
    }
    for (int i = lhs.mNumbers.size() - 1; i >= 0; --i) {
        if (lhs.mNumbers[i] != rhs.mNumbers[i]) {
            return lhs.mNumbers[i] < rhs.mNumbers[i];
        }
    }
    return false;
}

bool operator<= (const BigInteger& lhs, const BigInteger& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator> (const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.mNumbers.size() != rhs.mNumbers.size()) {
        return lhs.mNumbers.size() > rhs.mNumbers.size();
    }
    for (int i = lhs.mNumbers.size() - 1; i >= 0; --i) {
        if (lhs.mNumbers[i] != rhs.mNumbers[i]) {
            return lhs.mNumbers[i] > rhs.mNumbers[i];
        }
    }
    return false;
}

bool operator>= (const BigInteger& lhs, const BigInteger& rhs) {
    return (lhs > rhs) || (lhs == rhs);
}

int main() {
	const int n = 500;
	std::vector<BigInteger> fibs(n);
	fibs[0] = 1;
	fibs[1] = 2;
	for (int i = 2; i < n; ++i) {
		fibs[i] = fibs[i - 1] + fibs[i - 2];
	}
    while (true) {
        std::string s1, s2;
        std::cin >> s1 >> s2;
        BigInteger a(s1);
        BigInteger b(s2);
        if (a == 0 && b == 0) break;
        std::vector<BigInteger>::iterator l = std::lower_bound(fibs.begin(), fibs.end(), a);
        std::vector<BigInteger>::iterator u = std::upper_bound(fibs.begin(), fibs.end(), b);
        int count =  u - l;
        std::cout << count << std::endl;
    }
    return 0;    
}
