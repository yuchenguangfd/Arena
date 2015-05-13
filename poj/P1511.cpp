/*
 * Problem: Invitation Cards
 * http://poj.org/problem?id=1511
 */

#include <memory>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdio>

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) { }
};

template <class Alloc = std::allocator<int> >
class DirectedGraphAsAdjList {
public:
    DirectedGraphAsAdjList(int numVertex, int maxNumEdge) : mNumVertex(numVertex), mMaxNumEdge(maxNumEdge),
            mNumEdge(0) {
        Alloc alloc;
        mHeads = alloc.allocate(mNumVertex);
        std::fill(mHeads, mHeads + mNumVertex, -1);
        mEdges = alloc.allocate(mMaxNumEdge);
        mWeights = alloc.allocate(mMaxNumEdge);
        mNexts = alloc.allocate(mMaxNumEdge);
    }
    ~DirectedGraphAsAdjList() {
        Alloc alloc;
        alloc.deallocate(mHeads, mNumVertex);
        alloc.deallocate(mEdges, mMaxNumEdge);
        alloc.deallocate(mWeights, mMaxNumEdge);
        alloc.deallocate(mNexts, mMaxNumEdge);
    }
    int NumVertex() const  { return mNumVertex; }
    int NumEdge() const { return mNumEdge; }
    void AddEdge(const Edge &edge)  {
        mEdges[mNumEdge] = edge.v;
        mWeights[mNumEdge] = edge.w;
        mNexts[mNumEdge] = mHeads[edge.u];
        mHeads[edge.u] = mNumEdge;
        ++mNumEdge;
    }
    class EdgeIterator {
    public:
        EdgeIterator(const DirectedGraphAsAdjList *graph, int vertex) : mGraph(graph), mCurrPtr(graph->mHeads[vertex]) { }
        bool HasNext() { return mCurrPtr != -1; }
        void NextEdge(int *v, int *w) {
            *v = mGraph->mEdges[mCurrPtr];
            *w = mGraph->mWeights[mCurrPtr];
            mCurrPtr = mGraph->mNexts[mCurrPtr];
        }
    private:
        const DirectedGraphAsAdjList *mGraph;
        int mCurrPtr;
    };

    EdgeIterator GetEdgeIteraror(int vertex) const {
        return EdgeIterator(this, vertex);
    }
private:
    int mNumVertex;
    int mNumEdge;
    int mMaxNumEdge;
    int *mHeads;
    int *mEdges;
    int *mWeights;
    int *mNexts;
};

void SPFA(const DirectedGraphAsAdjList<>& graph, int source, std::vector<int>& distance) {
    std::vector<bool> isInQueue(graph.NumVertex());
    std::queue<int> qq;
    std::fill(distance.begin(), distance.end(), 0x7fffffff);
    distance[source] = 0;
    isInQueue[source] = true;
    qq.push(source);
    while (!qq.empty()) {
        int u = qq.front();
        qq.pop();
        isInQueue[u] = false;
        DirectedGraphAsAdjList<>::EdgeIterator iter = graph.GetEdgeIteraror(u);
        while (iter.HasNext()) {
            int v, w;
            iter.NextEdge(&v, &w);
            if (distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                if (!isInQueue[v]) {
                    isInQueue[v] = true;
                    qq.push(v);
                }
            }
        }
    }
}

int main() {
    int numCase;
    scanf("%d", &numCase);
    for (int caseId = 0; caseId < numCase; ++caseId) {
        int numStation, numPath;
        scanf("%d %d", &numStation, &numPath);
        DirectedGraphAsAdjList<> graph1(numStation, numPath);
        DirectedGraphAsAdjList<> graph2(numStation, numPath);
        for (int i = 0; i < numPath; ++i) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            --u; --v;
            graph1.AddEdge(Edge(u, v, w));
            graph2.AddEdge(Edge(v, u, w));
        }
        std::vector<int> distance1(numStation);
        SPFA(graph1, 0, distance1);
        long long result = 0;
        for (int i = 0; i < numStation; ++i) {
            result += distance1[i];
        }
        std::vector<int> distance2(numStation);
        SPFA(graph2, 0, distance2);
        for (int i = 0; i < numStation; ++i) {
            result += distance2[i];
        }
        printf("%lld\n", result);
    }
    return 0;
}
