/*
 * Problem: Frogger
 * http://poj.org/problem?id=2253
 */

#include <vector>
#include <cmath>
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
class FloydWarshall {
private:
    typedef typename GraphType::WeightType WeightType;
public:
    FloydWarshall(const GraphType *graph) : mGraph(graph), mDists(graph->NumVertex()) { }
    virtual ~FloydWarshall() { }
    void Compute() {
        mDists = *mGraph;
        int n = mGraph->NumVertex();
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    Relax(i, j, k);
                }
            }
        }

    }
    WeightType Distance(int u, int v) {
        return mDists.GetWeight(u, v);
    }
protected:
    virtual void Relax(int i, int j, int k) {
        mDists[i][j] = std::min(mDists[i][j], mDists[i][k] + mDists[k][j]);
    }
protected:
    const GraphType *mGraph;
    GraphType mDists;
};

class MyFloydWarshall: public FloydWarshall<WeightedDirectedGraphAsAdjMatrix<double> > {
public:
    MyFloydWarshall(const WeightedDirectedGraphAsAdjMatrix<double> *graph) :
        FloydWarshall<WeightedDirectedGraphAsAdjMatrix<double> >(graph) { }
protected:
    virtual void Relax(int i, int j, int k) {
        mDists[i][j] = std::min(mDists[i][j], std::max(mDists[i][k], mDists[k][j]));
    }
};

int main() {
    int caseID(0);
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        std::vector<Point2D64F> points(n);
        for (int i = 0; i < n; ++i) {
            scanf("%lf %lf", &points[i].x, &points[i].y);
        }
        WeightedDirectedGraphAsAdjMatrix<double> graph(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                graph[i][j] = Distance(points[i], points[j]);
            }
        }
        MyFloydWarshall floyd(&graph);
        floyd.Compute();
        printf("Scenario #%d\n", ++caseID);
        printf("Frog Distance = %0.3f\n\n", floyd.Distance(0, 1));
    }
    return 0;
}
