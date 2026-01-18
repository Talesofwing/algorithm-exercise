#include <vector>
#include <functional>

/*
	Priority Queue implemented using Heap (無狀態 Comparator)
*/

template<typename T, typename Comparator = std::less<T>>
class PriorityQueue {
private:
	static const int DEFAULT_CAPACITY = 4;

public:
	PriorityQueue() {
		_heap.reserve(DEFAULT_CAPACITY);
	}

	PriorityQueue(int capacity) {
		_heap.reserve(capacity);
	}

public:
	void Push(const T& value) {
		_heap.push_back(value);
		Swim(Size() - 1);
	}

	T Pop() {
		if (Empty()) {
			throw std::out_of_range("PriorityQueue is empty.");
		}

		T top = std::move(_heap[0]);
		if (Size() > 1) {
			_heap[0] = std::move(_heap.back());
		}

		_heap.pop_back();

		if (!Empty()) {
			Sink(0);
		}

		return top;
	}

	const T& Peek() const {
		return _heap[0];
	}

	int Size() const {
		return _heap.size();
	}

	bool Empty() const {
		return Size() == 0;
	}

	void Print() const {
		for (const auto& item : _heap) {
			std::cout << item << " ";
		}
		std::cout << std::endl;
	}

private:
	int Left(int index) const {
		return 2 * index + 1;
	}

	int Right(int index) const {
		return 2 * index + 2;
	}

	int Parent(int index) const {
		return (index - 1) / 2;
	}

	void Sink(int index) {
		while (true) {
			int v = index;

			if (Left(index) < Size() && Comparator()(_heap[Left(index)], _heap[v])) {
				v = Left(index);
			}

			if (Right(index) < Size() && Comparator()(_heap[Right(index)], _heap[v])) {
				v = Right(index);
			}

			if (v == index) {
				break;
			}

			std::swap(_heap[index], _heap[v]);
			index = v;
		}
	}

	void Swim(int index) {
		while (index > 0 && Comparator()(_heap[index], _heap[Parent(index)])) {
			std::swap(_heap[index], _heap[Parent(index)]);
			index = Parent(index);
		}
	}

private:
	std::vector<T> _heap;
};
