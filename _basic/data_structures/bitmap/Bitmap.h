#include <iostream>
#include <cassert>

template<int _Nb>  // Number of bits
class Bitmap {
	static_assert(_Nb > 0, "Width must be a positive integer.");

public:
	Bitmap() = default;

public:
	void set(int index) {
		assert(index >= 0 && index < _Nb && "Index out of bounds.");
		int arrayIndex = index / BITS_PER_LONG;
		int bitPosition = index % BITS_PER_LONG;
		_bitmap[arrayIndex] |= (1L << bitPosition);
	}

	void clear(int index) {
		assert(index >= 0 && index < _Nb && "Index out of bounds.");
		int arrayIndex = index / BITS_PER_LONG;
		int bitPosition = index % BITS_PER_LONG;
		_bitmap[arrayIndex] &= ~(1L << bitPosition);
	}

	bool get(int index) const {
		assert(index >= 0 && index < _Nb && "Index out of bounds.");
		int arrayIndex = index / BITS_PER_LONG;
		int bitPosition = index % BITS_PER_LONG;
		return (_bitmap[arrayIndex] & (1L << bitPosition)) != 0;
	}

private:
	static constexpr int BITS_PER_LONG = sizeof(long) * 8;
	static constexpr int ARRAY_SIZE = (_Nb + BITS_PER_LONG - 1) / BITS_PER_LONG;  // >> 6; (divided by 64)

	long _bitmap[ARRAY_SIZE] = {0};
};
