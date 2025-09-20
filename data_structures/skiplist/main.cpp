#include <iostream>
#include <ctime>

#include "SkipList.h"

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

	SkipList<int> sl;
	for (int i = 0; i < 20; ++i) {
		sl.insert(i, rand() % 100 + 1);
	}

	cout << "===== Original =====" << endl;
	sl.display();

	return 0;

	cout << "===== Update =====" << endl;
	int& hp = sl.at(0);
	hp = 1000;
	sl.display();

	cout << "===== Insert =====" << endl;
	sl.insert(10, 1);
	sl.insert(100, 10);
	sl.display();

	cout << "===== Remove =====" << endl;
	sl.remove(5);
	sl.remove(1);
	sl.display();
}
