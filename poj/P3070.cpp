/*
 * Problem: Fibonacci
 * http://poj.org/problem?id=3070
 */

#include <cstdio>
#include <memory>

typedef unsigned int uint32;

class ModularInteger {
public:
	ModularInteger(uint32 val = 0) : mValue(val % sModular) { }
	uint32 Value() const { return mValue; }
	static void SetModular(int modular);
	friend bool operator== (const ModularInteger& lhs, const ModularInteger& rhs);
	friend ModularInteger operator+ (const ModularInteger& lhs, const ModularInteger& rhs);
	friend ModularInteger operator* (const ModularInteger& lhs, const ModularInteger& rhs);
private:
	static const int DEFAULT_MODULAR = 0xffff;
	static int sModular;
	uint32 mValue;
};

inline bool operator== (const ModularInteger& lhs, const ModularInteger& rhs) {
	return (lhs.mValue == rhs.mValue);
}

inline ModularInteger operator+ (const ModularInteger& lhs, const ModularInteger& rhs) {
	return ModularInteger(lhs.mValue + rhs.mValue);
}

inline ModularInteger operator* (const ModularInteger& lhs, const ModularInteger& rhs) {
	return ModularInteger(lhs.mValue * rhs.mValue);
}

int ModularInteger::sModular = ModularInteger::DEFAULT_MODULAR;

void ModularInteger::SetModular(int modular) {
	sModular = modular;
}

template <class T, class Alloc = std::allocator<T> >
class Matrix {
public:
    Matrix(int rows, int cols, bool init = false, T initValue = T());
    Matrix(const Matrix<T, Alloc>& orig);
    ~Matrix();
    Matrix<T, Alloc>& operator= (const Matrix<T, Alloc>& rhs);
    template <class T1, class Alloc1>
    friend Matrix<T1, Alloc1> operator* (const Matrix<T1, Alloc1>& lhs, const Matrix<T1, Alloc1>& rhs);
    T* operator[] (int row) { return mData + row * mCols; }
    const T* operator[] (int row) const { return mData + row * mCols; }
private:
    T *mData;
    int mRows;
    int mCols;
    int mSize;
};

template <class T, class Alloc>
Matrix<T, Alloc>::Matrix(int rows, int cols, bool init, T initValue) :
    mRows(rows),
    mCols(cols),
    mSize(rows * cols) {
    Alloc alloc;
    mData = alloc.allocate(mSize);
    if (init) {
        std::fill(mData, mData + mSize, initValue);
    }
}

template <class T, class Alloc>
Matrix<T, Alloc>::Matrix(const Matrix<T, Alloc>& orig) :
    mRows(orig.mRows),
    mCols(orig.mCols),
    mSize(orig.mSize) {
    Alloc alloc;
    mData = alloc.allocate(mSize);
    std::copy(orig.mData, orig.mData + orig.mSize, mData);
}

template <class T, class Alloc>
Matrix<T, Alloc>::~Matrix() {
    Alloc alloc;
    alloc.deallocate(mData, mSize);
}

template <class T, class Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator= (const Matrix<T, Alloc>& rhs) {
    if (this == &rhs) return *this;
    if (mSize != rhs.mSize) {
        Alloc alloc;
        alloc.deallocate(mData, mSize);
        mRows = rhs.mRows;
        mCols = rhs.mCols;
        mSize = rhs.mSize;
        mData = alloc.allocate(mSize);
    }
    std::copy(rhs.mData, rhs.mData + rhs.mSize, mData);
    return *this;
}

template <class T, class Alloc>
Matrix<T, Alloc> operator* (const Matrix<T, Alloc>& lhs, const Matrix<T, Alloc>& rhs) {
    Matrix<T, Alloc> result(lhs.mRows, rhs.mCols);
    for(int i = 0; i < result.mRows; ++i) {
        for(int j = 0; j < result.mCols; ++j) {
            T sum = T();
            for(int k = 0; k < lhs.mCols; ++k) {
                sum = sum + lhs[i][k] * rhs[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

template <class T>
T FastPower(const T& x, int n) {
	T result = x;
	--n;
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

int main() {
	ModularInteger::SetModular(10000);
	Matrix<ModularInteger> Fib(2,2);
	Fib[0][0] = 1; Fib[0][1] = 1;
	Fib[1][0] = 1; Fib[1][1] = 0;
	while(true)	{
		int n;
		scanf("%d", &n);
		if(n == -1)break;
		if(n == 0) {
			printf("0\n");
			continue;
		}
		Matrix<ModularInteger> Fn = FastPower(Fib, n);
		printf("%d\n", Fn[0][1].Value());
	}
	return 0;
}
