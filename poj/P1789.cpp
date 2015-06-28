/*
 * Problem: Truck History
 * http://poj.org/problem?id=1789
 */

#include <iterator>
#include <vector>
#include <string>
#include <limits>
#include <cstdio>

template <class Iterator>
typename std::iterator_traits<Iterator>::difference_type
    CountDiff(Iterator seq1First, Iterator seq1Last, Iterator seq2First) {
    typename std::iterator_traits<Iterator>::difference_type count = 0;
    for (; seq1First != seq1Last; ++seq1First, ++seq2First) {
        if (!(*seq1First == *seq2First)) ++count;
    }
    return count;
}

template <class T>
class WeightedDirectedGraphAsAdjMatrix {
public:
    typedef T WeightType;
    WeightedDirectedGraphAsAdjMatrix(int numVertex, WeightType initWeight = WeightType()) :
        mNumVertex(numVertex), mWeights(numVertex * numVertex) {
        std::fill(mWeights.begin(), mWeights.end(), initWeight);
    }
    int NumVertex() const { return mNumVertex; }
    WeightType GetWeight(int u, int v) const { return mWeights[u * mNumVertex + v]; }
    void SetWeight(int u, int v, WeightType w) { mWeights[u * mNumVertex + v] = w; }
    WeightType* operator[] (int u) { return &mWeights[u * mNumVertex]; }
    const WeightType* operator[] (int u) const { return &mWeights[u * mNumVertex]; }
protected:
    int mNumVertex;
    std::vector<WeightType> mWeights;
};

template <class GraphType>
class Prim {
private:
    typedef typename GraphType::WeightType WeightType;
public:
    Prim(const GraphType *graph) : mGraph(graph), mDists(graph->NumVertex()), mStates(graph->NumVertex()),
        mPrevs(graph->NumVertex()), mTotalWeight(0) { }
    void Compute() {
        int source = 0;
        for (int u = 0; u < mGraph->NumVertex(); ++u) {
            mDists[u] = mGraph->GetWeight(source, u);
            mStates[u] = false;
            mPrevs[u] = source;
        }
        mDists[source] = 0;
        mStates[source] = true;
        mTotalWeight = 0;
        for (int i = 1; i < mGraph->NumVertex(); ++i) {
            WeightType min = std::numeric_limits<WeightType>::max();
            int k;
            for (int j = 0; j < mGraph->NumVertex(); ++j) {
                if (!mStates[j] && min > mDists[j]) {
                    min = mDists[j];
                    k = j;
                }
            }
            mStates[k] = true;
            mDists[k] = min;
            mTotalWeight += min;
            for (int j = 0; j < mGraph->NumVertex(); ++j) {
                if (!mStates[j] && mGraph->GetWeight(k, j) < mDists[j]) {
                    mDists[j] = mGraph->GetWeight(k, j);
                    mPrevs[j] = k;
                }
            }
        }
    }
    WeightType TotalWeight() const {
        return mTotalWeight;
    }
    const std::vector<int>& TreeAsPrevs() const {
        return mPrevs;
    }
private:
    const GraphType *mGraph;
    std::vector<WeightType> mDists;
    std::vector<bool> mStates;
    std::vector<int> mPrevs;
    WeightType mTotalWeight;
};

int main() {
    char buff[16];
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        std::vector<std::string> names;
        for (int i = 0; i < n; ++i) {
            scanf("%s", buff);
            names.push_back(std::string(buff));
        }

        WeightedDirectedGraphAsAdjMatrix<int> graph(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int diff = CountDiff(names[i].begin(), names[i].end(), names[j].begin());
                graph.SetWeight(i, j, diff);
                graph.SetWeight(j, i, diff);
            }
        }

        Prim<WeightedDirectedGraphAsAdjMatrix<int> > prim(&graph);
        prim.Compute();
        printf("The highest possible quality is 1/%d.\n", prim.TotalWeight());
    }
    return 0;
}
