#include <iostream>
#include <ctime>

#include "LinkedList.h"

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

	// LinkedList<int> list;
	// list.InsertHead(1);
	// list.InsertTail(2);
	// list.InsertAt(1, 5);
	// list.InsertAt(3, 10);

	// list.Print();

	// list.RemoveHead();
	// list.RemoveTail();
	// list.RemoveAt(0);

	// list.Print();

	// list.Clear();

	// list.Print();

	LinkedList<Player> list2;
	list2.InsertHead(Player());
	list2.InsertTail(Player());
	list2.InsertAt(1, Player());
	list2.InsertAt(3, Player());

	list2.Print();

	list2.RemoveHead();
	list2.RemoveTail();
	list2.RemoveAt(0);

	list2.Print();

	list2.Clear();

	list2.Print();

	return 0;
}
