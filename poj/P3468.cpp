/*
 * Problem: A Simple Problem with Integers
 * http://poj.org/problem?id=3468
 */

#include <functional>
#include <vector>
#include <cstdio>

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

typedef long long int64;
int main() {
    int n, numQuery;
    scanf("%d %d", &n, &numQuery);
    std::vector<int64> sum(n+1);
    for (int i = 1; i <= n; ++i) {
        int a;
        scanf("%d", &a);
        sum[i] = sum[i - 1] + a;
    }
    BinaryIndexedTree<int64, std::plus<int64> > bitDelta1(n+1), bitDelta2(n+1);
    while (numQuery--) {
        char cmd[4];
        int s, t, delta;
        scanf("%s", cmd);
        if (cmd[0] == 'C') {
            scanf("%d %d %d", &s, &t, &delta);
            bitDelta1.Update(s, delta);
            bitDelta1.Update(t + 1, -delta);
            bitDelta2.Update(s, delta * s);
            bitDelta2.Update(t + 1, -delta*(t+1));
        } else if (cmd[0] == 'Q'){
            scanf("%d%d", &s, &t);
            int64 s1 = sum[s-1] + s*bitDelta1.Query(s - 1) - bitDelta2.Query(s - 1);
            int64 s2 = sum[t] + (t+1)*bitDelta1.Query(t)- bitDelta2.Query(t);
            int64 rangeSum = s2 - s1;
            printf("%lld\n", rangeSum);
        }
    }
    return 0;
}
