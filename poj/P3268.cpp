/*
 * Problem: Silver Cow Party
 * http://poj.org/problem?id=3268
 */

#include <memory>
#include <limits>
#include <vector>
#include <cstdio>

template <class T, class Alloc = std::allocator<T> >
class WeightedDirectedGraphAsAdjMatrix {
public:
    WeightedDirectedGraphAsAdjMatrix(int numVertex, T initWeight = T()) : mNumVertex(numVertex) {
        int size = mNumVertex * mNumVertex;
        Alloc alloc;
        mData = alloc.allocate(size);
        for (int i = 0; i < size; ++i) {
            mData[i] = initWeight;
        }
    }
    ~WeightedDirectedGraphAsAdjMatrix() {
        int size = mNumVertex * mNumVertex;
        Alloc alloc;
        alloc.deallocate(mData, size);
    }
    int NumVertex() const { return mNumVertex; }
    void AddEdge(int u, int v, T weight) { mData[u * mNumVertex + v] = weight; }
    T GetWeight(int u, int v) const { return mData[u * mNumVertex + v]; }
private:
    int mNumVertex;
    T *mData;
};

template <class T, class Alloc = std::allocator<T> >
class Dijkstra {
public:
    Dijkstra(const WeightedDirectedGraphAsAdjMatrix<T, Alloc>* graph, int source) :
        mGraph(graph), mSource(source), mDistances(graph->NumVertex()),
        mStates(graph->NumVertex()) { }
    void Compute() {
        for (int u = 0; u < mGraph->NumVertex(); ++u) {
            mDistances[u] = mGraph->GetWeight(mSource, u);
            mStates[u] = false;
        }
        mDistances[mSource] = T();
        mStates[mSource] = true;
        for (int i = 1; i < mGraph->NumVertex(); ++i) {
            T min = std::numeric_limits<T>::max();
            int k;
            for (int j = 0; j < mGraph->NumVertex(); ++j) {
                if (!mStates[j] && min > mDistances[j]) {
                    min = mDistances[j];
                    k = j;
                }
            }
            mStates[k] = true;
            for (int j = 0; j < mGraph->NumVertex(); ++j) {
                if (!mStates[j] && mDistances[j] > mDistances[k] + mGraph->GetWeight(k, j)) {
                    mDistances[j] = mDistances[k] + mGraph->GetWeight(k, j);
                }
            }
        }
    }
    T ShortestDistance(int v) const { return mDistances[v]; }
private:
    const WeightedDirectedGraphAsAdjMatrix<T, Alloc> *mGraph;
    int mSource;
    std::vector<T, Alloc> mDistances;
    std::vector<bool, Alloc> mStates;
};

int main() {
    int n, m, source;
    scanf("%d%d%d", &n, &m, &source);
    --source;
    WeightedDirectedGraphAsAdjMatrix<int> graph1(n, 100000000);
    WeightedDirectedGraphAsAdjMatrix<int> graph2(n, 100000000);
    while (m--) {
        int s, t, w;
        scanf("%d%d%d", &s, &t, &w);
        --s;
        --t;
        graph1.AddEdge(s, t, w);
        graph2.AddEdge(t, s, w);
    }
    Dijkstra<int> SSSP1(&graph1, source);
    SSSP1.Compute();
    Dijkstra<int> SSSP2(&graph2, source);
    SSSP2.Compute();
    int latest = 0;
    for (int i = 0; i < n; ++i) {
        if (SSSP1.ShortestDistance(i) + SSSP2.ShortestDistance(i) > latest) {
            latest = SSSP1.ShortestDistance(i) + SSSP2.ShortestDistance(i);
        }
    }
    printf("%d\n", latest);
    return 0;
}
