#include <iostream>
#include <memory>
#include <cstring>
#include <cassert>

template<typename T>
class DynamicArray {
public:
	// Iterators

	class iterator {
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		iterator(T* ptr) : _ptr(ptr) {
			std::cout << "[Iterator] Constructor" << std::endl;
		}

		reference operator*() const { return *_ptr; }
		pointer operator->() const { return _ptr; }
		iterator& operator++() { ++_ptr; return *this; }
		iterator operator++(int) { iterator tmp = *this; ++*this; return tmp; }
		iterator& operator--() { --_ptr; return *this; }
		iterator operator--(int) { iterator tmp = *this; --*this; return tmp; }
		iterator operator+(difference_type n) const { return iterator(_ptr + n); }
		iterator operator-(difference_type n) const { return iterator(_ptr - n); }
		difference_type operator-(const iterator& other) const { return _ptr - other._ptr; }
		bool operator==(const iterator& other) const { return _ptr == other._ptr; }
		bool operator!=(const iterator& other) const { return _ptr != other._ptr; }
		bool operator<(const iterator& rhs) const { return _ptr < rhs._ptr; }
		bool operator>(const iterator& rhs) const { return _ptr > rhs._ptr; }
		bool operator<=(const iterator& rhs) const { return _ptr <= rhs._ptr; }
		bool operator>=(const iterator& rhs) const { return _ptr >= rhs._ptr; }
		reference operator[](difference_type n) const { return *(_ptr + n); }

	private:
		pointer _ptr;
	};

	class const_iterator {
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;

		const_iterator(pointer ptr = nullptr) : _ptr(ptr) {
			std::cout << "[Const Iterator] Constructor" << std::endl;
		}

		const_iterator(const iterator& it) : _ptr(it._ptr) {
			std::cout << "[Const Iterator] Copy Constructor" << std::endl;
		}

		reference operator*() const { return *_ptr; }
		pointer operator->() const { return _ptr; }
		const_iterator& operator++() { ++_ptr; return *this; }
		const_iterator operator++(int) { const_iterator tmp = *this; ++_ptr; return tmp; }
		const_iterator& operator--() { --_ptr; return *this; }
		const_iterator operator--(int) { const_iterator tmp = *this; --_ptr; return tmp; }
		const_iterator operator+(difference_type n) const { return const_iterator(_ptr + n); }
		const_iterator operator-(difference_type n) const { return const_iterator(_ptr - n); }
		difference_type operator-(const const_iterator& rhs) const { return _ptr - rhs._ptr; }
		bool operator==(const const_iterator& rhs) const { return _ptr == rhs._ptr; }
		bool operator!=(const const_iterator& rhs) const { return _ptr != rhs._ptr; }
		bool operator<(const const_iterator& rhs) const { return _ptr < rhs._ptr; }
		bool operator>(const const_iterator& rhs) const { return _ptr > rhs._ptr; }
		bool operator<=(const const_iterator& rhs) const { return _ptr <= rhs._ptr; }
		bool operator>=(const const_iterator& rhs) const { return _ptr >= rhs._ptr; }
		reference operator[](difference_type n) const { return *(_ptr + n); }

	private:
		pointer _ptr;
	};

	using size_type = std::size_t;

	iterator begin() { return iterator(_arr); }
	iterator end() { return iterator(_arr + _size); }

	const_iterator begin() const { return const_iterator(_arr); }
	const_iterator end() const { return const_iterator(_arr + _size); }
	const_iterator cbegin() const { return const_iterator(_arr); }
	const_iterator cend() const { return const_iterator(_arr + _size); }

public:
	// Constructors & Destructor

	DynamicArray()
		: _arr(nullptr), _size(0), _capacity(INITIAL_CAPACITY) {
		std::cout << "[DynamicArray] Constructor()" << std::endl;

		_arr = _alloc.allocate(_capacity);
	}

	explicit DynamicArray(size_t capacity)
		: _arr(nullptr), _size(0), _capacity(capacity) {
		std::cout << "[DynamicArray] Constructor(capacity)" << std::endl;

		if (capacity > 0) {
			_arr = _alloc.allocate(_capacity);
		}
	}

	DynamicArray(const DynamicArray& other) requires std::copy_constructible<T> {
		std::cout << "[DynamicArray] Copy Constructor" << std::endl;

		Copy(other);
	}

	DynamicArray(DynamicArray&& other) noexcept {
		std::cout << "[DynamicArray] Move Constructor" << std::endl;

		Move(std::move(other));
	}

