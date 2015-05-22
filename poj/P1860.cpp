/*
 * Problem: Currency Exchange
 * http://poj.org/problem?id=1860
 */

#include <vector>
#include <limits>
#include <cstdio>

template <class T>
struct WeightedEdge {
    int u, v;
    T weight;
    WeightedEdge(int u, int v, T weight) : u(u), v(v), weight(weight) { }
};

template <class T>
class WeightedDirectedGraphAsEdgeList {
public:
    WeightedDirectedGraphAsEdgeList(int numVertex, int maxNumEdge = 0) :
        mNumVertex(numVertex) {
        mEdgeList.reserve(maxNumEdge);
    }
    int NumVertex() const { return mNumVertex; }
    int NumEdge() const { return mEdgeList.size(); }
    void AddEdge(int u, int v, T weight) { AddEdge(WeightedEdge<T>(u, v, weight)); }
    void AddEdge(const WeightedEdge<T>& edge) { mEdgeList.push_back(edge); }
    const WeightedEdge<T>& GetEdge(int i) const { return mEdgeList[i]; }
protected:
    int mNumVertex;
    std::vector<WeightedEdge<T> > mEdgeList;
};

template <class WeightType, class DistanceType>
class BellmanFord {
public:
    BellmanFord(const WeightedDirectedGraphAsEdgeList<WeightType>* graph, int source) :
        mGraph(graph), mSource(source), mDistances(graph->NumVertex()), mExistNegativeCycle(false) { }
    virtual ~BellmanFord() { }
    void Compute() {
        DistanceType initDist = GetInitDistance();
        for (int i = 0; i < mGraph->NumVertex(); ++i) {
            mDistances[i] = initDist;
        }
        mDistances[mSource] = GetSourceDistance();
        for (int i = 1; i < mGraph->NumVertex(); ++i) {
            bool relaxed = false;
            for (int j = 0; j < mGraph->NumEdge(); ++j) {
                if (Relax(mGraph->GetEdge(j))) {
                    relaxed = true;
                }
            }
            if (!relaxed) break;
        }
        mExistNegativeCycle = false;
        for (int j = 0; j < mGraph->NumEdge(); ++j) {
            if (Relax(mGraph->GetEdge(j))) {
                mExistNegativeCycle = true;
                break;
            }
        }
    }
    virtual DistanceType GetInitDistance() const {
        return std::numeric_limits<DistanceType>::max();
    }
    virtual DistanceType GetSourceDistance() const {
       return 0;
   }
    virtual bool Relax(const WeightedEdge<WeightType>& edge) {
        if (mDistances[edge.u] < mDistances[edge.v] - edge.weight) {
            mDistances[edge.v] = mDistances[edge.u] + edge.weight;
            return true;
        } else {
            return false;
        }
    }
    bool ExistNegativeCycle() const { return mExistNegativeCycle; }
    DistanceType Distance(int v) const { return mDistances[v]; }
protected:
    const WeightedDirectedGraphAsEdgeList<WeightType> *mGraph;
    int mSource;
    std::vector<DistanceType> mDistances;
    bool mExistNegativeCycle;
};

struct WeightType {
    double rate;
    double commission;
    WeightType(double r, double c) :rate(r), commission(c) { }
};

double operator- (double lhs, const WeightType& rhs) {
    return 0.0;
}

double operator+ (double lhs, const WeightType& rhs) {
    return 0.0;
}

class CurrencyBellmanFord : public BellmanFord<WeightType, double> {
public:
    CurrencyBellmanFord(const WeightedDirectedGraphAsEdgeList<WeightType>* graph, int source,
            double sourceDistance) : BellmanFord<WeightType, double>(graph, source),
            mSourceDistance(sourceDistance) { }
    virtual double GetInitDistance() const {
        return -1e100;
    }
    virtual double GetSourceDistance() const {
        return mSourceDistance;
    }
    virtual bool Relax(const WeightedEdge<WeightType>& edge) {
        if (mDistances[edge.u] - edge.weight.commission > 0) {
            double d = (mDistances[edge.u] - edge.weight.commission) * edge.weight.rate;
            if (d > mDistances[edge.v]) {
                mDistances[edge.v] = d;
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
private:
    double mSourceDistance;
};

int main() {
    while (true) {
        int n, m, source;
        double v;
        if (scanf("%d %d %d %lf", &n, &m, &source, &v) == -1) break;
        --source;
        WeightedDirectedGraphAsEdgeList<WeightType> graph(n, m);
        for (int i = 0; i < m; ++i) {
            int a, b;
            double Rab, Cab, Rba, Cba;
            scanf("%d %d %lf %lf %lf %lf", &a, &b, &Rab, &Cab, &Rba, &Cba);
            --a; --b;
            graph.AddEdge(WeightedEdge<WeightType>(a, b, WeightType(Rab, Cab)));
            graph.AddEdge(WeightedEdge<WeightType>(b, a, WeightType(Rba, Cba)));
        }
        CurrencyBellmanFord SSSP(&graph, source, v);
        SSSP.Compute();
        if (SSSP.ExistNegativeCycle()) {
            printf("YES\n");
        } else if (SSSP.Distance(source) > v) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
