/*
 * Problem: Stockbroker Grapevine
 * http://poj.org/problem?id=1125
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
    const int INF = 9999999;
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        WeightedDirectedGraphAsAdjMatrix<int> graph(n, INF);
        for (int u = 0; u < n; ++u) {
            int k;
            scanf("%d", &k);
            while (k--) {
                int v, w;
                scanf("%d %d", &v, &w);
                --v;
                graph.SetWeight(u, v, w);
            }
        }

        FloydWarshall<WeightedDirectedGraphAsAdjMatrix<int> > floyd(&graph);
        floyd.Compute();

        int minTimeSrc, minTime = INF;
        bool disjoint = true;
        for (int i = 0; i < n; ++i) {
            int w = 0;
            for (int j = 0; j < n; ++j) {
                if (i != j && w < floyd.Distance(i, j)) {
                    w = floyd.Distance(i, j);
                }
            }
            if (w < INF) {
                disjoint = false;
                if (w < minTime) {
                    minTime = w;
                    minTimeSrc = i;
                }
            }
        }
        if (!disjoint) {
            printf("%d %d\n", minTimeSrc+1, minTime);
        } else {
            printf("disjoint\n");
        }
    }
    return 0;
}
