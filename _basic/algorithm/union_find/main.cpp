#include <iostream>

#include "UnionFind.h"

int main() {
	UnionFind uf(5);

	std::cout << std::boolalpha;
	std::cout << uf.Same(0, 1) << '\n';

	uf.Unite(0, 1);
	uf.Unite(2, 3);
	std::cout << uf.Same(0, 1) << '\n';
	std::cout << uf.Same(0, 2) << '\n';

	uf.Unite(1, 2);
	std::cout << uf.Same(0, 3) << '\n';
	std::cout << uf.Same(0, 4) << '\n';
}
