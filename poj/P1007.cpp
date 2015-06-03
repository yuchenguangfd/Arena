/*
 * Problem: DNA Sorting
 * http://poj.org/problem?id=1007
 */

#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

class CountInversion {
public:
    template <class T>
    int operator()(T *array, int size);
private:
    template <class T>
    int MergeSort(T *array, T *temp, int left, int right);
};

template <class T>
int CountInversion::operator()(T *array, int size) {
    T *temp = new T[size];
    int invs = MergeSort(array, temp, 0, size - 1);
    delete []temp;
    return invs;
}

template <class T>
int CountInversion::MergeSort(T *array, T *temp, int left, int right) {
    if (left >= right) return 0;
    int mid = (left + right) / 2;
    int invs = MergeSort(array, temp, left, mid) + MergeSort(array, temp, mid + 1, right);
    for (int i = left; i <= right; ++i) {
        temp[i] = array[i];
    }
    int i = left, j = mid+1, k = left;
    while (i <= mid && j <= right) {
        if (temp[i] <= temp[j]) {
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

template <class T>
void InsertionSort(T *array, int size) {
    for (int j = 1; j < size; ++j) {
        int i = j - 1;
        T key = array[j];
        while(i >= 0 && key < array[i]) {
            array[i + 1] = array[i];
            --i;
        }
        array[i+1] = key;
    }
}

struct DNA {
    int numInversion;
    std::string seq;
};

bool operator< (const DNA& lhs, const DNA& rhs) {
    return lhs.numInversion < rhs.numInversion;
}

int main() {
    CountInversion countInv;
	int n, m;
	scanf("%d %d", &n, &m);
	std::vector<DNA> dnas(m);
	for(int i = 0; i < m; ++i) {
	    char buff[64];
		scanf("%s", buff);
		dnas[i].seq = std::string(buff);
	    dnas[i].numInversion = countInv(buff, n);
	}
	InsertionSort(dnas.data(), dnas.size());
	for(int i = 0; i < m; ++i) {
	    printf("%s\n", dnas[i].seq.c_str());
	}
	return 0;
}
