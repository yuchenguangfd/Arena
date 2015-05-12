/*
 * Problem: Charm Bracelet
 * http://poj.org/problem?id=3624
 */

#include <memory>
#include <cstdio>

template <class T, class Alloc = std::allocator<T> >
class Array1D {
public:
    Array1D(int size, bool init = false, T initValue = T()) :
        mSize(size) {
        Alloc alloc;
        mData = alloc.allocate(mSize);
        if (init) {
            for (int i = 0; i < mSize; ++i) {
                alloc.construct(&mData[i], initValue);
            }
        }
    }
    ~Array1D()  {
        Alloc alloc;
        for (int i = 0; i < mSize; ++i) {
            alloc.destroy(&mData[i]);
        }
        alloc.deallocate(mData, mSize);
    }
    int Size() const { return mSize; }
    const T& operator[] (int index) const { return mData[index]; }
    T& operator[] (int index) { return mData[index]; }
private:
    int mSize;
    T *mData;
};

template <class T>
inline const T& Max(const T& a, const T& b) {
    return (a < b)? b : a;
}

int main() {
    int N,M;
    scanf("%d %d",&N, &M);
    Array1D<int> weight(N), desirability(N);
    for(int i = 0; i < N; ++i) {
        scanf("%d %d", &weight[i], &desirability[i]);
    }
    Array1D<int> dp(M+1, true, 0);
    for(int i = 0; i < N; ++i) {
        for(int j = M; j >= weight[i]; --j) {
            dp[j] = Max(dp[j-weight[i]]+desirability[i], dp[j]);
        }
    }
    int best = 0;
    for (int j = 0; j <= M; ++j) {
        best = Max(dp[j], best);
    }
    printf("%d\n", best);
    return 0;
}
