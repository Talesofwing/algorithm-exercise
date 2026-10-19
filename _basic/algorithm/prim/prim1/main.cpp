#include <iostream>
#include <vector>
#include <tuple>

#include "Prim.h"

int main() {
	int n = 4;
	std::vector<std::vector<std::tuple<int, int, int>>> graph(n);

	auto addEdge = [&](int u, int v, int w) {
		graph[u].emplace_back(u, v, w);
		graph[v].emplace_back(v, u, w);  // 無向圖，雙向都加
	};

	addEdge(0, 1, 1);
	addEdge(0, 2, 4);
	addEdge(1, 2, 2);
	addEdge(1, 3, 5);
	addEdge(2, 3, 3);

	int cost = Prim(graph);
	std::cout << "MST cost: " << cost << std::endl;

	std::vector<std::vector<std::tuple<int, int, int>>> disconnected(5);
	disconnected[0].emplace_back(0, 1, 1);
	disconnected[1].emplace_back(1, 0, 1);

	std::cout << "Disconnected result: " << Prim(disconnected) << std::endl;

	return 0;
}
