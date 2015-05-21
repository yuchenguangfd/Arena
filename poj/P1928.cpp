/*
 * Problem: The Peanuts
 * http://poj.org/problem?id=1928
 */

#include <vector>
#include <cstdio>

struct Peanut {
    int x, y;
    int num;
};

bool operator< (const Peanut& lhs, const Peanut& rhs) {
    return lhs.num > rhs.num;
}

template <class T>
void BubbleSort(T *array, int size) {
    bool isSorted = false;
    for (int i = 0; !isSorted && i < size; ++i) {
        isSorted = true;
        for (int j = size - 1; j > i; --j) {
            if (array[j] < array[j-1]) {
                T temp = array[j];
                array[j] = array[j-1];
                array[j-1] = temp;
                isSorted = false;
            }
        }
    }
}

inline int Abs(int x) {
    return x < 0 ? -x : x;
}

int main() {
    int numCase;
    scanf("%d", &numCase);
    for (int caseId = 0; caseId < numCase; ++caseId) {
        int n, m, time;
        scanf("%d %d %d", &n, &m, &time);
        std::vector<Peanut> peanuts;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                int num;
                scanf("%d", &num);
                if(num > 0) {
                    Peanut p;
                    p.x = i; p.y = j; p.num = num;
                    peanuts.push_back(p);
                }
            }
        }

        BubbleSort(peanuts.data(), peanuts.size());

        int count = 0;
        int x = 0;
        int y = peanuts[0].y;
        for(int i = 0; i < peanuts.size(); ++i) {
            int go = Abs(x-peanuts[i].x) + Abs(y-peanuts[i].y);
            int back = peanuts[i].x;
            if(time >= go + back + 1) {
                x = peanuts[i].x;
                y = peanuts[i].y;
                count += peanuts[i].num;
                time -= go + 1;
            } else {
                break;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}
