#include <iostream>
#include <cassert>

/*
	雙向鏈表，且加入Dummy Node(Head & Tail)
*/

template<typename T>
class LinkedList {
private:
	struct Node {
	public:
		Node() : data(), next(nullptr), prev(nullptr) {}
		Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

	public:
		T data;
		Node* next;
		Node* prev;
	};

public:
	LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {
		_head = new Node();
		_tail = new Node();

		_head->next = _tail;
		_tail->prev = _head;
	}

	~LinkedList() {
		Clear();

		delete _head;
		delete _tail;
	}

public:
	void InsertAt(int index, const T& value) {
		assert(index >= 0 && index <= _size);

		Node* cur = _head->next;
		for (int i = 0; i < index; ++i) {
			cur = cur->next;
		}

		Node* node = new Node(value);
		node->prev = cur->prev;
		node->next = cur;
		cur->prev->next = node;
		cur->prev = node;

		++_size;
	}

	void InsertHead(const T& value) {
		Node* node = new Node(value);
		node->prev = _head;
		node->next = _head->next;
		_head->next->prev = node;
		_head->next = node;

		++_size;
	}

	void InsertTail(const T& value) {
		Node* node = new Node(value);
		node->prev = _tail->prev;
		node->next = _tail;
		_tail->prev->next = node;
		_tail->prev = node;

		++_size;
	}

	void RemoveAt(int index) {
		assert(index >= 0 && index < _size);

		Node* cur = _head->next;
		for (int i = 0; i < index; ++i) {
			cur = cur->next;
		}

		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		delete cur;

		--_size;
	}

	void RemoveHead() {
		assert(_size > 0);

		Node* cur = _head->next;
		_head->next = cur->next;
		cur->next->prev = _head;
		delete cur;
		--_size;
	}

	void RemoveTail() {
		assert(_size > 0);

		Node* cur = _tail->prev;
		_tail->prev = cur->prev;
		cur->prev->next = _tail;
		delete cur;
		--_size;
	}

	T& Front() noexcept {
		return _head->next->data;
	}

	const T& Front() const noexcept {
		return _head->next->data;
	}

	T& Back() noexcept {
		return _tail->prev->data;
	}

	const T& Back() const noexcept {
		return _tail->prev->data;
	}

	void Clear() noexcept {
		Node* cur = _head->next;
		while (cur != _tail) {
			Node* next = cur->next;
			delete cur;
			cur = next;
		}

		_head->next = _tail;
		_tail->prev = _head;
		_size = 0;
	}

public:
	// Helpers

	void Print() const noexcept {
		std::cout << "Size: " << _size << std::endl;
		Node* cur = _head->next;
		while (cur != _tail) {
			std::cout << "\tData: " << cur->data << std::endl;
			cur = cur->next;
		}
	}

private:
	Node* _head;
	Node* _tail;
	size_t _size;
};
