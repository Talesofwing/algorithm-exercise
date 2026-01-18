#include <iostream>
#include <ctime>

#include "PriorityQueue.h"

using namespace std;

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	std::srand(std::time(NULL));

	PriorityQueue<int> queue;
	for (int i = 4; i >= 0; --i) {
		queue.Push(i);
	}

	queue.Print();

	const int& top = queue.Peek();
	cout << "Top: " << top << endl;

	int value = queue.Pop();
	cout << "Pop: " << value << endl;

	queue.Print();

	PriorityQueue<int, std::greater<int>> queue2;
	for (int i = 0; i < 5; ++i) {
		queue2.Push(i);
	}

	queue2.Print();

	const int& top2 = queue2.Peek();
	cout << "Top: " << top2 << endl;

	int value2 = queue2.Pop();
	cout << "Pop: " << value2 << endl;

	queue2.Print();

	return 0;
}
