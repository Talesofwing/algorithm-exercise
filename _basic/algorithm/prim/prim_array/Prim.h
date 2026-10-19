#pragma once

#include <vector>
#include <utility>
#include <climits>

inline int Prim(const std::vector<std::vector<std::pair<int, int>>>& graph) {
	int n = graph.size();
	if (n == 0) {
		return 0;
	}

	int weightSum = 0;

	std::vector<bool> visited(n, false);
	std::vector<int> minDist(n, INT_MAX);
	minDist[0] = 0;

	for (int iter = 0; iter < n; ++iter) {
		int curNode = -1;
		for (int j = 0; j < n; ++j) {
			if (!visited[j] && (curNode == -1 || minDist[j] < minDist[curNode])) {
				curNode = j;
			}
		}

		if (minDist[curNode] == INT_MAX) {
			return -1;
		}

		weightSum += minDist[curNode];
		visited[curNode] = true;

		for (const auto& edge : graph[curNode]) {
			int nextNode = edge.first;
			int nextWeight = edge.second;

			if (!visited[nextNode] && nextWeight < minDist[nextNode]) {
				minDist[nextNode] = nextWeight;
			}
		}
	}

	return weightSum;
}
