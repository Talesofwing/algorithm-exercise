#pragma once

#include <vector>
#include <queue>
#include <utility>

struct State {
public:
	State(int node, int weight) : Node(node), Weight(weight) {}

public:
	bool operator>(const State& other) const {
		return Weight > other.Weight;
	}

public:
	int Node;
	int Weight;
};

inline int Prim(const std::vector<std::vector<std::pair<int, int>>>& graph) {
	int n = graph.size();
	if (n == 0) {
		return 0;
	}

	int weightSum = 0;

	std::vector<bool> visited(n, false);

	std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
	pq.emplace(0, 0);

	while (!pq.empty()) {
		State state = pq.top();
		pq.pop();

		int curNode = state.Node;
		int curWeight = state.Weight;

		if (visited[curNode]) {
			continue;
		}

		weightSum += curWeight;
		visited[curNode] = true;

		for (const auto& edge : graph[curNode]) {
			int nextNode = edge.first;
			int nextWeight = edge.second;

			if (visited[nextNode]) {
				continue;
			}

			pq.emplace(nextNode, nextWeight);
		}
	}

	for (int i = 0; i < visited.size(); ++i) {
		if (!visited[i]) {
			return -1;
		}
	}

	return weightSum;
}
