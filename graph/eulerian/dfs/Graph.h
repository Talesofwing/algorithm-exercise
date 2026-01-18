#pragma once

#include <vector>
#include <algorithm>

// Use adjacency list representation for the non-directed weighted graph

class Graph {
public:
	struct Edge {
		int id;
		int to;

		Edge(int id, int to) : id(id), to(to) {}
	};

public:
	Graph() {}

public:
	void addNode() {
		_graph.emplace_back();
	}

	void addEdge(int id, int from, int to) {
		_graph[from].emplace_back(id, to);
		_graph[to].emplace_back(id, from);
	}

	void removeEdge(int from, int to) {
		auto& edges = _graph[from];
		edges.erase(std::remove_if(edges.begin(), edges.end(), [to](const Edge& edge) { return edge.to == to; }), edges.end());
		auto& revEdges = _graph[to];
		revEdges.erase(std::remove_if(revEdges.begin(), revEdges.end(), [from](const Edge& edge) { return edge.to == from; }), revEdges.end());
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

	const std::vector<Edge>& getEdges(int node) const {
		return _graph[node];
	}

private:
	std::vector<std::vector<Edge>> _graph;
};
