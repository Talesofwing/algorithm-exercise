#include <iostream>
#include <ctime>

#include "Stack.h"

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

	// Stack<int> stack;
	// for (int i = 0; i < 10; ++i) {
	// 	stack.Push(i);
	// }

	// stack.Print();

	// int& back = stack.Back();
	// back = 5;

	// stack.Print();

	// int& value = stack.Pop();

	// cout << "Pop: " << value << endl;

	// stack.Print();

	Stack<Player> stack2;
	for (int i = 0; i < 10; ++i) {
		stack2.Push(Player());
	}

	stack2.Print();

	Player& back = stack2.Back();
	back.hp = 500;

	stack2.Print();

	Player& value = stack2.Pop();

	cout << "Pop: " << value << endl;

	stack2.Print();

	return 0;
}
