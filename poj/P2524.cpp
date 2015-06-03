/*
 * Problem: Ubiquitous Religions
 * http://poj.org/problem?id=2524
 */

#include <vector>
#include <algorithm>
#include <cstdio>

class UFSet {
public:
    UFSet(int size) : mFather(size) {
        std::fill(mFather.begin(), mFather.end(), -1);
    }
    bool Union(int elem1, int elem2) {
        int root1 = Find(elem1);
        int root2 = Find(elem2);
        if (root1 == root2) return false;
        if (mFather[root1] < mFather[root2]) {
            mFather[root1] += mFather[root2];
            mFather[root2] = root1;
        } else {
            mFather[root2] += mFather[root1];
            mFather[root1] = root2;
        }
        return true;
    }
    int Find(int elem) const {
        int root = elem;
        while (mFather[root] >= 0) {
            root = mFather[root];
        }
        while (mFather[elem] >= 0) {
            int tmp = mFather[elem];
            mFather[elem] = root;
            elem = tmp;
        }
        return root;
    }
    int GroupSize(int elem) const {
        return -mFather[Find(elem)];
    }
    int NumGroup() const {
        int count = 0;
        for (int i = 0; i < mFather.size(); ++i) {
            if (mFather[i] < 0) {
                ++count;
            }
        }
        return count;
    }
private:
    mutable std::vector<int> mFather;
};

int main() {
    int caseId = 0;
    while (true) {
        int n, m;
        scanf("%d %d", &n, &m);
        if (n == 0 && m == 0) break;
        UFSet ufset(n);
        while (m--) {
            int a, b;
            scanf("%d %d", &a, &b);
            --a; --b;
            ufset.Union(a, b);
        }
        printf("Case %d: %d\n", ++caseId, ufset.NumGroup());
    }
    return 0;
}
