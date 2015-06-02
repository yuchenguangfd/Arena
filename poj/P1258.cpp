/*
 * Problem: Agri-Net
 * http://poj.org/problem?id=1258
 */

#include <vector>
#include <limits>
#include <cstdio>

template <class T>
class WeightedDirectedGraphAsAdjMatrix {
public:
	WeightedDirectedGraphAsAdjMatrix(int numVertex, T initWeight = T()) : mNumVertex(numVertex),
		mWeights(numVertex * numVertex) {
        for (int i = 0; i < mWeights.size(); ++i) {
        	mWeights[i] = initWeight;
        }
    }
    int NumVertex() const { return mNumVertex; }
    T GetWeight(int u, int v) const { return mWeights[u * mNumVertex + v]; }
    void AddEdge(int u, int v, T weight) { mWeights[u * mNumVertex + v] = weight; }
protected:
    int mNumVertex;
    std::vector<T> mWeights;
};

template <class GraphType, class WeightType>
class Prim {
public:
	Prim(const GraphType *graph) : mGraph(graph), mDistances(graph->NumVertex()), mStates(graph->NumVertex()),
		mTotalWeight(0) { }
	void Compute() {
		int source = 0;
		for (int u = 0; u < mGraph->NumVertex(); ++u) {
			mDistances[u] = mGraph->GetWeight(source, u);
			mStates[u] = false;
		}
		mDistances[source] = 0;
		mStates[source] = true;
		mTotalWeight = 0;
		for (int i = 1; i < mGraph->NumVertex(); ++i) {
			WeightType min = std::numeric_limits<WeightType>::max();
			int k;
			for (int j = 0; j < mGraph->NumVertex(); ++j) {
				if (!mStates[j] && min > mDistances[j]) {
					min = mDistances[j];
					k = j;
				}
			}
			mStates[k] = true;
			mDistances[k] = min;
			mTotalWeight += min;
			for (int j = 0; j < mGraph->NumVertex(); ++j) {
				if (!mStates[j] && mGraph->GetWeight(k, j) < mDistances[j]) {
					mDistances[j] = mGraph->GetWeight(k, j);
				}
			}
		}
	}
	WeightType TotalWeight() const {
		return mTotalWeight;
	}
private:
	const GraphType *mGraph;
	std::vector<WeightType> mDistances;
	std::vector<bool> mStates;
	WeightType mTotalWeight;
};

int main() {
	while(true) {
		int n;
		if (scanf("%d", &n) == EOF) break;
		WeightedDirectedGraphAsAdjMatrix<int> graph(n);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				int weight;
				scanf("%d", &weight);
				graph.AddEdge(i, j, weight);
			}
		}
		Prim<WeightedDirectedGraphAsAdjMatrix<int>, int> MST(&graph);
		MST.Compute();
		printf("%d\n", MST.TotalWeight());
    }
	return 0;
} 
