/*
 * Problem: Stars
 * http://poj.org/problem?id=2352
 */

#include <functional>
#include <algorithm>
#include <vector>
#include <cstdio>

template <class T>
class Point2D {
public:
    Point2D() : x(), y() { }
    Point2D(T x, T y) : x(x), y(y) { }
public:
    T x;
    T y;
};

template <class T, class BinaryOp>
class BinaryIndexedTree {
public:
    BinaryIndexedTree(int size) : mData(size) { }
    void Update(int i, const T& rhs) {
        for(; i < mData.size(); i += Step(i)) {
           mData[i] = mBinaryOp(mData[i], rhs);
       }
    }
    T Query(int i) const {
        if (i < 0) return T();
        T res = mData[i];
        for(i -= Step(i); i >= 0; i -= Step(i)) {
            res = mBinaryOp(res, mData[i]);
        }
        return res;
    }
private:
    int Step(int i) const {
        int x = i + 1;
        return x & (-x);
    }
private:
    std::vector<T> mData;
    BinaryOp mBinaryOp;
};

typedef Point2D<int> Point2D32I;

int main() {
    int n;
    scanf("%d", &n);
    std::vector<Point2D32I> starts(n);
    int maxX = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &starts[i].x, &starts[i].y);
        maxX = std::max(maxX, starts[i].x);
    }
    BinaryIndexedTree<int, std::plus<int> > bit(maxX+1);
    std::vector<int> count(n);
    for (int i = 0; i < n; ++i) {
        ++count[bit.Query(starts[i].x)];
        bit.Update(starts[i].x, 1);
    }
    for (int i = 0; i < n; ++i) {
        printf("%d\n", count[i]);
    }
    return 0;
}
