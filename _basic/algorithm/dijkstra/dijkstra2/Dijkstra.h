#pragma once

#include <vector>
#include <queue>
#include <climits>
#include <utility>

struct State {
public:
	State(int node, int distFromStart, int edgesFromStart) : Node(node), DistFromStart(distFromStart), EdgesFromStart(edgesFromStart) {}

public:
	bool operator<(const State& other) const {
		return DistFromStart > other.DistFromStart;
	}

public:
	int Node;
	int DistFromStart;	// Total distance from the source node
	int EdgesFromStart;	// Total edges from the source node
};

inline std::vector<std::vector<int>> Dijkstra(const std::vector<std::vector<std::pair<int, int>>>& graph, int src, int k) {
	int n = graph.size();
	std::vector<std::vector<int>> distTo(n, std::vector<int>(k + 1, INT_MAX));

	std::priority_queue<State> pq;

	pq.emplace(src, 0, 0);
	distTo[src][0] = 0;

	while (!pq.empty()) {
		State state = pq.top();
		pq.pop();

		int curNode = state.Node;
		int curDistFromStart = state.DistFromStart;
		int curEdgesFromStart = state.EdgesFromStart;

		if (distTo[curNode][curEdgesFromStart] < curDistFromStart) {
			continue;
		}

		for (const auto& neighbor : graph[curNode]) {
			int nextNode = neighbor.first;
			int nextDistFromStart = curDistFromStart + neighbor.second;
			int nextEdgesFromStart = curEdgesFromStart + 1;

			if (nextEdgesFromStart > k || distTo[nextNode][nextEdgesFromStart] <= nextDistFromStart) {
				continue;
			}

			pq.emplace(nextNode, nextDistFromStart, nextEdgesFromStart);
			distTo[nextNode][nextEdgesFromStart] = nextDistFromStart;
		}
	}

	return distTo;
}
