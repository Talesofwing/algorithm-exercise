#include <iostream>
#include <bitset>

template<typename T, size_t BITSET_SIZE>
class BloomFilter {
public:
	BloomFilter(int hashFunctionCount) : _hashFunctionCount(hashFunctionCount) {}

public:
	void add(const T& element) {
		for (int i = 0; i < _hashFunctionCount; ++i) {
			int hashValue = hash(element, i);
			_bitmap.set(hashValue);

			std::cout << "[Add] Bitmap Index: " << hashValue << std::endl;
		}
	}

	bool contains(const T& element) {
		for (int i = 0; i < _hashFunctionCount; ++i) {
			int hashValue = hash(element, i);
			std::cout << "[Contains] Bitmap Index: " << hashValue << std::endl;
			if (!_bitmap.test(hashValue)) {
				return false;
			}
		}

		return true;
	}

private:
	int hash(const T& element, int seed) {
		std::hash<T> hasher;
		return (hasher(element) + seed) % BITSET_SIZE;
	}

private:
	std::bitset<BITSET_SIZE> _bitmap;
	int _hashFunctionCount;
};
