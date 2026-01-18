#pragma once

#include <vector>

// Use adjacency matrix representation for the directed weighted graph

class Graph {
public:
	struct Edge {
		int to;
		int weight;

		Edge(int to, int weight) : to(to), weight(weight) {}
	};

public:
	Graph() {}

public:
	void addNode() {
		int n = _graph.size();
		// Add a new row
		_graph.emplace_back(n + 1, 0);
		// Expand all existing rows
		for (int i = 0; i < n; ++i) {
			_graph[i].push_back(0);
		}
	}

	void addEdge(int from, int to, int weight) {
		_graph[from][to] = weight;
	}

	void removeEdge(int from, int to) {
		_graph[from][to] = 0;
	}

	bool hasEdge(int from, int to) const {
		return _graph[from][to] != 0;
	}

	int getEdgeWeight(int from, int to) const {
		return _graph[from][to];
	}

	const std::vector<Edge> getEdges(int node) const {
		std::vector<Edge> res;
		for (int i = 0; i < _graph[node].size(); ++i) {
			if (_graph[node][i] != 0) {
				res.emplace_back(Edge(i, _graph[node][i]));
			}

		}
		return res;
	}

private:
	std::vector<std::vector<int>> _graph;
};
