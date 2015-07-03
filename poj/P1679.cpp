/*
 * Problem: The Unique MST
 * http://poj.org/problem?id=1679
 */

#include <algorithm>
#include <limits>
#include <vector>
#include <cstdio>

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

#define PRIM_COMPUTE_SOLUTION

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


template <class GraphType>
class SecondMST {
private:
    typedef typename GraphType::WeightType WeightType;
public:
    SecondMST(const GraphType *graph) : mGraph(graph),
        mFirstTotalWeight(0), mSecondTotalWeight(0) { }
    void Compute() {
        GraphType graphTry = *mGraph;
        Prim<GraphType> prim(&graphTry);
        prim.Compute();
        mFirstTotalWeight = prim.TotalWeight();
        mSecondTotalWeight = std::numeric_limits<WeightType>::max();
        const std::vector<int>& prevs = prim.TreeAsPrevs();
        for (int v = 1; v < mGraph->NumVertex(); ++v) {
            int u = prevs[v];
            WeightType origWeight = mGraph->GetWeight(u, v);
            graphTry.SetWeight(u, v, std::numeric_limits<WeightType>::max());
            Prim<GraphType> prim(&graphTry);
            prim.Compute();
            mSecondTotalWeight = std::min(mSecondTotalWeight, prim.TotalWeight());
            graphTry.SetWeight(u, v, origWeight);
        }
    }
    WeightType FirstTotalWeight() const { return mFirstTotalWeight;}
    WeightType SecondTotalWeight() const { return mSecondTotalWeight; }
private:
    const GraphType *mGraph;
    WeightType mFirstTotalWeight;
    WeightType mSecondTotalWeight;
};

int main() {
    const int oo = 1000000000;
    int numCase;
    scanf("%d", &numCase);
    while (numCase--) {
        int n, m;
        scanf("%d%d", &n, &m);
        WeightedDirectedGraphAsAdjMatrix<int> graph(n, oo);
        while (m--) {
            int u,v, w;
            scanf("%d %d %d", &u, &v, &w);
            --u; --v;
            graph.SetWeight(u, v, w);
            graph.SetWeight(v, u, w);
        }

        SecondMST<WeightedDirectedGraphAsAdjMatrix<int> > smst(&graph);
        smst.Compute();
        if (smst.FirstTotalWeight() != smst.SecondTotalWeight()) {
            printf("%d\n", smst.FirstTotalWeight());
        } else {
            printf("Not Unique!\n");
        }
    }
    return 0;
}
