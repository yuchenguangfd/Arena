/*
 * Problem: MooFest
 * http://poj.org/problem?id=1990
 */

#include <utility>
#include <algorithm>
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
    std::size_t Step(std::size_t i) const {
        int x = i + 1;
        return x & (-x);
    }
private:
    std::vector<T> mData;
    BinaryOp mBinaryOp;
};

class Cow : private std::pair<int, int> {
public:
	Cow(int volume, int coordinate) : std::pair<int, int>(volume, coordinate) { }
	int Volume() const { return first; }
	int Coordinate() const { return second; }
};

class CowComp {
public:
    bool operator() (const Cow& lhs, const Cow& rhs) {
    	return lhs.Volume() < rhs.Volume();
    }
};

int main() {
	int numCow;
	scanf("%d", &numCow);
	std::vector<Cow> cows;
	cows.reserve(numCow);
	for(int i = 0; i < numCow; ++i) {
		int volume, coordinate;
		scanf("%d %d", &volume, &coordinate);
		cows.push_back(Cow(volume, coordinate));
	}
	std::sort(cows.begin(), cows.end(), CowComp());
	long long ans = 0;
	const int MAX_X = 20000;
	BinaryIndexedTree<int, std::plus<int> > L(MAX_X);
	BinaryIndexedTree<int, std::plus<int> > S(MAX_X);
	for(int i = 0; i < cows.size(); ++i) {
		int vi = cows[i].Volume();
		int xi = cows[i].Coordinate();
		int a = L.Query(xi-1);
		int b = L.Query(MAX_X-1)-L.Query(xi-1-1);
		int s1 = S.Query(xi-1);
		int s2 = S.Query(MAX_X-1)-S.Query(xi-1-1);
		long long t = (a-b)*xi-s1+s2;
		ans += vi*t;
		L.Update(xi-1,1);
		S.Update(xi-1,xi);
	}
	printf("%lld\n", ans);
	return 0;
}
