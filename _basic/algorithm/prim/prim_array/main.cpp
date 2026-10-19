#include <iostream>
#include <vector>
#include <utility>

#include "Prim.h"

int main() {
	int n = 4;
	std::vector<std::vector<std::pair<int, int>>> graph(n);

	auto addEdge = [&](int u, int v, int w) {
		graph[u].emplace_back(v, w);
		graph[v].emplace_back(u, w);
	};

	addEdge(0, 1, 1);
	addEdge(0, 2, 4);
	addEdge(1, 2, 2);
	addEdge(1, 3, 5);
	addEdge(2, 3, 3);

	std::cout << "MST cost: " << Prim(graph) << std::endl;

	std::vector<std::vector<std::pair<int, int>>> disconnected(5);
	disconnected[0].emplace_back(1, 1);
	disconnected[1].emplace_back(0, 1);

	std::cout << "Disconnected result: " << Prim(disconnected) << std::endl;

	return 0;
}
