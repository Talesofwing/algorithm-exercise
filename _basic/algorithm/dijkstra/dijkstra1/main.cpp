
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

void PrintDistances(const vector<int>& dist) {
	for (int i = 0; i < static_cast<int>(dist.size()); ++i) {
		cout << "Node " << i << ": ";

		if (dist[i] == INT_MAX) {
			cout << "Unreachable";
		} else {
			cout << dist[i];
		}

		cout << '\n';
	}
}

int main() {
	{
		vector<vector<pair<int, int>>> graph(5);

		AddEdge(graph, 0, 1, 4);
		AddEdge(graph, 0, 2, 1);
		AddEdge(graph, 2, 1, 2);
		AddEdge(graph, 1, 3, 1);
		AddEdge(graph, 2, 3, 5);
		AddEdge(graph, 3, 4, 3);

		auto dist = Dijkstra(graph, 0);

		vector<int> expected = {0, 3, 1, 4, 7};
		assert(dist == expected);

		cout << "Test 1 passed\n";
		PrintDistances(dist);
	}

	{
		vector<vector<pair<int, int>>> graph(4);

		AddEdge(graph, 0, 1, 5);
		AddEdge(graph, 1, 2, 2);

		auto dist = Dijkstra(graph, 0);

		assert(dist[0] == 0);
		assert(dist[1] == 5);
		assert(dist[2] == 7);
		assert(dist[3] == INT_MAX);

		cout << "\nTest 2 passed\n";
		PrintDistances(dist);
	}

	{
		vector<vector<pair<int, int>>> graph(1);

		auto dist = Dijkstra(graph, 0);

		assert(dist.size() == 1);
		assert(dist[0] == 0);

		cout << "\nTest 3 passed\n";
	}

	{
		vector<vector<pair<int, int>>> graph(4);

		AddEdge(graph, 0, 1, 10);
		AddEdge(graph, 0, 2, 2);
		AddEdge(graph, 2, 1, 3);
		AddEdge(graph, 1, 3, 1);
		AddEdge(graph, 2, 3, 20);

		auto dist = Dijkstra(graph, 0);

		vector<int> expected = {0, 5, 2, 6};
		assert(dist == expected);

		cout << "\nTest 4 passed\n";
		PrintDistances(dist);
	}

	cout << "\nAll tests passed!\n";

	return 0;
}
