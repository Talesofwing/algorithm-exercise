#include "Dijkstra.h"

#include <iostream>
#include <vector>
#include <utility>
#include <cassert>
#include <climits>

using namespace std;

void AddEdge(
	vector<vector<pair<int, int>>>& graph,
	int from,
	int to,
	int weight) {
	graph[from].emplace_back(to, weight);
}

void PrintDistances(const vector<vector<int>>& dist) {
	for (int node = 0; node < static_cast<int>(dist.size()); ++node) {
		cout << "Node " << node << ":\n";

		for (int edges = 0; edges < static_cast<int>(dist[node].size()); ++edges) {
			cout << "  Exactly " << edges << " edges: ";

			if (dist[node][edges] == INT_MAX) {
				cout << "Unreachable";
			} else {
				cout << dist[node][edges];
			}

			cout << '\n';
		}
	}
}

int main() {
	// Test 1: Basic graph
	{
		vector<vector<pair<int, int>>> graph(5);

		AddEdge(graph, 0, 1, 4);
		AddEdge(graph, 0, 2, 1);
		AddEdge(graph, 2, 1, 2);
		AddEdge(graph, 1, 3, 1);
		AddEdge(graph, 2, 3, 5);
		AddEdge(graph, 3, 4, 3);

		auto dist = Dijkstra(graph, 0, 3);

		assert(dist[0][0] == 0);
		assert(dist[1][1] == 4);
		assert(dist[1][2] == 3);
		assert(dist[2][1] == 1);
		assert(dist[3][2] == 5);
		assert(dist[3][3] == 4);
		assert(dist[4][3] == 8);

		cout << "Test 1 passed\n";
		PrintDistances(dist);
	}

	// Test 2: Unreachable nodes
	{
		vector<vector<pair<int, int>>> graph(4);

		AddEdge(graph, 0, 1, 5);
		AddEdge(graph, 1, 2, 2);

		auto dist = Dijkstra(graph, 0, 2);

		assert(dist[0][0] == 0);
		assert(dist[1][1] == 5);
		assert(dist[2][2] == 7);
		assert(dist[3][0] == INT_MAX);
		assert(dist[3][1] == INT_MAX);
		assert(dist[3][2] == INT_MAX);

		cout << "\nTest 2 passed\n";
	}

	// Test 3: Single node
	{
		vector<vector<pair<int, int>>> graph(1);

		auto dist = Dijkstra(graph, 0, 0);

		assert(dist.size() == 1);
		assert(dist[0].size() == 1);
		assert(dist[0][0] == 0);

		cout << "\nTest 3 passed\n";
	}

	// Test 4: Multiple paths with different edge counts
	{
		vector<vector<pair<int, int>>> graph(4);

		AddEdge(graph, 0, 1, 10);
		AddEdge(graph, 0, 2, 2);
		AddEdge(graph, 2, 1, 3);
		AddEdge(graph, 1, 3, 1);
		AddEdge(graph, 2, 3, 20);

		auto dist = Dijkstra(graph, 0, 3);

		assert(dist[1][1] == 10);
		assert(dist[1][2] == 5);
		assert(dist[3][1] == INT_MAX);
		assert(dist[3][2] == 11);
		assert(dist[3][3] == 6);

		cout << "\nTest 4 passed\n";
	}

	// Test 5: k = 0
	{
		vector<vector<pair<int, int>>> graph(3);

		AddEdge(graph, 0, 1, 1);
		AddEdge(graph, 1, 2, 1);

		auto dist = Dijkstra(graph, 0, 0);

		assert(dist.size() == 3);

		for (int node = 1; node < 3; ++node) {
			assert(dist[node][0] == INT_MAX);
		}

		assert(dist[0][0] == 0);

		cout << "\nTest 5 passed\n";
	}

	cout << "\nAll tests passed!\n";

	return 0;
}
