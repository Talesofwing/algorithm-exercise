#include <iostream>
#include <iomanip>
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
	// cout << fixed << setprecision(15);

	srand(time(NULL));

	const int count = 2;
	SkipList<int> sl;
	vector<double> scores(count);
	for (int i = 0; i < count; ++i) {
		double score = rand() % 100 + 1;
		scores.emplace_back(score);
		sl.insert(i, score);
	}

	cout << "===== Original =====" << endl;
	sl.display();

	int index = rand() % count;
	SkipList<int>::SkipListNode* node = sl.find_by_index(index);
	cout << "\n===== Update(index = " << index << ", hp = " << node->obj << ") =====" << endl;
	node->obj = 1000;
	sl.display();

	cout << "\n===== Find(index = 1) =====" << endl;
	node = sl.find_by_index(1);
	cout << "By Index(1): " << node->obj << endl;
	cout << "By Score(" << node->score << "): " << sl.find_by_score(node->obj, node->score)->obj << endl;
	cout << "By Obj(" << node->obj << "): " << sl.find_by_obj(node->obj)->obj << endl;

	cout << "\n===== Remove =====" << endl;
	sl.remove_by_index(0);
	sl.remove_by_index(0);
	sl.display();

	cout << "\n===== Insert =====" << endl;
	sl.insert(10, 1);
	sl.insert(100, 10);
	sl.display();

	cout << "\n===== Clear =====" << endl;
	sl.clear();
	sl.display();

	cout << "\n===== Insert =====" << endl;
	sl.insert(10, 5324);
	sl.insert(5, 123);
	sl.display();
}
