/*
 * Problem: Out of Hay
 * http://poj.org/problem?id=2395
 */

#include <algorithm>
#include <vector>
#include <limits>
#include <cstdio>

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
    int n, m;
    scanf("%d %d", &n, &m);
    WeightedDirectedGraphAsAdjMatrix<int> graph(n, 0x7FFFFFFF);
    while (m--) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        --u; --v;
        if (graph.GetWeight(u, v) > w) {
            graph.SetWeight(u, v, w);
            graph.SetWeight(v, u, w);
        }
    }
    Prim<WeightedDirectedGraphAsAdjMatrix<int> > prim(&graph);
    prim.Compute();
    const std::vector<int>& prevs = prim.TreeAsPrevs();
    int maxLength = 0;
    for (int i = 1; i < n; ++i) {
        if (maxLength < graph.GetWeight(prevs[i], i)) {
            maxLength = graph.GetWeight(prevs[i], i);
        }
    }
    printf("%d\n", maxLength);
    return 0;
}
