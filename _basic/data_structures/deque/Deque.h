#include "LinkedList.h"

template<typename T>
class Deque {
public:
	Deque() {}

public:
	void Push_Front(const T& value) {
		_deque.InsertHead(value);
	}

	void Push_Back(const T& value) {
		_deque.InsertTail(value);
	}

	T& Pop_Front() {
		T& value = _deque.Front();
		_deque.RemoveHead();

		return value;
	}

	T& Pop_Back() {
		T& value = _deque.Back();
		_deque.RemoveTail();

		return value;
	}

	T& Top() {
		return _deque.Front();
	}

	T& Back() {
		return _deque.Back();
	}

	int Size() const {
		return _deque.Size();
	}

	bool Empty() const {
		return Size() == 0;
	}

	void Print() {
		_deque.Print();
	}

private:
	LinkedList<T> _deque;
};
