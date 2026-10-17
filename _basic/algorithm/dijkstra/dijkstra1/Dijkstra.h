#pragma once

#include <vector>
#include <queue>
#include <climits>
#include <utility>

struct State {
public:
	State(int node, int distFromStart) : Node(node), DistFromStart(distFromStart) {}

public:
	bool operator<(const State& other) const {
		return DistFromStart > other.DistFromStart;
	}

public:
	int Node;
	int DistFromStart;	// Total distance from the source node
};

inline std::vector<int> Dijkstra(const std::vector<std::vector<std::pair<int, int>>>& graph, int src) {
	int n = graph.size();
	std::vector<int> distTo(n, INT_MAX);

	std::priority_queue<State> pq;

	pq.emplace(src, 0);
	distTo[src] = 0;

	while (!pq.empty()) {
		State state = pq.top();
		pq.pop();

		int curNode = state.Node;
		int curDistFromStart = state.DistFromStart;

		if (distTo[curNode] < curDistFromStart) {
			continue;
		}

		for (const auto& neighbor : graph[curNode]) {
			int nextNode = neighbor.first;
			int nextDistFromStart = curDistFromStart + neighbor.second;

			if (distTo[nextNode] <= nextDistFromStart) {
				continue;
			}

			pq.emplace(nextNode, nextDistFromStart);
			distTo[nextNode] = nextDistFromStart;
		}
	}

	return distTo;
}
