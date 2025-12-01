#include <iostream>
#include <ctime>

#include "HashTable.h"

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

template<typename K, typename V>
void print(HashTable<K, V>& table) {
	cout << "HashTable Size: " << table.size() << endl;
	for (const auto& key : table.keys()) {
		cout << "\tKey: " << key << flush;
		auto& value = table.get(key);
		cout << ", Value: " << value << endl;
	}
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	std::srand(std::time(NULL));

	vector<int> keys;
	for (int i = 0; i < 10; ++i) {
		keys.push_back(rand() % 100);
	}

	// HashTable<int, int> group;
	// for (int i = 0; i < 10; ++i) {
	// 	group.insert(keys[i], rand() % 100 + 1);
	// }

	// cout << "===== Initial HashTable =====" << endl;
	// print(group);

	// group.insert(keys[5], 55);

	// cout << "=====  HashTable Updated(" << keys[5] << ") =====" << endl;
	// print(group);

	// group.remove(keys[3]);

	// cout << "=====  HashTable Removed(" << keys[3] << ") =====" << endl;
	// print(group);

	// cout << "Get Keys[7](" << keys[7] << "): " << group.get(keys[7]) << endl;

	HashTable<int, Player> group2;
	for (int i = 0; i < 10; ++i) {
		group2.insert(keys[i], Player());
	}

	cout << "===== Initial HashTable =====" << endl;
	print(group2);

	group2.insert(keys[5], Player());

	cout << "=====  HashTable Updated(" << keys[5] << ") =====" << endl;
	print(group2);

	group2.remove(keys[3]);

	cout << "=====  HashTable Removed(" << keys[3] << ") =====" << endl;
	print(group2);

	cout << "Get Keys[7](" << keys[7] << "): " << group2.get(keys[7]) << endl;

	return 0;
}
