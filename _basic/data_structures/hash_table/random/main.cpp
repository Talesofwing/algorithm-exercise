#include <iostream>
#include <ctime>

#include "RandomHashTable.h"

using namespace std;

class Player {
public:
	Player() : hp(rand() % 100 + 1) {
		// cout << "Player Constructor" << endl;
	}

	Player(const Player& player) : hp(player.hp) {
		// cout << "Player Copy Constructor" << endl;
	}

	~Player() {
		// cout << "Player Destructor" << endl;
	}

public:
	int hp;
};

ostream& operator<<(ostream& os, const Player& player) {
	os << player.hp;
	return os;
}

template<typename K, typename V>
void print(RandomHashTable<K, V>& table) {
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

	constexpr int SIZE = 10;

	vector<int> keys;
	for (int i = 0; i < SIZE; ++i) {
		keys.push_back(rand() % 20);
	}

	// RandomHashTable<int, int> group;
	// for (int i = 0; i < SIZE; ++i) {
	// 	group.insert(keys[i], rand() % 100 + 1);
	// }

	// cout << "===== Initial LinkedHashTable =====" << endl;
	// print(group);

	// group.insert(keys[2], 55);

	// cout << "=====  LinkedHashTable Updated(" << keys[2] << ") =====" << endl;
	// print(group);

	// group.remove(keys[keys.size() - 1]);

	// cout << "=====  LinkedHashTable Removed(" << keys[keys.size() - 1] << ") =====" << endl;
	// print(group);

	// int key = group.randomKey();
	// cout << "Random Key[" << key << "]: " << group.get(key) << endl;

	RandomHashTable<int, Player> group2;
	for (int i = 0; i < SIZE; ++i) {
		group2.insert(keys[i], Player());
	}

	cout << "===== Initial HashTable =====" << endl;
	print(group2);

	group2.insert(keys[2], Player());

	cout << "=====  HashTable Updated(" << keys[2] << ") =====" << endl;
	print(group2);

	group2.remove(keys[keys.size() - 1]);

	cout << "=====  HashTable Removed(" << keys[keys.size() - 1] << ") =====" << endl;
	print(group2);

	int key = group2.randomKey();
	cout << "Random Key[" << key << "]: " << group2.get(key) << endl;

	return 0;
}
