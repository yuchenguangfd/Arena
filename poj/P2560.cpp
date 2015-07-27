/*
 * Problem: Freckles
 * http://poj.org/problem?id=2560
 */

#include <memory>
#include <limits>
#include <vector>
#include <cmath>
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
inline T Distance(const Point2D<T>& lhs, const Point2D<T>& rhs) {
    T dx = lhs.x - rhs.x;
    T dy = lhs.y - rhs.y;
    return sqrt(dx*dx + dy*dy);
}

typedef Point2D<double>	Point2D64F;

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
class Prim {
private:
    typedef typename GraphType::WeightType WeightType;
public:
    Prim(const GraphType *graph) : mGraph(graph), mDists(graph->NumVertex()), mStates(graph->NumVertex()),
        mTotalWeight(0)
#ifdef PRIM_COMPUTE_SOLUTION
        , mPrevs(graph->NumVertex())
#endif /* PRIM_COMPUTE_SOLUTION */
    { }
    void Compute() {
        int source = 0;
        for (int u = 0; u < mGraph->NumVertex(); ++u) {
            mDists[u] = mGraph->GetWeight(source, u);
            mStates[u] = false;
#ifdef PRIM_COMPUTE_SOLUTION
            mPrevs[u] = source;
#endif /* PRIM_COMPUTE_SOLUTION */
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
#ifdef PRIM_COMPUTE_SOLUTION
                    mPrevs[j] = k;
#endif /* PRIM_COMPUTE_SOLUTION */
                }
            }
        }
    }
    WeightType TotalWeight() const { return mTotalWeight; }
#ifdef PRIM_COMPUTE_SOLUTION
    const std::vector<int>& TreeAsPrevs() const { return mPrevs; }
#endif /* PRIM_COMPUTE_SOLUTION */
private:
    const GraphType *mGraph;
    std::vector<WeightType> mDists;
    std::vector<bool> mStates;
    WeightType mTotalWeight;
#ifdef PRIM_COMPUTE_SOLUTION
    std::vector<int> mPrevs;
#endif /* PRIM_COMPUTE_SOLUTION */
};

int main() {
    int n;
    scanf("%d", &n);
    std::vector<Point2D64F> points(n);
    for(int i = 0; i < n; ++i) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    std::auto_ptr<WeightedDirectedGraphAsAdjMatrix<double> > graph(
            new WeightedDirectedGraphAsAdjMatrix<double>(n, 1e100));
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            double dist = Distance(points[i], points[j]);
            graph->SetWeight(i, j, dist);
            graph->SetWeight(j, i, dist);
        }
    }
    Prim<WeightedDirectedGraphAsAdjMatrix<double> > mst(graph.release());
    mst.Compute();
    printf("%.2f\n", mst.TotalWeight());
    return 0;
}
