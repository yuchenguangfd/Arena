/*
 * Problem: Genealogical tree
 * http://poj.org/problem?id=2367
 */

#include <vector>
#include <cstdio>

struct Edge {
    int u, v;
    Edge(int u, int v) : u(u), v(v) { }
};

class DirectedGraphAsAdjList {
public:
    DirectedGraphAsAdjList(int numVertex, int maxNumEdge = 0) :
        mHeads(numVertex) {
        mEdges.reserve(maxNumEdge);
        mNexts.reserve(maxNumEdge);
        for (int i = 0; i < numVertex; ++i) {
            mHeads[i] = NIL;
        }
    }
    virtual ~DirectedGraphAsAdjList() { }
    int NumVertex() const  { return mHeads.size(); }
    int NumEdge() const { return mEdges.size(); }
    void AddEdge(const Edge &edge)  {
        mNexts.push_back(mHeads[edge.u]);
        mEdges.push_back(edge.v);
        mHeads[edge.u] = mEdges.size() - 1;
    }
    class EdgeIterator {
    public:
        EdgeIterator(const DirectedGraphAsAdjList *graph, int vertex) :
            mGraph(graph), mCurrentPtr(graph->mHeads[vertex]) { }
        bool HasNext() { return mCurrentPtr != NIL; }
        int NextVertex() {
            int next = mGraph->mEdges[mCurrentPtr];
            mCurrentPtr = mGraph->mNexts[mCurrentPtr];
            return next;
        }
    private:
        const DirectedGraphAsAdjList *mGraph;
        int mCurrentPtr;
    };
    EdgeIterator GetEdgeIteraror(int vertex) const {
        return EdgeIterator(this, vertex);
    }
private:
    static const int NIL = -1;
    std::vector<int> mHeads;
    std::vector<int> mEdges;
    std::vector<int> mNexts;
};

template <class GraphType>
class TopoSort {
public:
    TopoSort(const GraphType* graph) :
        mGraph(graph), mColors(graph->NumVertex()), mSequence(graph->NumVertex()),
        mIsDAG(false), mCurrentSequenceIndex(0) { }
    void Compute() {
        for (int u = 0; u < mGraph->NumVertex(); ++u) {
            mColors[u] = ColorWhite;
        }
        mIsDAG = true;
        mCurrentSequenceIndex = mGraph->NumVertex();
        for (int u = 0; mIsDAG && u < mGraph->NumVertex(); ++u) {
            if (mColors[u] == ColorWhite) {
                DFSVisit(u);
            }
        }
    }
    int SequenceAt(int i) const { return mSequence[i]; }
    bool IsDAG() const { return mIsDAG; }
private:
    void DFSVisit(int u) {
        mColors[u] = ColorGray;
        typename GraphType::EdgeIterator iter = mGraph->GetEdgeIteraror(u);
        while (iter.HasNext()) {
            int v = iter.NextVertex();
            if (mColors[v] == ColorWhite) {
                DFSVisit(v);
                if (!mIsDAG) return;
            } else if (mColors[v] == ColorGray) {
                mIsDAG = false;
                return;
            }
        }
        mColors[u] = ColorBlack;
        mSequence[--mCurrentSequenceIndex] = u;
    }
private:
    const GraphType* mGraph;
    enum Color {
        ColorWhite, ColorBlack, ColorGray
    };
    std::vector<int> mColors;
    std::vector<int> mSequence;
    int mCurrentSequenceIndex;
    bool mIsDAG;
};

int main() {
    int n;
    scanf("%d", &n);
    DirectedGraphAsAdjList graph(n);
    for(int u = 0; u < n; ++u) {
        while(true) {
            int v;
            scanf("%d", &v);
            if (v == 0) break;
            --v;
            graph.AddEdge(Edge(u,v));
        }
	}

    TopoSort<DirectedGraphAsAdjList> topoSort(&graph);
    topoSort.Compute();

    for(int i = 0; i < n; ++i)	{
        if (i > 0) printf(" ");
        printf("%d", topoSort.SequenceAt(i) + 1);
	}
	printf("\n");
	return 0;
}