	explicit DynamicArray(std::initializer_list<T> list) requires std::copy_constructible<T>
		: _arr(nullptr), _size(list.size()), _capacity(list.size()) {
		std::cout << "[DynamicArray] Initializer List Constructor" << std::endl;

		if (_capacity > 0) {
			_arr = _alloc.allocate(_capacity);

			if constexpr (std::is_trivially_copyable_v<T>) {
				std::memcpy(_arr, list.begin(), sizeof(T) * _size);
			} else {
				try {
					std::uninitialized_copy_n(list.begin(), _size, _arr);
				} catch (...) {
					_alloc.deallocate(_arr, _capacity);
					_arr = nullptr;
					_size = 0;
					_capacity = 0;
					throw;
				}
			}
		}
	}

	~DynamicArray() {
		Release();
	}

public:
	// Methods

	void Insert(const T& value) requires std::copy_constructible<T> {
		std::cout << "[DynamicArray] Insert(copy)" << std::endl;

		Expand();

		std::construct_at(_arr + _size, value);

		++_size;
	}

	void Insert(T&& value) requires std::move_constructible<T> {
		std::cout << "[DynamicArray] Insert(move)" << std::endl;

		Expand();

		std::construct_at(_arr + _size, std::move(value));

		++_size;
	}

	void Insert(int index, const T& value) requires std::copy_constructible<T> {
		std::cout << "[DynamicArray] Insert(copy index)" << std::endl;

		if (index < 0 || index > _size) {
			throw std::out_of_range("Index out of range");
		}

		Expand();

		for (int i = _size; i > index; i--) {
			std::construct_at(_arr + i, std::move(_arr[i - 1]));
			std::destroy_at(_arr + i - 1);
		}

		std::construct_at(_arr + index, value);

		++_size;
	}

	void Insert(int index, T&& value) requires std::move_constructible<T> {
		std::cout << "[DynamicArray] Insert(move index)" << std::endl;

		if (index < 0 || index > _size) {
			throw std::out_of_range("Index out of range");
		}

		Expand();

		for (int i = _size; i > index; i--) {
			std::construct_at(_arr + i, std::move(_arr[i - 1]));
			std::destroy_at(_arr + i - 1);
		}

		std::construct_at(_arr + index, std::move(value));

		++_size;
	}

	template<typename... Args>
	void Emplace(Args&&... args) {
		std::cout << "[DynamicArray] Emplace()" << std::endl;

		Expand();

		std::construct_at(_arr + _size, std::forward<Args>(args)...);

		++_size;
	}

	template<typename... Args>
	void EmplaceAt(int index, Args&&... args) {
		std::cout << "[DynamicArray] Emplace(index)" << std::endl;

		if (index < 0 || index > _size) {
			throw std::out_of_range("Index out of range");
		}

		Expand();

		for (int i = _size; i > index; i--) {
			std::construct_at(_arr + i, std::move(_arr[i - 1]));
			std::destroy_at(_arr + i - 1);
		}

		std::construct_at(_arr + index, std::forward<Args>(args)...);

		++_size;
	}

	void Remove() {
		std::cout << "[DynamicArray] Remove()" << std::endl;

		if (_size <= 0) {
			throw std::out_of_range("Index out of range");
		}

		std::destroy_at(_arr + _size - 1);

		--_size;
	}

	void Remove(int index) {
		std::cout << "[DynamicArray] Remove(index)" << std::endl;

		if (index < 0 || index >= _size) {
			throw std::out_of_range("Index out of range");
		}

		for (int i = index; i < _size - 1; i++) {
			std::destroy_at(_arr + i);
			std::construct_at(_arr + i, std::move(_arr[i + 1]));
		}

		std::destroy_at(_arr + _size - 1);

		--_size;
	}

	void Remove(int start, int end) {
		std::cout << "[DynamicArray] Remove(start, end)" << std::endl;

		if (start < 0 || start >= _size ||
			end < 0 || end >= _size ||
			start > end) {
			throw std::out_of_range("Index out of range");
		}

		for (int i = start; i <= end; i++) {
			std::destroy_at(_arr + i);
		}

		int dest = start;
		for (int i = end + 1; i < _size; i++, dest++) {
			std::construct_at(_arr + dest, std::move(_arr[i]));
			std::destroy_at(_arr + i);
		}

		_size -= (end - start + 1);
	}

	T& At(int index) {
		assert(index >= 0 && index < _size && "Index out of range");

		return _arr[index];
	}

	const T& At(int index) const {
		assert(index >= 0 && index < _size && "Index out of range");

		return _arr[index];
	}

	void Reserve(int capacity) requires std::copy_constructible<T> {
		std::cout << "[DynamicArray] Reserve(" << capacity << ")" << std::endl;

		if (capacity <= _capacity) {
			return;
		}

		T* arr = _alloc.allocate(capacity);

		try {
			if constexpr (std::is_move_constructible_v<T>) {
				std::uninitialized_move_n(_arr, _size, arr);
			} else {
				std::uninitialized_copy_n(_arr, _size, arr);
			}
		} catch (...) {
			_alloc.deallocate(arr, capacity);
			throw;
		}

		int size = _size;

		Release();

		_arr = arr;
		_capacity = capacity;
		_size = size;
	}

