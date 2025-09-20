#include "LinkedList.h"

template<typename T>
class Queue {
public:
	Queue() {}

public:
	void Push(const T& value) {
		_queue.InsertTail(value);
	}

	T& Pop() {
		T& value = _queue.Front();
		_queue.RemoveHead();

		return value;
	}

	T& Top() {
		return _queue.Front();
	}

	int Size() const {
		return _queue.Size();
	}

	bool Empty() const {
		return Size() == 0;
	}

	void Print() {
		_queue.Print();
	}

private:
	LinkedList<T> _queue;
};
