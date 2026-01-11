#include <iostream>
#include <ctime>
#include <iomanip>

#include "Graph.h"

using namespace std;

int main() {
	cin.tie(nullptr);
	cout << std::boolalpha;
	ios::sync_with_stdio(false);
	std::srand(std::time(NULL));

	Graph graph;
	for (int i = 0; i < 5; ++i) {
		graph.addNode();
	}

	graph.addEdge(0, 1, 10);
	graph.addEdge(0, 2, 20);
	graph.addEdge(1, 2, 30);
	graph.addEdge(2, 3, 40);
	graph.addEdge(2, 4, 25);
	graph.addEdge(3, 4, 50);
	cout << "Edge from 0 to 1 exists: " << graph.hasEdge(0, 1) << "\n";
	cout << "Weight of edge from 0 to 2: " << graph.getEdgeWeight(0, 2) << "\n";

	graph.removeEdge(0, 1);
	cout << "Edge from 0 to 1 exists after removal: " << graph.hasEdge(0, 1) << "\n";

	cout << "Weight of edge from 0 to 2: " << graph.getEdgeWeight(0, 2) << "\n";

	auto edges = graph.getEdges(2);
	for (const auto& edge : edges) {
		cout << "Edge from 2 to " << edge.to << " with weight " << edge.weight << "\n";
	}

	return 0;
}
