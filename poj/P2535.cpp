/*
 * Problem: Very Simple Problem
 * http://poj.org/problem?id=2535
 */

#include <utility>
#include <algorithm>
#include <vector>
#include <cstdio>

struct CountSimplestOrHardestOp {
    int sp, hd;
    CountSimplestOrHardestOp(int sp, int hd) : sp(sp), hd(hd) { }
    const std::pair<int, int> operator() (int lhs, const std::pair<int, int>& rhs) {
        std::pair<int, int> res(rhs);
        if (lhs == sp) ++res.first;
        if (lhs == hd) ++res.second;
        return res;
    }
};

struct CollectVerySimple {
    int members, id;
    std::vector<int>& verySimples;
    CollectVerySimple(int members, std::vector<int>& verySimples):
        members(members), id(0), verySimples(verySimples) { }
    void operator() (const std::pair<int, int> p) {
        ++id;
        if (p.first > members / 2 && p.second == 0) {
          verySimples.push_back(id);
        }
    }
};

int main() {
	int members, problems;
	scanf("%d %d",&members, &problems);
	std::vector<std::pair<int, int> > pairs(problems);
	for (int i = 0; i < members; ++i) {
        std::vector<int> complexity(problems);
		for (int j = 0; j < problems; ++j) {
			scanf("%d", &complexity[j]);
		}
		int sp = *(std::min_element(complexity.begin(), complexity.end()));
		int hd = *(std::max_element(complexity.begin(), complexity.end()));
		std::transform(complexity.begin(), complexity.end(), pairs.begin(), pairs.begin(), CountSimplestOrHardestOp(sp, hd));
	}

	std::vector<int> verySimples;
	verySimples.reserve(problems);
	std::for_each(pairs.begin(), pairs.end(), CollectVerySimple(members, verySimples));
	if (verySimples.empty()) verySimples.push_back(0);

	for (int i = 0; i < verySimples.size(); i++) {
	    printf("%d%c", verySimples[i], (i!=verySimples.size()-1)?' ':'\n');
	}
	return 0;
}
