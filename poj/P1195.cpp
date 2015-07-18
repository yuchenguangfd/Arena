/*
 * Problem: Mobile phones
 * http://poj.org/problem?id=1195
 */

#include <functional>
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
    std::size_t Step(std::size_t i) const {
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
    int queryType;
    int size;
    scanf("%d %d", &queryType, &size);
    BinaryIndexedTree2D<int, std::plus<int> > bit(size, size);
    while(true) {
        scanf("%d", &queryType);
        if (queryType == 1) {
            int row, col, delta;
            scanf("%d %d %d", &row, &col, &delta);
            bit.Update(row, col, delta);
        } else if (queryType == 2) {
            int left, bottom, right, top;
            scanf("%d %d %d %d", &left, &bottom, &right, &top);
            int ans = bit.Query(right, top)
                    - bit.Query(left - 1, top)
                    - bit.Query(right, bottom - 1)
                    + bit.Query(left - 1, bottom - 1);
            printf("%d\n", ans);
        } else if (queryType == 3) {
            break;
        }
    }
    return 0;
}
