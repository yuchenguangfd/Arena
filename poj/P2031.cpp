/*
 * Problem: Building a Space Station
 * http://poj.org/problem?id=2031
 */

#include <vector>
#include <limits>
#include <cmath>
#include <cstdio>

template <class T>
class Point3D {
public:
    Point3D() : x(), y(), z() { }
    Point3D(T x, T y, T z) { this->x = x; this->y = y; this->z = z; }
public:
    T x;
    T y;
    T z;
};

template <class T>
inline T Distance(const Point3D<T>& lhs, const Point3D<T>& rhs) {
    T dx = lhs.x - rhs.x;
    T dy = lhs.y - rhs.y;
    T dz = lhs.z - rhs.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

typedef Point3D<double> Point3D64F;

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
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        std::vector<Point3D64F> points(n);
        std::vector<double> radius(n);
        for (int i = 0; i < n; ++i) {
            scanf("%lf %lf %lf %lf", &points[i].x, &points[i].y, &points[i].z, &radius[i]);
        }
        WeightedDirectedGraphAsAdjMatrix<double> graph(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double d = Distance(points[i], points[j]);
                if (radius[i] + radius[j] >= d) {
                    d = 0.00;
                } else {
                    d -= radius[i] + radius[j];
                }
                graph.AddEdge(i, j, d);
                graph.AddEdge(j, i, d);
            }
        }
        Prim<WeightedDirectedGraphAsAdjMatrix<double> > prim(&graph);
        prim.Compute();
        printf("%0.3f\n", prim.TotalWeight());
    }
    return 0;
}
