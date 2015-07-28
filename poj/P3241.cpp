/*
 * Problem: Object Clustering
 * http://poj.org/problem?id=3241
 */

#include <algorithm>
#include <limits>
#include <memory>
#include <vector>
#include <cstdio>

template <class T>
class Point2D {
public:
    Point2D() : x(), y() { }
    Point2D(T x, T y) : x(x), y(y) { }
public:
    T x;
    T y;
};

template <class T>
class Point2DCompX {
public:
    const bool operator() (const Point2D<T>& lhs, const Point2D<T>& rhs) const {
        return (lhs.x != rhs.x) ? lhs.x < rhs.x : lhs.y < rhs.y;
    }
};

template <class T>
class Point2DWithId : public Point2D<T> {
public:
    Point2DWithId() : Point2D<T>(), id(0) { }
    Point2DWithId(T x, T y, int id) : Point2D<T>(x, y), id(id) { }
public:
    int id;
};

template <class T>
inline T ManhattanDistance(const Point2D<T>& lhs, const Point2D<T> rhs){
    T dx = lhs.x - rhs.x;
    T dy = lhs.y - rhs.y;
    return std::abs(dx) + std::abs(dy);
}

typedef Point2D<int> Point2D32I;
typedef Point2DWithId<int> Point2D32IWithId;

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

template <class T, class BinaryOp>
class BinaryIndexedTree {
public:
    BinaryIndexedTree(int size) : mData(size) { }
    void Update(int i, const T& rhs) {
        for(; i < mData.size(); i += Step(i)) {
           mData[i] = mBinaryOp(mData[i], rhs);
       }
    }
    T Query(int i) const {
        if (i < 0) return T();
        T res = mData[i];
        for(i -= Step(i); i >= 0; i -= Step(i)) {
            res = mBinaryOp(res, mData[i]);
        }
        return res;
    }
private:
    int Step(int i) const {
        int x = i + 1;
        return x & (-x);
    }
private:
    std::vector<T> mData;
    BinaryOp mBinaryOp;
};

template <class GraphType>
class ManhattanMSTGraphBuilder {
private:
    struct BitNode {
        int val;
        int pos;
        BitNode() : val(std::numeric_limits<int>::max()), pos(-1) { }
        BitNode(int val, int pos) : val(val), pos(pos) { }
    };
    struct BitOp {
        const BitNode& operator() (const BitNode& lhs, const BitNode& rhs) const {
            return (lhs.val < rhs.val) ? lhs : rhs;
        }
    };
public:
    void Build(const std::vector<Point2D32I>& origPoints) {
        std::vector<Point2D32IWithId> points;
        points.reserve(origPoints.size());
        for (std::size_t i = 0; i < origPoints.size(); ++i) {
            points.push_back(Point2D32IWithId(origPoints[i].x, origPoints[i].y, i));
        }
        mGraph = new GraphType(points.size());
        for(int region = 0; region < 4; ++region){
            if (region == 1 || region == 3) {
                for (int i = 0; i < points.size(); ++i) {
                    std::swap(points[i].x, points[i].y);
                }
            } else if (region == 2) {
                for (int i = 0; i < points.size(); ++i) {
                    points[i].x = -points[i].x;
                }
            }
            std::sort(points.begin(), points.end(), Point2DCompX<int>());
            std::vector<int> thresholds(points.size());
            for (std::size_t i = 0; i < points.size(); ++i) {
                thresholds[i] = points[i].y - points[i].x;
            }
            std::sort(thresholds.begin(), thresholds.end());
            int m = std::unique(thresholds.begin(), thresholds.end()) - thresholds.begin();
            thresholds.resize(m);
            BinaryIndexedTree<BitNode, BitOp> bit(m);
            for (int i = points.size() - 1; i >= 0; --i) {
                int key = points[i].y - points[i].x;
                int pos = std::lower_bound(thresholds.begin(), thresholds.end(), key) - thresholds.begin();
                int otherId = bit.Query(m-1-pos).pos;
                if (otherId != -1) {
                    mGraph->AddEdge(points[i].id, points[otherId].id, ManhattanDistance(points[i], points[otherId]));
                }
                bit.Update(m-1-pos, BitNode(points[i].x + points[i].y, i));
            }
        }
    }
    GraphType* GetGraph() const {
        return mGraph;
    }
private:
    GraphType* mGraph;
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
    int n, k;
    scanf("%d %d", &n, &k);
    std::vector<Point2D32I> points(n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    ManhattanMSTGraphBuilder<Graph> builder;
    builder.Build(points);

    std::auto_ptr<Graph> graph(builder.GetGraph());
    Kruskal<Graph> kruskal(graph.get());
    kruskal.Compute();
    int ans = (kruskal.TreeAsEdges())[n - 1 - k]->weight;
    printf("%d\n", ans);
    return 0;
}
