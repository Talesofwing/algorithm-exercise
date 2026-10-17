#include <iostream>
#include <stack>

#include "Graph.h"

using namespace std;

// Solve the Eulerian path problem for undirected graphs using brute force DFS to find all possible Eulerian paths

Graph graph;
vector<bool> visited;
int totalNodes = -1;
int totalEdges = -1;

int startNode = -1;
int endNode = -1;
int curEdgeCount = 0;

vector<int> path;

bool find_start_and_end_nodes() {
	// 找出起點和終點
	int oddDegreeCount = 0;
	for (int i = 0; i < totalNodes; ++i) {
		int degree = graph.getEdges(i).size();
		if (degree == 0) {
			// Isolated node, skip
			continue;
		}

		if (degree % 2 == 1) {
			++oddDegreeCount;
			if (startNode == -1) {
				startNode = i;
			} else if (endNode == -1) {
				endNode = i;
			} else {
				// Above two nodes with odd degree already found -> not Eulerian
				return false;
			}
		}
	}

	if (oddDegreeCount == 0) {
		// Eulerian Circuit

		for (int i = 0; i < totalNodes; ++i) {
			if (!graph.getEdges(i).empty()) {  // degree > 0
				startNode = endNode = i;
				break;
			}
		}

		cout << "Is Eulerian Circuit" << endl;

		return true;
	} else if (oddDegreeCount == 2) {
		// Semi-Eulerian Graph

		cout << "Is Semi-Eulerian Graph" << endl;

		return true;
	} else {
		// Non-Eulerian Graph

		return false;
	}
}

void find_eulerian_path(int from) {
	const std::vector<Graph::Edge>& edges = graph.getEdges(from);
	path.push_back(from);

	if (from == endNode) {
		if (curEdgeCount == totalEdges) {
			for (int node : path) {
				cout << node << " ";
			}
			cout << endl;
			path.pop_back();
			return;
		}
	}

	for (int i = 0; i < edges.size(); ++i) {
		int edgeId = edges[i].id;
		if (!visited[edgeId]) {
			int to = edges[i].to;

			visited[edgeId] = true;
			++curEdgeCount;
			find_eulerian_path(to);
			--curEdgeCount;
			visited[edgeId] = false;
		}
	}

	path.pop_back();
}

int main() {
	cin >> totalNodes;
	cin >> totalEdges;

	// Add nodes
	for (int i = 0; i < totalNodes; ++i) {
		graph.addNode();
	}

	// Add edges
	for (int i = 0; i < totalEdges; ++i) {
		int from = 0;
		int to = 0;
		cin >> from >> to;
		graph.addEdge(i, from, to);
	}

	// Traverse and display the entire graph
	cout << endl << "Graph Structure:" << endl;
	for (int i = 0; i < totalNodes; ++i) {
		const std::vector<Graph::Edge>& edges = graph.getEdges(i);
		cout << "Node " << i << " (degree: " << edges.size() << ") -> ";
		for (const auto& edge : edges) {
			cout << edge.to << "[id:" << edge.id << "] ";
		}
		cout << endl;
	}
	cout << endl;

	// Initialize visited edges tracker
	visited.resize(totalEdges, false);

	if (!find_start_and_end_nodes()) {
		cout << "No Eulerian Path" << endl;
	} else {
		cout << "StartNode: " << startNode << ", EndNode: " << endNode << endl;
		find_eulerian_path(startNode);
	}

	return 0;
}
