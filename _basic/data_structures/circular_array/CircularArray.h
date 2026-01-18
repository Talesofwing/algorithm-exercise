#include <iostream>
#include <cassert>

template<typename T>
class CircularArray {
	static const size_t INITIAL_CAPACITY = 4;

public:
	CircularArray() : _data(new T[INITIAL_CAPACITY]), _size(0), _capacity(INITIAL_CAPACITY), _head(0), _back(0) {}
	CircularArray(size_t capacity) : _data(new T[capacity]), _size(0), _capacity(capacity), _head(0), _back(0) {}

	~CircularArray() noexcept {
		Release();
	}

public:

	void InsertHead(const T& value) {
		Expand();

		_head = (_head - 1 + _capacity) % _capacity;
		_data[_head] = value;
		++_size;
	}

	void InsertBack(const T& value) {
		Expand();

		_data[_back] = value;
		_back = (_back + 1) % _capacity;
		++_size;
	}

	void InsertAt(size_t index, const T& value) {
		assert(index <= _size && "Index out of range");

		if (index == 0) {
			InsertHead(value);
			return;
		} else if (index == _size) {
			InsertBack(value);
			return;
		}

		Expand();

		size_t cur = (_head + index) % _capacity;

		for (size_t i = _size; i > index; i--) {
			_data[(i + _head) % _capacity] = std::move(_data[(i + _head - 1) % _capacity]);
		}

		_data[cur] = value;

		_size++;
		_back = (_head + _size) % _capacity;
	}

	void RemoveHead() {
		if (_size == 0) {
			return;
		}

		if constexpr (!std::is_trivially_destructible_v<T>) {
			_data[_head].~T();
		}

		_head = (_head + 1) % _capacity;

		--_size;
	}

	void RemoveBack() {
		if (_size == 0) {
			return;
		}

		_back = (_back - 1 + _capacity) % _capacity;

		if constexpr (!std::is_trivially_destructible_v<T>) {
			_data[_back].~T();
		}

		--_size;
	}

	void RemoveAt(size_t index) {
		assert(index < _size && "Index out of range");

		if (index == 0) {
			RemoveHead();
			return;
		} else if (index == _size - 1) {
			RemoveBack();
			return;
		}

		if constexpr (!std::is_trivially_destructible_v<T>) {
			_data[(_head + index) % _capacity].~T();
		}

		for (size_t i = index; i < _size - 1; i++) {
			_data[(i + _head) % _capacity] = std::move(_data[(i + _head + 1) % _capacity]);
		}

		--_size;
		_back = (_head + _size) % _capacity;
	}

	T& At(size_t index) {
		assert(index < _size && "Index out of range");

		return _data[(index + _head) % _capacity];
	}

	const T& At(size_t index) const {
		assert(index < _size && "Index out of range");

		return _data[(index + _head) % _capacity];
	}

	void Clear() noexcept {
		if constexpr (!std::is_trivially_destructible_v<T>) {
			for (size_t i = 0; i < _size; ++i) {
				_data[(_head + i) % _capacity].~T();
			}
		}

		_size = 0;
		_head = 0;
		_back = 0;
	}

	void shrink_to_fit() noexcept {
		if (_size == _capacity) {
			return;
		}

		if (_size == 0) {
			Release();

			return;
		}

		T* arr = new T[_size];
		for (size_t i = 0; i < _size; i++) {
			size_t index = (i + _head) % _capacity;
			arr[i] = std::move(_data[index]);
		}

		int size = _size;

		Release();

		_size = size;
		_data = arr;
		_capacity = size;
		_head = 0;
		_back = size;
	}

	void Resize(size_t size) {
		std::cout << "[CircularArray] Resize(" << size << ")" << std::endl;

		Reserve(size);

		if (size > _size) {
			for (size_t i = _size; i < size; ++i) {
				_data[(_head + i) % _capacity] = T();
			}
		} else {
			if constexpr (!std::is_trivially_destructible_v<T>) {
				for (size_t i = size; i < _size; ++i) {
					_data[(_head + i) % _capacity].~T();
				}
			}
		}

		_size = size;
		_back = (_head + _size) % _capacity;
	}

	void Reserve(size_t capacity) {
		std::cout << "[CircularArray] Reserve(" << capacity << ")" << std::endl;

		if (capacity <= _capacity) {
			return;
		}

		T* arr = new T[capacity];
		for (size_t i = 0; i < _size; i++) {
			size_t index = (i + _head) % _capacity;
			arr[i] = std::move(_data[index]);
		}

		int size = _size;

		Release();

		_data = arr;
		_capacity = capacity;
		_head = 0;
		_size = size;
		_back = size;
	}

	T& Front() noexcept {
		return _data[_head];
	}

	const T& Front() const noexcept {
		return _data[_head];
	}

	T& Back() noexcept {
		return _data[(_back - 1 + _capacity) % _capacity];
	}

	const T& Back() const noexcept {
		return _data[(_back - 1 + _capacity) % _capacity];
	}

	bool Empty() const noexcept {
		return _size == 0;
	}

	size_t Size() const noexcept {
		return _size;
	}

	void Print() const noexcept {
		std::cout << "[CircularArray] Size: " << _size << ", Capacity: " << _capacity << std::endl;
		std::cout << "\t";
		for (size_t i = 0; i < _size; ++i) {
			std::cout << _data[(i + _head) % _capacity] << ", ";
		}
		std::cout << std::endl;
	}

public:
	// operators

	T& operator[](size_t index) {
		return At(index);
	}

	const T& operator[](size_t index) const {
		return At(index);
	}

private:
	void Expand() {
		if (_size >= _capacity) {
			Reserve(_capacity == 0 ? INITIAL_CAPACITY : _capacity * 2);
		}
	}

	void Release() {
		std::cout << "[CircularArray] Release()" << std::endl;

		if (_data) {
			delete[] _data;
			_data = nullptr;
			_size = 0;
			_capacity = 0;
			_head = 0;
			_back = 0;
		}
	}

private:
	T* _data;
	size_t _size;
	size_t _capacity;

	size_t _head;
	size_t _back;
};
