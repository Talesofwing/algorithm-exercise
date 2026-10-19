#include "Kruskal.h"

#include <iostream>
#include <vector>

int main() {
	std::vector<Edge> edges = {
		{0, 1, 4},
		{0, 2, 4},
		{1, 2, 2},
		{1, 3, 5},
		{2, 3, 5},
		{2, 4, 11},
		{3, 4, 2},
		{3, 5, 6},
		{4, 5, 1}
	};

	std::cout << "MST total weight: " << Kruskal(6, edges) << '\n';

	std::vector<Edge> connectedEdges = {
		{0, 1, 10},
		{0, 2, 6},
		{0, 3, 5},
		{1, 3, 15},
		{2, 3, 4}
	};
	std::cout << "Second connected graph MST total weight: "
		<< Kruskal(4, connectedEdges) << '\n';

	std::vector<Edge> disconnectedEdges = {
		{0, 1, 3},
		{2, 3, 7}
	};
	std::cout << "Disconnected graph result: "
		<< Kruskal(4, disconnectedEdges) << '\n';

	return 0;
}
