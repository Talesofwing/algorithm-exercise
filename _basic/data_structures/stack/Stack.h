#include "LinkedList.h"

template<typename T>
class Stack {
public:
	Stack() {}

public:
	void Push(const T& value) {
		_stack.InsertTail(value);
	}

	T& Pop() {
		T& value = _stack.Back();
		_stack.RemoveTail();

		return value;
	}

	T& Back() {
		return _stack.Back();
	}

	int Size() const {
		return _stack.Size();
	}

	bool Empty() const {
		return Size() == 0;
	}

	void Print() {
		_stack.Print();
	}

private:
	LinkedList<T> _stack;
};
