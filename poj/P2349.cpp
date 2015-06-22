/*
 * Problem: Arctic Network
 * http://poj.org/problem?id=2349
 */

#include <vector>
#include <cmath>
#include <cstdio>

template <class T>
class Point2D {
public:
    Point2D() : x(), y() { }
    Point2D(T x, T y) { this->x = x; this->y = y;}
public:
    T x;
    T y;
};

template <class T>
inline T Distance(const Point2D<T> &lhs, const Point2D<T>& rhs) {
    T dx = lhs.x - rhs.x;
    T dy = lhs.y - rhs.y;
    return sqrt(dx*dx + dy*dy);
}

typedef Point2D<double> Point2D64F;

template <class WeightType>
struct WeightedEdge {
    int u, v;
    WeightType weight;
    WeightedEdge(int u, int v, WeightType w) : u(u), v(v), weight(w) { }
};

template <class T>
class WeightedDirectedGraphAsEdgeList {
public:
    typedef T WeightType;
    typedef WeightedEdge<T> EdgeType;
    WeightedDirectedGraphAsEdgeList(int numVertex, int maxNumEdge = 0) :
        mNumVertex(numVertex) {
        mEdgeList.reserve(maxNumEdge);
    }
    int NumVertex() const { return mNumVertex; }
    int NumEdge() const { return mEdgeList.size(); }
    void AddEdge(int u, int v, WeightType w) { AddEdge(EdgeType(u, v, w)); }
    void AddEdge(const EdgeType& edge) { mEdgeList.push_back(edge); }
    const EdgeType& GetEdge(int i) const { return mEdgeList[i]; }
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

int main() {
    int numCase;
    scanf("%d", &numCase);
    while (numCase--) {
        int numChannel, n;
        scanf("%d %d", &numChannel, &n);
        std::vector<Point2D64F> points(n);
        for (int i = 0; i < n; ++i) {
            scanf("%lf %lf", &points[i].x, &points[i].y);
        }

        WeightedDirectedGraphAsEdgeList<double> graph(n, n*(n-1)/2);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                graph.AddEdge(i, j, Distance(points[i], points[j]));
            }
        }

        Kruskal<WeightedDirectedGraphAsEdgeList<double> > kruskal(&graph);
        kruskal.Compute();
        const std::vector<const WeightedDirectedGraphAsEdgeList<double>::EdgeType*>& edges
            = kruskal.TreeAsEdges();
        double ans = edges[n - numChannel - 1]->weight;
        printf("%0.2f\n", ans);
    }
    return 0;
}
