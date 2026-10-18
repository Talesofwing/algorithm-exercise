#include "AStar.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void showExample(const string& title, const vector<vector<int>>& grid) {
	cout << title << '\n';

	for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
		for (int col = 0; col < static_cast<int>(grid[row].size()); ++col) {
			if (row == 0 && col == 0) {
				cout << "S ";
			} else if (row == static_cast<int>(grid.size()) - 1 &&
				col == static_cast<int>(grid[row].size()) - 1) {
				cout << "G ";
			} else {
				cout << (grid[row][col] == 1 ? "# " : ". ");
			}
		}
		cout << '\n';
	}

	cout << "Shortest path length: " << AStar(grid) << "\n\n";
}

int main() {
	cout << "A* examples (S: start, G: goal, #: obstacle, .: open cell)\n";
	cout << "Movement is allowed in eight directions; the path length includes the start cell.\n\n";

	showExample("1. Open map", {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	});

	showExample("2. Find a route around obstacles", {
		{0, 1, 0, 0, 0},
		{0, 1, 0, 1, 0},
		{0, 0, 0, 1, 0},
		{1, 1, 0, 0, 0},
		{0, 0, 0, 1, 0}
	});

	showExample("3. No route to the goal", {
		{0, 1, 0},
		{1, 1, 0},
		{0, 0, 0}
	});

	return 0;
}
