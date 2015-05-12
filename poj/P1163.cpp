/*
 * Problem: The Triangle
 * http://poj.org/problem?id=1163
 */

#include <algorithm>
#include <memory>
#include <cstdio>

template <class T, class Alloc = std::allocator<T> >
class Array2D {
public:
    Array2D(int r, int c, bool init = false, T initValue = T()) :
        mRows(r), mCols(c), mSize(r * c) {
        Alloc alloc;
        mData = alloc.allocate(mSize);
        if (init) {
            for (int i = 0; i < mSize; ++i) {
                alloc.construct(&mData[i], initValue);
            }
        }
    };
    ~Array2D() {
        Alloc alloc;
        for (int i = 0; i < mSize; ++i) {
            alloc.destroy(&mData[i]);
        }
        alloc.deallocate(mData, mSize);
    }
    int Rows() const { return mRows; }
    int Cols() const { return mCols; }
    const T* operator[] (int i) const {
        return mData + i * mCols;
    }
    T* operator[] (int i) {
        return mData + i * mCols;
    }
private:
    int mRows, mCols;
    int mSize;
    T* mData;
};

template <class T>
inline const T& Max(const T& a, const T& b) {
    return (a < b)? b : a;
}

int main() {
	int n;
	scanf("%d", &n);
	Array2D<int> triangle(n, n), dp(n, n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= i; j++) {
			scanf("%d", &triangle[i][j]);
		}
	}

	for(int j = 0; j < n; j++) {
		dp[n-1][j] = triangle[n-1][j];
	}
	for(int i = n-2; i >= 0; i--) {
		for(int j = 0; j <= i; j++) {
			dp[i][j] = Max(dp[i+1][j], dp[i+1][j+1]) + triangle[i][j];
		}
	}
	printf("%d\n", dp[0][0]);
	return 0;
}
