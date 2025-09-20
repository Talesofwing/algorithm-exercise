#include <iostream>
#include <ctime>

#include "Queue.h"

using namespace std;

class Player {
public:
	Player() : hp(rand() % 100 + 1) {
		cout << "Player Constructor" << endl;
	}

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

	// Queue<int> queue;
	// for (int i = 0; i < 10; ++i) {
	// 	queue.Push(i);
	// }

	// queue.Print();

	// int& top = queue.Top();
	// top = 5;

	// queue.Print();

	// int& value = queue.Pop();

	// cout << "Pop: " << value << endl;

	// queue.Print();

	Queue<Player> queue2;
	for (int i = 0; i < 10; ++i) {
		cout << "i = " << i << " :";
		queue2.Push(Player());
	}

	queue2.Print();

	Player& top = queue2.Top();
	top.hp = 500;

	queue2.Print();

	Player& value = queue2.Pop();

	cout << "Pop: " << value << endl;

	queue2.Print();

	return 0;
}
