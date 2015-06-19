/*
 * Problem: Highways
 * http://poj.org/problem?id=1751
 */

#include <vector>
#include <limits>
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
    void AddEdge(int u, int v, WeightType w) { mWeights[u * mNumVertex + v] = w; }
protected:
    int mNumVertex;
    std::vector<WeightType> mWeights;
};

template <class GraphType>
class Prim {
private:
    typedef typename GraphType::WeightType WeightType;
public:
    Prim(const GraphType *graph) : mGraph(graph), mDists(graph->NumVertex()), mStates(graph->NumVertex()),
        mPrevs(graph->NumVertex()), mTotalWeight(0) { }
    void Compute() {
        int source = 0;
        for (int u = 0; u < mGraph->NumVertex(); ++u) {
            mDists[u] = mGraph->GetWeight(source, u);
            mStates[u] = false;
            mPrevs[u] = source;
        }
        mDists[source] = 0;
        mStates[source] = true;
        mTotalWeight = 0;
        for (int i = 1; i < mGraph->NumVertex(); ++i) {
            WeightType min = std::numeric_limits<WeightType>::max();
            int k;
            for (int j = 0; j < mGraph->NumVertex(); ++j) {
                if (!mStates[j] && min > mDists[j]) {
                    min = mDists[j];
                    k = j;
                }
            }
            mStates[k] = true;
            mDists[k] = min;
            mTotalWeight += min;
            for (int j = 0; j < mGraph->NumVertex(); ++j) {
                if (!mStates[j] && mGraph->GetWeight(k, j) < mDists[j]) {
                    mDists[j] = mGraph->GetWeight(k, j);
                    mPrevs[j] = k;
                }
            }
        }
    }
    WeightType TotalWeight() const {
        return mTotalWeight;
    }
    const std::vector<int>& TreeAsPrevs() const {
        return mPrevs;
    }
private:
    const GraphType *mGraph;
    std::vector<WeightType> mDists;
    std::vector<bool> mStates;
    std::vector<int> mPrevs;
    WeightType mTotalWeight;
};

int main() {
    int n;
	scanf("%d", &n);
    std::vector<Point2D64F> points(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
	WeightedDirectedGraphAsAdjMatrix<double> graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            graph.AddEdge(i, j, Distance(points[i], points[j]));
        }
    }

    int m;
	scanf("%d", &m);
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u; --v;
        graph.AddEdge(u, v, 0.0);
        graph.AddEdge(v, u, 0.0);
    }

    Prim<WeightedDirectedGraphAsAdjMatrix<double> > mst(&graph);
    mst.Compute();
    const std::vector<int>& treePrevs = mst.TreeAsPrevs();
    for (int i = 1; i < n; ++i) {
        int u = i;
        int v = treePrevs[i];
        if (graph.GetWeight(u, v) > 0.0) {
            printf("%d %d\n", u + 1, v + 1);
        }
    }

	return 0;
}
