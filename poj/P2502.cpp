/*
 * Problem: Subway
 * http://poj.org/problem?id=2502
 */

#include <limits>
#include <vector>
#include <cmath>
#include <cstdio>

template<class T>
class Point2D {
public:
    Point2D() :
            x(), y() {
    }
    Point2D(T x, T y) {
        this->x = x;
        this->y = y;
    }
public:
    T x;
    T y;
};

template<class T>
inline T Distance(const Point2D<T> &lhs, const Point2D<T>& rhs) {
    T dx = lhs.x - rhs.x;
    T dy = lhs.y - rhs.y;
    return sqrt(dx * dx + dy * dy);
}

template<class T, class Alloc = std::allocator<T> >
class WeightedDirectedGraphAsAdjMatrix {
public:
    WeightedDirectedGraphAsAdjMatrix(int numVertex, T initWeight = T()) :
            mNumVertex(numVertex) {
        int size = mNumVertex * mNumVertex;
        Alloc alloc;
        mData = alloc.allocate(size);
        for (int i = 0; i < size; ++i) {
            mData[i] = initWeight;
        }
    }
    virtual ~WeightedDirectedGraphAsAdjMatrix() {
        int size = mNumVertex * mNumVertex;
        Alloc alloc;
        alloc.deallocate(mData, size);
    }
    int NumVertex() const {
        return mNumVertex;
    }
    T GetWeight(int u, int v) const {
        return mData[u * mNumVertex + v];
    }
    virtual void AddEdge(int u, int v, T weight) {
        mData[u * mNumVertex + v] = weight;
    }
protected:
    int mNumVertex;
    T *mData;
};

template<class T, class Alloc = std::allocator<T> >
class Dijkstra {
public:
    Dijkstra(const WeightedDirectedGraphAsAdjMatrix<T, Alloc>* graph,
            int source) :
            mGraph(graph), mSource(source), mDistances(graph->NumVertex()), mStates(
                    graph->NumVertex()) {
    }
    void Compute() {
        for (int u = 0; u < mGraph->NumVertex(); ++u) {
            mDistances[u] = mGraph->GetWeight(mSource, u);
            mStates[u] = false;
        }
        mDistances[mSource] = T();
        mStates[mSource] = true;
        for (int i = 1; i < mGraph->NumVertex(); ++i) {
            T min = std::numeric_limits<T>::max();
            int k;
            for (int j = 0; j < mGraph->NumVertex(); ++j) {
                if (!mStates[j] && min > mDistances[j]) {
                    min = mDistances[j];
                    k = j;
                }
            }
            mStates[k] = true;
            for (int j = 0; j < mGraph->NumVertex(); ++j) {
                if (!mStates[j]
                        && mDistances[j]
                                > mDistances[k] + mGraph->GetWeight(k, j)) {
                    mDistances[j] = mDistances[k] + mGraph->GetWeight(k, j);
                }
            }
        }
    }
    T Distance(int v) const {
        return mDistances[v];
    }
private:
    const WeightedDirectedGraphAsAdjMatrix<T, Alloc> *mGraph;
    int mSource;
    std::vector<T, Alloc> mDistances;
    std::vector<bool, Alloc> mStates;
};

typedef Point2D<double> Point;

int main() {
    int x, y;
    std::vector<Point> points;
    scanf("%d %d", &x, &y);
    points.push_back(Point(x, y));
    scanf("%d %d", &x, &y);
    points.push_back(Point(x, y));

    std::vector<int> lineBegins, lineEnds;
    while (true) {
        int rtn = scanf("%d %d", &x, &y);
        if (rtn == -1) break;
        lineBegins.push_back(points.size());
        points.push_back(Point(x, y));
        while (true) {
            scanf("%d %d", &x, &y);
            if (x == -1 && y == -1) break;
            points.push_back(Point(x, y));
        }
        lineEnds.push_back(points.size());
    }

    WeightedDirectedGraphAsAdjMatrix<double> graph(points.size());
    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            double time = Distance(points[i], points[j]) / 10000 * 60;
            graph.AddEdge(i, j, time);
            graph.AddEdge(j, i, time);
        }
    }
    for (int i = 0; i < lineBegins.size(); ++i) {
        for (int k = lineBegins[i] + 1; k < lineEnds[i]; ++k) {
            double time = Distance(points[k-1], points[k]) / 40000 * 60;
            graph.AddEdge(k - 1, k, time);
            graph.AddEdge(k, k - 1, time);
        }
    }

    Dijkstra<double> SSSP(&graph, 0);
    SSSP.Compute();
    printf("%d\n", (int)(SSSP.Distance(1) + 0.5));
    return 0;
}
