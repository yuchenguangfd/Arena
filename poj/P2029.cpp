/*
 * Problem: Get Many Persimmon Trees
 * http://poj.org/problem?id=2029
 */

#include <functional>
#include <algorithm>
#include <vector>
#include <cstdio>

template <class T, class BinaryOp>
class BinaryIndexedTree2D {
public:
    BinaryIndexedTree2D(int rows, int cols) : mRows(rows), mCols(cols), mData(rows * cols) { }
    void Update(int i, int j, const T& rhs) {
        for (int ii = i; ii < mRows; ii += Step(ii)) {
            for (int jj = j; jj < mCols; jj += Step(jj)) {
                T& lhs = mData[ii * mCols + jj];
                lhs = mBinaryOp(lhs, rhs);
            }
        }
    }
    T Query(int i, int j) const {
        if (i < 0 || j < 0) return 0;
        T res = T();
        for (int ii = i; ii >= 0; ii -= Step(ii)) {
            for (int jj = j; jj >= 0; jj -= Step(jj)) {
                res = mBinaryOp(res, mData[ii * mCols + jj]);
            }
        }
        return res;
    }
private:
    int Step(int i) const {
        int x = i + 1;
        return x & (-x);
    }
private:
    int mRows;
    int mCols;
    std::vector<T> mData;
    BinaryOp mBinaryOp;
};


int main() {
    while (true) {
        int N;
        scanf("%d", &N);
        if (N == 0) break;
        int W, H;
        scanf("%d%d", &W, &H);

        BinaryIndexedTree2D<int, std::plus<int> > bit(H+1, W+1);
        for (int i = 0; i < N; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            bit.Update(y, x, 1);
        }
        int S, T;
        scanf("%d%d", &S, &T);
        int best = 0;
        for (int i = 0; i + T <= H; ++i) {
            for (int j = 0; j + S <= W; ++j) {
                int s1 = bit.Query(i, j);
                int s2 = bit.Query(i, j + S);
                int s3 = bit.Query(i + T, j);
                int s4 = bit.Query(i + T, j + S);
                int numTree = s4 - s2 - s3 + s1;
                best = std::max(best, numTree);
            }
        }
        printf("%d\n", best);
    }
    return 0;
}
