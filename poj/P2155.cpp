/*
 * Problem: Matrix
 * http://poj.org/problem?id=2155
 */

#include <algorithm>
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
    int numCase;
    scanf("%d", &numCase);
    while (numCase--) {
        int n, numOp;
        scanf("%d %d", &n, &numOp);
        BinaryIndexedTree2D<int, std::plus<int> > bit(n+1, n+1);
        while (numOp--) {
            char cmd[3];
            int x1, y1, x2, y2;
            scanf("%s", cmd);
            if (cmd[0] == 'C') {
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                if (x1 > x2) std::swap(x1, x2);
                if (y1 > y2) std::swap(y1, y2);
                bit.Update(x1, y1, +1);
                bit.Update(x1, y2+1, -1);
                bit.Update(x2+1, y1, -1);
                bit.Update(x2+1, y2+1, +1);
            } else {
                scanf("%d %d", &x1, &y1);
                printf("%d\n", bit.Query(x1, y1) % 2);
            }
        }
        printf("\n");
    }
    return 0;
}
