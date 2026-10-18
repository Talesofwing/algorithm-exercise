#pragma once

#include <vector>
#include <queue>
#include <climits>
#include <utility>
#include <cstdlib>

struct State {
public:
	State(int x, int y, int g, int f) : X(x), Y(y), G(g), F(f) {}

public:
	bool operator<(const State& other) const {
		return F > other.F;
	}

public:
	int X, Y;
	int G, F;   // F = G + H
};

inline int Heuristic(int x1, int y1, int x2, int y2) {
	return std::max(std::abs(x1 - x2), std::abs(y1 - y2));
}

inline int AStar(const std::vector<std::vector<int>>& grid) {
	int n = grid.size();

	if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
		return -1;
	}

	if (n == 1) {
		return 1;
	}

	std::vector<std::vector<int>> distTo(n, std::vector<int>(n, INT_MAX));
	std::priority_queue<State> pq;

	pq.emplace(0, 0, 1, 1 + Heuristic(0, 0, n - 1, n - 1));
	distTo[0][0] = 1;

	std::vector<std::vector<int>> dirs = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	while (!pq.empty()) {
		State state = pq.top();
		pq.pop();

		int curX = state.X, curY = state.Y;
		int curG = state.G;

		if (curX == n - 1 && curY == n - 1) {
			return curG;
		}

		if (distTo[curX][curY] < curG) {
			continue;
		}

		for (const auto& dir : dirs) {
			int nx = curX + dir[0], ny = curY + dir[1];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n || grid[nx][ny] == 1) {
				continue;
			}

			int ng = curG + 1;

			if (distTo[nx][ny] <= ng) {
				continue;
			}

			distTo[nx][ny] = ng;
			int f = ng + Heuristic(nx, ny, n - 1, n - 1);
			pq.emplace(nx, ny, ng, f);
		}
	}

	return -1;
}