	void Resize(int size) requires std::default_initializable<T>&& std::copy_constructible<T> {
		std::cout << "[DynamicArray] Resize(" << size << ")" << std::endl;

		if (size > _capacity) {
			Reserve(size);
		}

		if (size > _size) {
			for (int i = _size; i < size; i++) {
				std::construct_at(_arr + i);
			}
		} else {
			for (int i = size; i < _size; i++) {
				std::destroy_at(_arr + i);
			}
		}

		_size = size;
	}

	void shrink_to_fit() requires std::copy_constructible<T> {
		if (_size == _capacity) {
			return;
		}

		if (_size == 0) {
			Release();

			return;
		}

		T* arr = _alloc.allocate(_size);

		try {
			if constexpr (std::is_move_constructible_v<T>) {
				std::uninitialized_move_n(_arr, _size, arr);
			} else {
				std::uninitialized_copy_n(_arr, _size, arr);
			}
		} catch (...) {
			_alloc.deallocate(arr, _size);
			throw;
		}

		int size = _size;

		Release();

		_arr = arr;
		_capacity = size;
		_size = size;
	}

	void Clear() noexcept(noexcept(std::destroy_n(_arr, _size))) {
		if (_arr) {
			std::destroy_n(_arr, _size);
			_size = 0;
		}
	}

	T& Front() {
		if (_size == 0) {
			throw std::out_of_range("Index out of range");
		}

		return _arr[0];
	}

	const T& Front() const {
		if (_size == 0) {
			throw std::out_of_range("Index out of range");
		}

		return _arr[0];
	}

	T& Back() {
		if (_size == 0) {
			throw std::out_of_range("Index out of range");
		}

		return _arr[_size - 1];
	}

	const T& Back() const {
		if (_size == 0) {
			throw std::out_of_range("Index out of range");
		}

		return _arr[_size - 1];
	}

	int Size() const noexcept {
		return _size;
	}

	int Capacity() const noexcept {
		return _capacity;
	}

	bool IsEmpty() const noexcept {
		return _size == 0;
	}

	bool IsFull() const noexcept {
		return _size == _capacity;
	}

public:
	// Operators

	DynamicArray& operator=(const DynamicArray& other) requires std::copy_constructible<T> {
		std::cout << "[DynamicArray] Copy operator" << std::endl;

		if (this == &other) {
			return *this;
		}

		Copy(other);

		return *this;
	}

	DynamicArray& operator=(DynamicArray&& other) noexcept {
		std::cout << "[DynamicArray] Move operator" << std::endl;

		Move(std::move(other));

		return *this;
	}

	T& operator[](int index) {
		return At(index);
	}

	const T& operator[](int index) const {
		return At(index);
	}

protected:
	// Internal Helper Methods

	void Expand() requires std::copy_constructible<T> {
		if (IsFull()) {
			int newCap = _capacity == 0 ? INITIAL_CAPACITY : _capacity * 2;
			Reserve(newCap);
		}
	}

	/// @brief Copy from another DynamicArray.
	/// @param other The array to copy from.
	/// @exception May throw if element copy constructor throws or allocation fails.
	/// @note If the other array is empty, the current array will be destroyed.
	void Copy(const DynamicArray& other) requires std::copy_constructible<T> {
		if (other._capacity == 0) {
			Release();

			_arr = nullptr;
			_size = 0;
			_capacity = 0;
			return;
		}

		if (_capacity >= other._size) {
			// Capacity sufficient, reuse memory.

			std::destroy_n(_arr, _size);
			std::uninitialized_copy_n(other._arr, other._size, _arr);

			_size = other._size;
		} else {
			// Strong Exception Guarantee

			T* arr = _alloc.allocate(other._capacity);

			try {
				// uninitialized_copy_n
				//    Can be copied with placement new.If something goes wrong, the memory is deallocated automatically
				std::uninitialized_copy_n(other._arr, other._size, arr);
			} catch (...) {
				_alloc.deallocate(arr, other._capacity);
				arr = nullptr;
				throw;
			}

			Release();

			_arr = arr;
			_size = other._size;
			_capacity = other._capacity;
		}
	}

	void Move(DynamicArray&& other) noexcept {
		if (this == &other) {
			return;
		}

		Release();

		_arr = other._arr;
		_size = other._size;
		_capacity = other._capacity;

		other._arr = nullptr;
		other._size = 0;
		other._capacity = 0;
	}

	void Release() noexcept(noexcept(std::destroy_n(_arr, _size))) {
		if (_arr) {
			std::destroy_n(_arr, _size);
			_alloc.deallocate(_arr, _capacity);

			_arr = nullptr;
			_size = 0;
			_capacity = 0;
		}
	}

private:
	// Members

	T* _arr = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;

	std::allocator<T> _alloc;

	static const int INITIAL_CAPACITY = 4;
};
