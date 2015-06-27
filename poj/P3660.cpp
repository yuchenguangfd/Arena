/*
 * Problem: Cow Contest
 * http://poj.org/problem?id=3660
 */

#include <algorithm>
#include <vector>
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
    WeightType* operator[] (int u) { return &mWeights[u * mNumVertex]; }
    const WeightType* operator[] (int u) const { return &mWeights[u * mNumVertex]; }
protected:
    int mNumVertex;
    std::vector<WeightType> mWeights;
};

template <class GraphType>
class FloydWarshall {
private:
    typedef typename GraphType::WeightType WeightType;
public:
    FloydWarshall(const GraphType *graph) : mGraph(graph), mDists(graph->NumVertex()) { }
    virtual ~FloydWarshall() { }
    void Compute() {
        mDists = *mGraph;
        int n = mGraph->NumVertex();
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    Relax(i, j, k);
                }
            }
        }
    }
    WeightType Distance(int u, int v) {
        return mDists.GetWeight(u, v);
    }
protected:
    virtual void Relax(int i, int j, int k) {
        mDists[i][j] = std::min(mDists[i][j], mDists[i][k] + mDists[k][j]);
    }
protected:
    const GraphType *mGraph;
    GraphType mDists;
};

int main() {
    const int OO = 1000000;
    int n, m;
    scanf("%d%d", &n, &m);

    WeightedDirectedGraphAsAdjMatrix<int> graph(n, OO);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u; --v;
        graph.SetWeight(u, v, 1);
    }
    for (int i = 0; i < n; ++i) {
        graph.SetWeight(i, i, 1);
    }

    FloydWarshall<WeightedDirectedGraphAsAdjMatrix<int> > floyd(&graph);
    floyd.Compute();
    int total = 0;
    for (int i = 0; i < n; ++i) {
        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (floyd.Distance(i, j) < OO || floyd.Distance(j, i) < OO) {
                ++count;
            }
        }
        if (count == n) {
            ++total;
        }
    }
    printf("%d\n", total);
    return 0;
}
