#pragma once

#include <vector>

class UnionFind {
public:
	UnionFind(int n) : _count(n), _parent(n), _rank(n, 0) {
		for (int i = 0; i < n; ++i) {
			_parent[i] = i;
		}
	}

public:
	int Root(int x) {
		return _parent[x] == x ? x : _parent[x] = Root(_parent[x]);
	}

	void Unite(int x, int y) {
		int X = Root(x);
		int Y = Root(y);

		if (X == Y) {
			return;
		}

		if (_rank[X] < _rank[Y]) {
			_parent[X] = Y;
		} else {
			_parent[Y] = X;

			if (_rank[X] == _rank[Y]) {
				++_rank[X];
			}
		}

		--_count;
	}

	bool Same(int x, int y) {
		return Root(x) == Root(y);
	}

	int Count() const {
		return _count;
	}

private:
	int _count;
	std::vector<int> _parent;
	std::vector<int> _rank;
};
