#include <iostream>
#include <ctime>

#include "Deque.h"

using namespace std;

class Player {
public:
	Player() : hp(rand() % 100 + 1) {
		cout << "Player Constructor" << endl;
	}

	Player(int hp) : hp(hp) {}

	Player(const Player& player) : hp(player.hp) {
		cout << "Player Copy Constructor" << endl;
	}

	~Player() {
		cout << "Player Destructor" << endl;
	}

public:
	int hp;
};

ostream& operator<<(ostream& os, const Player& player) {
	os << player.hp;
	return os;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	std::srand(std::time(NULL));

	// Deque<int> queue;
	// queue.Push_Front(1);
	// queue.Push_Front(2);
	// queue.Push_Front(3);

	// queue.Print();

	// queue.Push_Back(4);
	// queue.Push_Back(5);
	// queue.Push_Back(6);

	// queue.Print();

	// int& top = queue.Top();
	// top = 200;

	// int& back = queue.Back();
	// back = 300;

	// queue.Print();

	// int& value = queue.Pop_Back();
	// int& value2 = queue.Pop_Front();

	// cout << "Pop_Back: " << value << endl;
	// cout << "Pop_Front: " << value2 << endl;

	// queue.Print();

	Deque<Player> queue2;
	queue2.Push_Front(Player(1));
	queue2.Push_Front(Player(2));
	queue2.Push_Front(Player(3));

	queue2.Print();

	queue2.Push_Back(Player(4));
	queue2.Push_Back(Player(5));
	queue2.Push_Back(Player(6));

	queue2.Print();

	Player& top = queue2.Top();
	top.hp = 200;

	Player& back = queue2.Back();
	back.hp = 300;

	queue2.Print();

	Player& value = queue2.Pop_Back();
	Player& value2 = queue2.Pop_Front();

	cout << "Pop_Back: " << value << endl;
	cout << "Pop_Front: " << value2 << endl;

	queue2.Print();

	return 0;
}
