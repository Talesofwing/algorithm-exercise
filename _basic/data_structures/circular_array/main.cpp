#include <iostream>
#include <ctime>

#include "CircularArray.h"

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

	// CircularArray<int> a(2);
	// a.InsertHead(1);
	// a.InsertBack(2);
	// a.InsertAt(1, 5);
	// a.InsertAt(2, 10);

	// a.Print();

	// a.RemoveHead();
	// a.RemoveBack();
	// a.RemoveAt(1);

	// a.Print();

	// a.shrink_to_fit();

	// a.Print();

	// a.Clear();

	// a.Print();

	CircularArray<Player> a2(2);
	a2.InsertHead({});
	a2.InsertBack({});
	a2.InsertAt(1, {});
	a2.InsertAt(2, {});

	a2.Print();

	a2.RemoveHead();
	a2.RemoveBack();
	a2.RemoveAt(1);

	a2.Print();

	a2.shrink_to_fit();

	a2.Print();

	a2.Clear();

	a2.Print();

	return 0;
}
