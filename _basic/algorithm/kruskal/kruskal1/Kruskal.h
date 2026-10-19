#pragma once

#include <algorithm>

#include "UnionFind.h"

struct Edge {
public:
	Edge(int from, int to, int weight) : From(from), To(to), Weight(weight) {}

public:
	bool operator<(const Edge& other) const {
		return Weight < other.Weight;
	}

public:
	int From;
	int To;
	int Weight;
};

inline int Kruskal(int n, std::vector<Edge>& edges) {
	UnionFind uf(n);

	std::sort(edges.begin(), edges.end());

	int mst = 0;
	for (const auto& edge : edges) {
		int from = edge.From;
		int to = edge.To;
		int weight = edge.Weight;

		if (uf.Same(from, to)) {
			continue;
		}

		mst += weight;
		uf.Unite(from, to);
	}

	return uf.Count() == 1 ? mst : -1;
}
