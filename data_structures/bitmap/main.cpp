#include <iostream>
#include <ctime>

#include "Bitmap.h"

using namespace std;

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	std::srand(std::time(NULL));

	Bitmap<128> bitmap;
	bitmap.set(5);
	bitmap.set(64);

	cout << bitmap.get(5) << "\n";   // Should print 1
	cout << bitmap.get(64) << "\n";  // Should print 1
	cout << bitmap.get(127) << "\n"; // Should print 0
	bitmap.clear(5);
	cout << bitmap.get(5) << "\n";   // Should print 0
	// cout << bitmap.get(128) << "\n"; // Should trigger an assertion failure

	return 0;
}
