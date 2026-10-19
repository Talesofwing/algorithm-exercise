#include <iostream>
#include <vector>
#include <utility>

#include "Prim.h"  // 換成你實際的檔名

int main() {
	int n = 4;
	std::vector<std::vector<std::pair<int, int>>> graph(n);  // pair: (鄰居節點, 權重)

	auto addEdge = [&](int u, int v, int w) {
		graph[u].emplace_back(v, w);
		graph[v].emplace_back(u, w);  // 無向圖，雙向都加
	};

	addEdge(0, 1, 1);
	addEdge(0, 2, 4);
	addEdge(1, 2, 2);
	addEdge(1, 3, 5);
	addEdge(2, 3, 3);

	int cost = Prim(graph);
	std::cout << "MST cost: " << cost << std::endl;  // 預期 1+2+3=6

	// 不連通的圖：節點 4 是孤立點
	std::vector<std::vector<std::pair<int, int>>> disconnected(5);
	disconnected[0].emplace_back(1, 1);
	disconnected[1].emplace_back(0, 1);

	std::cout << "Disconnected result: " << Prim(disconnected) << std::endl;  // 預期 -1

	return 0;
}
