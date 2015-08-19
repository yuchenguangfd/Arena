/*
 * Problem: Ultra-QuickSort
 * http://poj.org/problem?id=2299
 */

#include <vector>
#include <cstdio>

typedef unsigned long long uint64;

class CountInversion {
public:
    template <class T>
    uint64 operator()(T *array, int size) {
        T *temp = new T[size];
        uint64 invs = MergeSort(array, temp, 0, size - 1);
        delete []temp;
        return invs;
    }
private:
    template <class T>
    uint64 MergeSort(T *array, T *temp, int left, int right) {
        if (left >= right) return 0;
        int mid = (left + right) / 2;
        uint64 invs = MergeSort(array, temp, left, mid) + MergeSort(array, temp, mid + 1, right);
        for (int i = left; i <= right; ++i) {
            temp[i] = array[i];
        }
        int i = left, j = mid+1, k = left;
        while (i <= mid && j <= right) {
            if (temp[i] < temp[j]) {
                array[k++] = temp[i++];
            } else {
                invs += mid - i + 1;
                array[k++] = temp[j++];
            }
        }
        while (i <= mid) array[k++] = temp[i++];
        while (j <= right) array[k++] = temp[j++];
        return invs;
    }
};

int main() {
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        std::vector<int> array(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &array[i]);
        }
        printf("%lld\n", CountInversion()(array.data(), array.size()));
    }
    return 0;
}
