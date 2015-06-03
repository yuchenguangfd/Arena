/*
 * Problem: Tangled in Cables
 * http://poj.org/problem?id=2075
 */

#include <vector>
#include <string>
#include <limits>
#include <algorithm>
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
    void AddEdge(int u, int v, WeightType weight) { mWeights[u * mNumVertex + v] = weight; }
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
    double cableLength;
    scanf("%lf", &cableLength);
    int n;
    scanf("%d", &n);
    std::vector<std::string> names(n);
    for (int i = 0; i < n; ++i) {
        char buff[32];
        scanf("%s", buff);
        names[i] = std::string(buff);
    }
    WeightedDirectedGraphAsAdjMatrix<double> graph(n, 1e100);
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        char buff[32];
        scanf("%s", buff);
        int u = std::find(names.begin(), names.end(), std::string(buff)) - names.begin();
        scanf("%s", buff);
        int v = std::find(names.begin(), names.end(), std::string(buff)) - names.begin();
        double w;
        scanf("%lf", &w);
        graph.AddEdge(u, v, w);
        graph.AddEdge(v, u, w);
    }

    Prim<WeightedDirectedGraphAsAdjMatrix<double> > prim(&graph);
    prim.Compute();

    if (prim.TotalWeight() > cableLength) {
        printf("Not enough cable\n");
    } else {
        printf("Need %0.1f miles of cable\n", prim.TotalWeight());
    }
}
