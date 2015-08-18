/*
 * Problem: Uncle Jack
 * http://poj.org/problem?id=3199
 */

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <cstdio>

template <class T>
const T FastPower(const T& x, unsigned int n) {
    T result(1);
    T p = x;
    while (n != 0) {
        if (n & 0x1) {
            result = result * p;
        }
        p = p * p;
        n >>= 1;
    }
    return result;
}


class BigInteger {
public:
    BigInteger();
    BigInteger(int i);
    BigInteger(const BigInteger& orig);
    virtual ~BigInteger();
    BigInteger& operator= (const BigInteger& rhs);
    const std::string ToString() const;
    friend BigInteger operator* (const BigInteger& lhs, const BigInteger& rhs);
private:
    static const int RADIX = 10000;
    std::vector<int> mNumbers;
};

BigInteger::BigInteger() : mNumbers(1) { }

BigInteger::BigInteger(int val) {
    assert(val >= 0);
    int nums[4];
    int count = 0;
    while (val > 0) {
        nums[count] = val % RADIX;
        val /= RADIX;
        count++;
    }
    mNumbers.resize(count);
    for (int i = 0; i < count; ++i) {
        mNumbers[i] = nums[i];
    }
}

BigInteger::BigInteger(const BigInteger& orig) :
    mNumbers(orig.mNumbers) { }

BigInteger::~BigInteger() { }

BigInteger& BigInteger::operator= (const BigInteger& rhs) {
    if (this == &rhs) return *this;
    mNumbers = rhs.mNumbers;
    return *this;
}

const std::string BigInteger::ToString() const {
    std::ostringstream oss;
    oss << *mNumbers.rbegin();
    for (std::vector<int>::const_reverse_iterator it = mNumbers.rbegin() + 1; it != mNumbers.rend(); ++it) {
        for (int r = BigInteger::RADIX / 10; r >= 10; r /= 10) {
            if(*it < r) oss << '0';
        }
        oss << *it;
    }
    return oss.str();
}

BigInteger operator* (const BigInteger& lhs, const BigInteger& rhs) {
    int length1 = lhs.mNumbers.size();
    int length2 = rhs.mNumbers.size();
    BigInteger result;
    result.mNumbers.resize(length1 + length2);
    for (int i = 0; i < length1; ++i) {
        for (int j = 0; j < length2; ++j) {
            int pos = i + j;
            result.mNumbers[pos] += lhs.mNumbers[i] * rhs.mNumbers[j];
            result.mNumbers[pos+1] +=  result.mNumbers[pos] / BigInteger::RADIX;
            result.mNumbers[pos] %= BigInteger::RADIX;
        }
    }
    if (result.mNumbers[length1 + length2 - 1] == 0) {
        result.mNumbers.resize(length1 + length2 - 1);
    }
    return result;
}

int main() {
    while (true) {
        int n, d;
        scanf("%d%d", &n, &d);
        if (n == 0 && d == 0) break;
        BigInteger big_n(n);
        BigInteger ans = FastPower(big_n, d);
        printf("%s\n", ans.ToString().c_str());
    }
    return 0;
}
