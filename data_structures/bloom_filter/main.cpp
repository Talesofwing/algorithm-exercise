#include <iostream>
#include <ctime>

#include "BloomFilter.h"

using namespace std;

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	std::srand(std::time(NULL));

	BloomFilter<int, 100> bloomFilter(6);
	bloomFilter.add(23);
	bloomFilter.add(29);

	if (bloomFilter.contains(23)) {
		// Will print
		cout << "Bloom Filter contains 23" << endl;
	} else {
		cout << "Bloom Filter does not contain 23" << endl;
	}

	if (bloomFilter.contains(26)) {
		// Will print
		cout << "Bloom Filter contains 26" << endl;
	} else {
		cout << "Bloom Filter does not contain 26" << endl;
	}

	return 0;
}
