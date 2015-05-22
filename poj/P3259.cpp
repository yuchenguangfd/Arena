/*
 * Problem: Wormholes
 * http://poj.org/problem?id=3259
 */

#include <vector>
#include <limits>
#include <cstdio>

template <class T>
struct WeightedEdge {
    int u, v;
    T weight;
    WeightedEdge(int u, int v, T weight) : u(u), v(v), weight(weight) { }
};

template <class T>
class WeightedDirectedGraphAsEdgeList {
public:
    WeightedDirectedGraphAsEdgeList(int numVertex, int maxNumEdge = 0) :
        mNumVertex(numVertex) {
        mEdgeList.reserve(maxNumEdge);
    }
    int NumVertex() const { return mNumVertex; }
    int NumEdge() const { return mEdgeList.size(); }
    void AddEdge(int u, int v, T weight) { AddEdge(WeightedEdge<T>(u, v, weight)); }
    void AddEdge(const WeightedEdge<T>& edge) { mEdgeList.push_back(edge); }
    const WeightedEdge<T>& GetEdge(int i) const { return mEdgeList[i]; }
protected:
    int mNumVertex;
    std::vector<WeightedEdge<T> > mEdgeList;
};

template <class T>
class BellmanFord {
public:
    BellmanFord(const WeightedDirectedGraphAsEdgeList<T>* graph, int source,
            T infDistanceValue = std::numeric_limits<T>::max()) :
        mGraph(graph), mSource(source), mInfDistanceValue(infDistanceValue),
        mDistances(graph->NumVertex()), mExistNegativeCycle(false) { }
    void Compute() {
        for (int i = 0; i < mGraph->NumVertex(); ++i) {
            mDistances[i] = mInfDistanceValue;
        }
        mDistances[mSource] = 0;
        for (int i = 1; i < mGraph->NumVertex(); ++i) {
            bool relaxed = false;
            for (int j = 0; j < mGraph->NumEdge(); ++j) {
                const WeightedEdge<T>& edge = mGraph->GetEdge(j);
                if (mDistances[edge.u] < mDistances[edge.v] - edge.weight) {
                    mDistances[edge.v] = mDistances[edge.u] + edge.weight;
                    relaxed = true;
                }
            }
            if (!relaxed) break;
        }
        mExistNegativeCycle = false;
        for (int j = 0; j < mGraph->NumEdge(); ++j) {
            const WeightedEdge<T>& edge = mGraph->GetEdge(j);
            if (mDistances[edge.u] < mDistances[edge.v] - edge.weight) {
                mExistNegativeCycle = true;
                break;
            }
        }
    }
    bool ExistNegativeCycle() const { return mExistNegativeCycle; }
private:
    const WeightedDirectedGraphAsEdgeList<T> *mGraph;
    int mSource;
    T mInfDistanceValue;
    std::vector<T> mDistances;
    bool mExistNegativeCycle;
};

int main() {
    int numCase;
    scanf("%d", &numCase);
    while (numCase--) {
        int n, m, w;
        scanf("%d %d %d", &n, &m, &w);
        WeightedDirectedGraphAsEdgeList<int> graph(n, m*2+w);
        for (int i = 0; i < m; ++i) {
            int u, v, time;
            scanf("%d %d %d", &u, &v, &time);
            --u; --v;
            graph.AddEdge(u, v, time);
            graph.AddEdge(v, u, time);
        }
        for (int i = 0; i < w; ++i) {
            int u, v, time;
            scanf("%d %d %d", &u, &v, &time);
            --u; --v;
            graph.AddEdge(u, v, -time);
        }
        BellmanFord<int> SSSP(&graph, 0, 0);
        SSSP.Compute();
        printf("%s\n", (SSSP.ExistNegativeCycle()) ? "YES" : "NO");
    }
    return 0;
}
