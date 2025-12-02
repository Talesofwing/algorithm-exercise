#include <iostream>
#include <ctime>

#include "LinkedHashTable.h"

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
void print(LinkedHashTable<K, V>& table) {
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
		keys.push_back(rand() % 100);
	}

	// LinkedHashTable<int, int> group;
	// for (int i = 0; i < SIZE; ++i) {
	// 	group.insert(keys[i], rand() % 100 + 1);
	// }

	// cout << "===== Initial LinkedHashTable =====" << endl;
	// print(group);

	// group.insert(keys[2], 55);

	// cout << "=====  LinkedHashTable Updated(" << keys[2] << ") =====" << endl;
	// print(group);

	// group.remove(keys.size() - 1);

	// cout << "=====  LinkedHashTable Removed(" << keys[keys.size() - 1] << ") =====" << endl;
	// print(group);

	// cout << "Get Keys[" << keys.size() - 2 << "](" << keys[keys.size() - 2] << "): " << group.get(keys[keys.size() - 2]) << endl;

	LinkedHashTable<int, Player> group2;
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

	cout << "Get Keys[" << keys.size() - 2 << "](" << keys[keys.size() - 2] << "): " << group2.get(keys[keys.size() - 2]) << endl;

	return 0;
}
