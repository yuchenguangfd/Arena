/*
 * Problem: The Suspects
 * http://poj.org/problem?id=1611
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
    int Find(int elem) {
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
    int GroupSize(int elem) {
        return -mFather[Find(elem)];
    }
private:
    std::vector<int> mFather;
};

int main() {
    while (true) {
        int n, m;
        scanf("%d %d", &n, &m);
        if (n == 0 && m == 0) break;
        UFSet ufset(n);
        for (int i = 0; i < m; ++i) {
            int k, elem1;
            scanf("%d %d", &k, &elem1);
            for (int j = 1; j < k; ++j) {
                int elem2;
                scanf("%d", &elem2);
                ufset.Union(elem1, elem2);
            }
        }
        printf("%d\n", ufset.GroupSize(0));
    }
}
