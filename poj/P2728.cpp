/*
 * Problem: Desert King
 * http://poj.org/problem?id=2728
 */

#include <vector>
#include <limits>
#include <cmath>
#include <cassert>
#include <cstdio>

template <class T>
class Point2D {
public:
    Point2D() : x(), y() { }
    Point2D(T x, T y) { this->x = x; this->y = y; }
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

typedef Point2D<double> Point2D64F;

template <class T>
inline T Abs(T x) {
    return (x < T()) ? -x : x;
}

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

template <class GraphType>
class MinRatioSpanTree {
public:
    MinRatioSpanTree(const GraphType *graph1, const GraphType *graph2) :
        mGraph1(graph1), mGraph2(graph2), mGraph(graph1->NumVertex()), mMinRatio(0.0) {
        assert(graph1->NumVertex() == graph2->NumVertex());
    }
    void Compute() {
        BinarySearch();
    }
    double MinRatio() const { return mMinRatio; }
private:
    void BinarySearch() {
        const double EPS = 0.0001;
        double low = 0, high = 100;
        while (high - low > EPS) {
            double mid = (low + high) / 2.0;
            BuildGraph(mid);
            Prim<GraphType> prim(&mGraph);
            prim.Compute();
            if (prim.TotalWeight() >= 0) {
                low = mid;
            } else {
                high = mid;
            }
        }
        mMinRatio = low;
    }
    void BuildGraph(double ratio) {
        for (int i = 0; i < mGraph.NumVertex(); ++i) {
            for (int j = i + 1; j < mGraph.NumVertex(); ++j) {
                double w = mGraph1->GetWeight(i, j) - ratio * mGraph2->GetWeight(i, j);
                mGraph.SetWeight(i, j, w);
                mGraph.SetWeight(j, i, w);
            }
        }
    }

private:
    const GraphType *mGraph1;
    const GraphType *mGraph2;
    GraphType mGraph;
    double mMinRatio;
};

int main() {
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        std::vector<Point2D64F> positions(n);
        std::vector<double> heights(n);
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf %lf", &positions[i].x, &positions[i].y, &heights[i]);
        }

        WeightedDirectedGraphAsAdjMatrix<double> graphDist(n);
        WeightedDirectedGraphAsAdjMatrix<double> graphHeight(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double w1 = Distance(positions[i], positions[j]);
                graphDist.SetWeight(i, j, w1);
                graphDist.SetWeight(j, i, w1);
                double w2 = Abs(heights[i] - heights[j]);
                graphHeight.SetWeight(i, j, w2);
                graphHeight.SetWeight(j, i, w2);
            }
        }

        MinRatioSpanTree<WeightedDirectedGraphAsAdjMatrix<double> > mrst(&graphHeight, &graphDist);
        mrst.Compute();
        printf("%.3f\n", mrst.MinRatio());
    }
    return 0;
}
