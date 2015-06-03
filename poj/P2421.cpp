/*
 * Problem: Constructing Roads
 * http://poj.org/problem?id=2421
 */

#include <vector>
#include <algorithm>
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
    void AddEdge(int u, int v, WeightType w) { mWeights[u * mNumVertex + v] = w; }
protected:
    int mNumVertex;
    std::vector<WeightType> mWeights;
};

template <class GraphType>
class Prim {
private:
    typedef typename GraphType::WeightType WeightType;
public:
    Prim(const GraphType *graph) : mGraph(graph), mDistances(graph->NumVertex()), mStates(graph->NumVertex()),
        mTotalWeight(0) { }
    void Compute() {
        int source = 0;
        for (int u = 0; u < mGraph->NumVertex(); ++u) {
            mDistances[u] = mGraph->GetWeight(source, u);
            mStates[u] = false;
        }
        mDistances[source] = 0;
        mStates[source] = true;
        mTotalWeight = 0;
        for (int i = 1; i < mGraph->NumVertex(); ++i) {
            WeightType min = std::numeric_limits<WeightType>::max();
            int k;
            for (int j = 0; j < mGraph->NumVertex(); ++j) {
                if (!mStates[j] && min > mDistances[j]) {
                    min = mDistances[j];
                    k = j;
                }
            }
            mStates[k] = true;
            mDistances[k] = min;
            mTotalWeight += min;
            for (int j = 0; j < mGraph->NumVertex(); ++j) {
                if (!mStates[j] && mGraph->GetWeight(k, j) < mDistances[j]) {
                    mDistances[j] = mGraph->GetWeight(k, j);
                }
            }
        }
    }
    WeightType TotalWeight() const {
        return mTotalWeight;
    }
private:
    const GraphType *mGraph;
    std::vector<WeightType> mDistances;
    std::vector<bool> mStates;
    WeightType mTotalWeight;
};

int main() {
    int n;
    scanf("%d", &n);
    WeightedDirectedGraphAsAdjMatrix<int> graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w;
            scanf("%d", &w);
            graph.AddEdge(i, j, w);
        }
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        --u; --v;
        graph.AddEdge(u, v, 0);
        graph.AddEdge(v, u, 0);
    }

    Prim<WeightedDirectedGraphAsAdjMatrix<int> > prim(&graph);
    prim.Compute();

    printf("%d\n", prim.TotalWeight());
    return 0;
}
