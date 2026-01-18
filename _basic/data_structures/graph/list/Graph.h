#pragma once

#include <vector>
#include <algorithm>

// Use adjacency list representation for the directed weighted graph

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
		_graph.emplace_back();
	}

	void addEdge(int from, int to, int weight) {
		_graph[from].emplace_back(to, weight);
	}

	void removeEdge(int from, int to) {
		auto& edges = _graph[from];
		edges.erase(std::remove_if(edges.begin(), edges.end(), [to](const Edge& edge) { return edge.to == to; }), edges.end());
	}

	bool hasEdge(int from, int to) const {
		const auto& edges = _graph[from];
		for (const auto& edge : edges) {
			if (edge.to == to) {
				return true;
			}
		}
		return false;
	}

	int getEdgeWeight(int from, int to) const {
		const auto& edges = _graph[from];
		for (const auto& edge : edges) {
			if (edge.to == to) {
				return edge.weight;
			}
		}
		return -1; // Edge not found
	}

	const std::vector<Edge>& getEdges(int node) const {
		return _graph[node];
	}

private:
	std::vector<std::vector<Edge>> _graph;
};
