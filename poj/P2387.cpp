/*
 * Problem: Til the Cows Come Home
 * http://poj.org/problem?id=2387
 */

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
    virtual ~WeightedDirectedGraphAsAdjMatrix() {
        int size = mNumVertex * mNumVertex;
        Alloc alloc;
        alloc.deallocate(mData, size);
    }
    int NumVertex() const { return mNumVertex; }
    T GetWeight(int u, int v) const { return mData[u * mNumVertex + v]; }
    virtual void AddEdge(int u, int v, T weight) { mData[u * mNumVertex + v] = weight; }
protected:
    int mNumVertex;
    T *mData;
};

template <class T, class Alloc = std::allocator<T> >
class Dijkstra {
public:
    Dijkstra(const WeightedDirectedGraphAsAdjMatrix<T, Alloc>* graph, int source) :
        mGraph(graph), mSource(source), mDistances(graph->NumVertex()), mStates(graph->NumVertex()) { }
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

class Graph : public WeightedDirectedGraphAsAdjMatrix<int> {
public:
    Graph(int numVertex, int initWeight) : WeightedDirectedGraphAsAdjMatrix<int>(numVertex, initWeight) { }
    virtual void AddEdge(int u, int v, int weight) {
        if (mData[u * mNumVertex + v] > weight) {
            mData[u * mNumVertex + v] = weight;
        }
    }
};

int main() {
    int N, T;
    scanf("%d%d", &T, &N);
    Graph graph(N, 10000000);
    while (T--) {
        int s, t, w;
        scanf("%d%d%d", &s, &t, &w);
        --s; --t;
        graph.AddEdge(s, t, w);
        graph.AddEdge(t, s, w);
    }
    Dijkstra<int> SSSP(&graph, 0);
    SSSP.Compute();
    printf("%d\n", SSSP.ShortestDistance(N-1));
    return 0;
}
