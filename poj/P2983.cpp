/*
 * Problem: Is the Information Reliable?
 * http://poj.org/problem?id=2983
 */

#include <vector>
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
    void AddEdge(const WeightedEdge<T>& edge) { mEdgeList.push_back(edge); }
    const WeightedEdge<T>& GetEdge(int i) const { return mEdgeList[i]; }
protected:
    int mNumVertex;
    std::vector<WeightedEdge<T> > mEdgeList;
};

template <class T>
class BellmanFord {
public:
    BellmanFord(const WeightedDirectedGraphAsEdgeList<T>* graph, int source) :
        mGraph(graph), mSource(source), mDistances(graph->NumVertex()),
        mExistNegativeCycle(false) { }
    void Compute() {
        const T DISTANCE_INF = 100000;
        for (int i = 0; i < mGraph->NumVertex(); ++i) {
            mDistances[i] = DISTANCE_INF;
        }
        mDistances[mSource] = 0;
        for (int i = 1; i < mGraph->NumVertex(); ++i) {
            bool relaxed = false;
            for (int j = 0; j < mGraph->NumEdge(); ++j) {
                const WeightedEdge<T>& edge = mGraph->GetEdge(j);
                if (mDistances[edge.u] + edge.weight < mDistances[edge.v]) {
                    mDistances[edge.v] = mDistances[edge.u] + edge.weight;
                    relaxed = true;
                }
            }
            if (!relaxed) break;
        }
        mExistNegativeCycle = false;
        for (int j = 0; j < mGraph->NumEdge(); ++j) {
            const WeightedEdge<T>& edge = mGraph->GetEdge(j);
            if (mDistances[edge.u] + edge.weight < mDistances[edge.v]) {
                mExistNegativeCycle = true;
                break;
            }
        }
    }
    bool ExistNegativeCycle() const { return mExistNegativeCycle; }
private:
    const WeightedDirectedGraphAsEdgeList<T> *mGraph;
    int mSource;
    std::vector<T> mDistances;
    bool mExistNegativeCycle;
};

int main() {
    while (true) {
        int n, m;
        if (scanf("%d %d", &n, &m) == EOF) break;
        WeightedDirectedGraphAsEdgeList<int> graph(n, m);
        for (int i = 0; i < m; ++i) {
            char tip[3];
            scanf("%s", tip);
            int u, v, w;
            if (tip[0] == 'P') {
                scanf("%d %d %d", &u, &v, &w);
                --u; --v;
                graph.AddEdge(WeightedEdge<int>(v, u, w));
                graph.AddEdge(WeightedEdge<int>(u, v, -w));
            } else {
                scanf("%d%d", &u, &v);
                --u; --v;
                graph.AddEdge(WeightedEdge<int>(u, v, -1));
            }
        }

        BellmanFord<int> SSSP(&graph, 0);
        SSSP.Compute();
        if (SSSP.ExistNegativeCycle()) {
            printf("Unreliable\n");
        } else {
            printf("Reliable\n");
        }
    }
    return 0;
}
