/*
 * Problem: Slim Span
 * http://poj.org/problem?id=3522
 */

#include <algorithm>
#include <limits>
#include <vector>
#include <cstdio>

template <class WeightType>
struct WeightedEdge {
    int u, v;
    WeightType weight;
    WeightedEdge(int u, int v, WeightType w) : u(u), v(v), weight(w) { }
};

template <class WeightType>
bool operator< (const WeightedEdge<WeightType>& lhs, const WeightedEdge<WeightType>& rhs) {
    return lhs.weight < rhs.weight;
}

template <class T>
class WeightedDirectedGraphAsEdgeList {
public:
    typedef T WeightType;
    typedef WeightedEdge<T> EdgeType;
    WeightedDirectedGraphAsEdgeList(int numVertex, int maxNumEdge = 0) :
        mNumVertex(numVertex) {
        mEdgeList.reserve(maxNumEdge);
    }
    template <class Iterator>
    WeightedDirectedGraphAsEdgeList(int numVertex, Iterator begin, Iterator end) :
        mNumVertex(numVertex),
        mEdgeList(begin, end) { }
    int NumVertex() const { return mNumVertex; }
    int NumEdge() const { return mEdgeList.size(); }
    void AddEdge(int u, int v, WeightType w) { AddEdge(EdgeType(u, v, w)); }
    void AddEdge(const EdgeType& edge) { mEdgeList.push_back(edge); }
    const EdgeType& GetEdge(int i) const { return mEdgeList[i]; }
    typename std::vector<EdgeType>::iterator Begin() { return mEdgeList.begin(); }
    typename std::vector<EdgeType>::iterator End() { return mEdgeList.end(); }
protected:
    int mNumVertex;
    std::vector<EdgeType> mEdgeList;
};

template <class GraphType>
class Kruskal {
private:
    typedef typename GraphType::WeightType WeightType;
    typedef typename GraphType::EdgeType EdgeType;
public:
    Kruskal(const GraphType *graph) : mGraph(graph), mHeap(graph->NumEdge()), mUFSet(graph->NumVertex())
        , mTotalWeight(0) {
        mTreeEdges.reserve(mGraph->NumVertex() - 1);
    }
    void Compute() {
        UFSetInit();
        HeapInit();
        mTreeEdges.clear();
        int count = 0;
        while (count < mGraph->NumVertex() - 1 && mHeap.size() > 0) {
            const EdgeType* minEdge = HeapExtract();
            if (UFSetUnion(minEdge->u, minEdge->v)) {
                mTreeEdges.push_back(minEdge);
                mTotalWeight += minEdge->weight;
                ++count;
            }
        }
    }
    WeightType TotalWeight() const { return mTotalWeight; }
    bool IsTree() const { return mTreeEdges.size() == mGraph->NumVertex() - 1; }
    const std::vector<const EdgeType*>& TreeAsEdges() const { return mTreeEdges; }
private:
    void UFSetInit() {
        std::fill(mUFSet.begin(), mUFSet.end(), -1);
    }
    bool UFSetUnion(int a, int b) {
        int root1 = UFSetFind(a);
        int root2 = UFSetFind(b);
        if (root1 == root2) return false;
        if (mUFSet[root1] < mUFSet[root2]) {
            mUFSet[root1] += mUFSet[root2];
            mUFSet[root2] = root1;
        } else {
            mUFSet[root2] += mUFSet[root1];
            mUFSet[root1] = root2;
        }
        return true;
    }
    int UFSetFind(int a) {
        int root = a;
        while (mUFSet[root] >= 0) {
            root = mUFSet[root];
        }
        while (mUFSet[a] >= 0) {
            int tmp = mUFSet[a];
            mUFSet[a] = root;
            a = tmp;
        }
        return root;
    }
    void HeapInit() {
        for (int i = 0; i < mGraph->NumEdge(); ++i) {
            mHeap[i] = &(mGraph->GetEdge(i));
        }
        for (int i = mGraph->NumEdge() / 2 - 1; i >= 0; --i) {
            HeapShiftDown(i);
        }
    }
    const EdgeType* HeapExtract() {
        const EdgeType* res = mHeap[0];
        mHeap[0] = mHeap[mHeap.size() - 1];
        mHeap.pop_back();
        HeapShiftDown(0);
        return res;
    }
    void HeapShiftDown(int pos) {
        const EdgeType* key = mHeap[pos];
        int child = 2 * pos + 1;
        while (child < mHeap.size()) {
            if (child + 1 < mHeap.size() && mHeap[child + 1]->weight < mHeap[child]->weight) {
                ++child;
            }
            if (mHeap[child]->weight < key->weight) {
                mHeap[pos] = mHeap[child];
                pos = child;
                child = pos * 2 + 1;
            } else {
                break;
            }
        }
        mHeap[pos] = key;
    }

private:
    const GraphType *mGraph;
    std::vector<int> mUFSet;
    std::vector<const EdgeType*> mHeap;
    std::vector<const EdgeType*> mTreeEdges;
    WeightType mTotalWeight;
};

typedef WeightedDirectedGraphAsEdgeList<int> Graph;

int main() {
    while (true) {
        int n, m;
        scanf("%d %d", &n, &m);
        if (n == 0 && m == 0) break;
        Graph graph(n, m);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            --u; --v;
            graph.AddEdge(u, v, w);
        }
        std::sort(graph.Begin(), graph.End());
        int minSlimness = std::numeric_limits<int>::max();
        for (int i = 0; i <= m - n + 1; ++i) {
            Graph graph2(n, graph.Begin() + i, graph.End());
            Kruskal<Graph> kruskal(&graph2);
            kruskal.Compute();
            if (!kruskal.IsTree()) break;
            const std::vector<const Graph::EdgeType*>& edges = kruskal.TreeAsEdges();
            int slimness = edges[edges.size() - 1]->weight - edges[0]->weight;
            minSlimness = std::min(slimness, minSlimness);
        }
        if (minSlimness < std::numeric_limits<int>::max()) {
            printf("%d\n", minSlimness);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}
