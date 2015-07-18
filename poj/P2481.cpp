/*
 * Problem: Cows
 * http://poj.org/problem?id=2481
 */

#include <functional>
#include <algorithm>
#include <vector>
#include <cstdio>

template <class T, class BinaryOp>
class BinaryIndexedTree {
public:
    BinaryIndexedTree(std::size_t size) : mData(size) { }
    void Update(std::size_t pos, const T& rhs) {
        for(std::size_t i = pos; i < mData.size(); i += Step(i)) {
           mData[i] = mBinaryOp(mData[i], rhs);
       }
    }
    T Query(std::size_t pos) {
        T res = mData[pos];
        for(int j = pos - Step(pos); j >= 0; j -= Step(j)) {
            res = mBinaryOp(res, mData[j]);
        }
        return res;
    }
private:
    std::size_t Step(int i) {
        int x = i + 1;
        return x & (-x);
    }
private:
    std::vector<T> mData;
    BinaryOp mBinaryOp;
};

struct Range {
	int s;
	int t;
	int id;
};

bool operator< (const Range& x, const Range& y) {
	if (x.t != y.t)
		return x.t < y.t;
	else
		return x.s > y.s;
}

int main() {
	while (true) {
	    int n;
		scanf("%d", &n);
		if (n == 0) break;
		std::vector<Range> ranges(n);
		int limit = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &ranges[i].s, &ranges[i].t);
			ranges[i].id = i;
			limit = std::max(limit, ranges[i].t);
		}
		std::sort(ranges.begin(), ranges.end());
		std::vector<int> ans(n);
		BinaryIndexedTree<int, std::plus<int> > bit(limit + 1);
		for(int i = n - 1; i >= 0; --i)	{
			if(i != n-1 && ranges[i].t == ranges[i+1].t && ranges[i].s == ranges[i+1].s) {
				ans[ranges[i].id] = ans[ranges[i+1].id];
			} else {
				ans[ranges[i].id] = bit.Query(ranges[i].s);
			}
			bit.Update(ranges[i].s, 1);
		}
		for (int i = 0; i < n; ++i) {
		    printf("%d%c", ans[i], (i==n-1)?'\n':' ');
		}
	}
	return 0;
}
