#include <iostream>
#include <ctime>
#include <vector>

#include "HashSet.h"

using namespace std;

class Player {
public:
	Player() : hp(rand() % 100 + 1) {}

	Player(const Player& player) : hp(player.hp) {}

	~Player() {}

	bool operator<(const Player& other) const {
		return hp < other.hp;
	}

public:
	int hp;
};

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	std::srand(std::time(NULL));

	Player player1, player2, player3, player4, player5, player6, player7, player8, player9, player10;

	HashSet<Player> group;
	group.add(player1);
	group.add(player2);
	group.add(player1);
	group.add(player2);

	cout << "===== Initial HashSet =====" << endl;
	cout << "Size: " << group.size() << endl;

	cout << "===== Remove player1 =====" << endl;
	group.remove(player1);
	cout << "Size: " << group.size() << endl;

	cout << "===== Add player1 =====" << endl;
	group.add(player1);
	group.add(player1);
	group.add(player1);
	group.add(player1);
	cout << "Size: " << group.size() << endl;

	return 0;
}
