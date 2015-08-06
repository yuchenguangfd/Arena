/*
 * Problem: Picnic Planning
 * http://poj.org/problem?id=1639
 */

#include <string>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

struct Connection {
    std::string name1, name2;
    int dist;
};

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

typedef WeightedDirectedGraphAsAdjMatrix<int> Graph;

template <class GraphType>
class DegreeLimitMST {
public:
    typedef typename GraphType::WeightType WeightType;
    DegreeLimitMST(const GraphType* graph, int limit) : mGraph(*graph), mLimit(limit),
            mFlags(graph->NumVertex()), mVisits(graph->NumVertex()),
            mDists(graph->NumVertex()), mPrevs(graph->NumVertex()),
            mBests(graph->NumVertex()), mBestNums(graph->NumVertex()), mRevs(graph->NumVertex()),
            INF(std::numeric_limits<WeightType>::max()) { }
    void Compute() {
        int deg0 = 0;
        for (int i = 1; i < mGraph.NumVertex(); ++i) {
            if (mGraph[0][i] > 0) ++deg0;
        }
        mTotalWeight = 0;
        int numComponent = 0;
        int k = 0;
        std::fill(mFlags.begin(), mFlags.end(), false);
        std::fill(mDists.begin(), mDists.end(), 0);
        std::fill(mPrevs.begin(), mPrevs.end(), 0);
        while (k < mGraph.NumVertex() - 1) {
            ++numComponent;
            k += Prim();
        }
        WeightType currentTotalWeight = mTotalWeight;
        while (numComponent < mLimit) {
            if (numComponent == deg0) break;
            ++numComponent;
            std::fill(mBests.begin(), mBests.end(), 0);
            std::fill(mBestNums.begin(), mBestNums.end(), 0);
            mBests[0] = -INF;
            for (int i = 1; i < mGraph.NumVertex(); ++i) {
                GetBest(i);
            }
            WeightType min_delta = INF;
            int choose;
            for (int i = 1; i < mGraph.NumVertex(); ++i) {
                if (mPrevs[i] != 0
                 && mGraph[0][i] > 0
                 && mGraph[0][i] - mBests[i] < min_delta) {
                    min_delta = mGraph[0][i] - mBests[i];
                    choose = i;
                }
            }
            Reverse(choose);
            currentTotalWeight += min_delta;
            if (currentTotalWeight < mTotalWeight) {
                mTotalWeight = currentTotalWeight;
            }
        }
    }
    WeightType TotalWeight() const { return mTotalWeight; }
private:
    int Prim() {
        int src = 0;
        WeightType src_dist_min = INF;
        for (int i = 1; i < mGraph.NumVertex(); ++i) {
            if (!mFlags[i] && mGraph[0][i] > 0 && mGraph[0][i] < src_dist_min) {
                src_dist_min = mGraph[0][i];
                src = i;
            }
        }
        for (int i = 1; i < mGraph.NumVertex(); ++i) {
            if (!mFlags[i]) {
                mVisits[i] = false;
                mPrevs[i] = src;
                mDists[i] = (mGraph[src][i] > 0) ? mGraph[src][i] : INF;
            }
        }
        mDists[src] = 0;
        mPrevs[src] = 0;
        mFlags[src] = true;
        mVisits[src] = true;
        int count = 1;
        WeightType sum = 0;
        for (int i = 1; i < mGraph.NumVertex() - 1; ++i) {
            int k = -1;
            WeightType dist_min = INF;
            for (int j = 1; j < mGraph.NumVertex(); ++j) {
                if (!mVisits[j] && dist_min > mDists[j]) {
                    dist_min = mDists[j];
                    k = j;
                }
            }
            if (k == -1) break;
            mFlags[k] = true;
            mVisits[k] = true;
            sum += mDists[k];
            ++count;
            for (int j = 1; j < mGraph.NumVertex(); ++j) {
                if (!mVisits[j] && mGraph[k][j] > 0 && mDists[j] > mGraph[k][j]) {
                    mDists[j] = mGraph[k][j];
                    mPrevs[j] = k;
                }
            }
        }
        mTotalWeight += sum + mGraph[0][src];
        return count;
    }

    int GetBest(int i) {
        if (mBests[i]) return mBests[i];
        if (!mPrevs[i]) return mBests[i] = -INF;
        int tmp = GetBest(mPrevs[i]);
        if (tmp < mGraph[mPrevs[i]][i]) {
            mBests[i] = mGraph[mPrevs[i]][i];
            mBestNums[i] = i;
        } else{
            mBests[i] = tmp;
            mBestNums[i] = mBestNums[mPrevs[i]];
        }
        return mBests[i];
    }

    void Reverse(int i) {
        int top = 0;
        int end = mBestNums[i];
        mRevs[0] = 0;
        while (i != end) {
            mRevs[++top] = i;
            i = mPrevs[i];
        }
        mRevs[++top] = i;
        for (i = top; i > 0; --i) {
            mPrevs[mRevs[i]] = mRevs[i-1];
        }
    }
private:
    const WeightType INF;
    GraphType mGraph;
    int mLimit;
    WeightType mTotalWeight;
    std::vector<bool> mFlags;
    std::vector<bool> mVisits;
    std::vector<int> mPrevs;
    std::vector<WeightType> mDists;
    std::vector<WeightType> mBests;
    std::vector<int> mBestNums;
    std::vector<int> mRevs;
};

int main() {
    int n, m, k;
    std::cin >> m;
    std::vector<Connection> connections;
    std::map<std::string, int> name_map;
    name_map["Park"] = 0;
    n = 1;
    for (int i = 0; i < m; ++i) {
        Connection conn;
        std::cin >> conn.name1 >> conn.name2 >> conn.dist;
        if (name_map.find(conn.name1) == name_map.end()) {
            name_map[conn.name1] = (n++);
        }
        if (name_map.find(conn.name2) == name_map.end()) {
            name_map[conn.name2] = (n++);
        }
        connections.push_back(conn);
    }
    std::cin >> k;
    Graph graph(n);
    for (std::vector<Connection>::iterator it = connections.begin(); it != connections.end(); ++it) {
        int u = name_map[it->name1];
        int v = name_map[it->name2];
        if (graph.GetWeight(u, v) == 0 || graph.GetWeight(u, v) > it->dist) {
            graph.SetWeight(u, v, it->dist);
            graph.SetWeight(v, u, it->dist);
        }
    }
    DegreeLimitMST<Graph> dlmst(&graph, k);
    dlmst.Compute();
    std::cout << "Total miles driven: " << dlmst.TotalWeight() << std::endl;
    return 0;
}
