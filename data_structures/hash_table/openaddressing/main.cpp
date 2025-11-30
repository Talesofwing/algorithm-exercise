#include <iostream>
#include <ctime>

#include "HashTable_MarkDeleted.h"
#include "HashTable_MoveElement.h"

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
void print(HashTable<K, V>& table) {
	cout << "HashTable Size: " << table.size() << endl;
	for (const auto& key : table.keys()) {
		cout << "\tKey: " << key << flush;
		auto& value = table.get(key);
		cout << ", Value: " << value << endl;
	}
}

template<typename K, typename V>
void print(HashTable2<K, V>& table) {
	cout << "HashTable Size: " << table.size() << endl;
	for (const auto& key : table.keys()) {
		cout << "\tKey: " << key << flush;
		auto& value = table.get(key);
		cout << ", Value: " << value << endl;
	}
}


void test1() {
	// Move elements
	constexpr int count = 5;

	vector<int> keys;
	for (int i = 0; i < count; ++i) {
		keys.push_back(rand() % 100);
	}

	HashTable<int, int> group;
	for (int i = 0; i < count; ++i) {
		group.insert(keys[i], rand() % 100 + 1);
	}

	cout << "===== Initial HashTable =====" << endl;
	print(group);

	group.insert(keys[2], 55);

	cout << "=====  HashTable Updated(" << keys[2] << ") =====" << endl;
	print(group);

	group.remove(keys[3]);

	cout << "=====  HashTable Removed(" << keys[3] << ") =====" << endl;
	print(group);

	cout << "Get Keys[4](" << keys[4] << "): " << group.get(keys[4]) << endl;

	// HashTable<int, Player> group2;
	// for (int i = 0; i < count; ++i) {
	// 	group2.insert(keys[i], Player());
	// }

	// cout << "===== Initial HashTable =====" << endl;
	// print(group2);

	// group2.insert(keys[2], Player());

	// cout << "=====  HashTable Updated(" << keys[2] << ") =====" << endl;
	// print(group2);

	// group2.remove(keys[3]);

	// cout << "=====  HashTable Removed(" << keys[3] << ") =====" << endl;
	// print(group2);

	// cout << "Get Keys[4](" << keys[4] << "): " << group2.get(keys[4]) << endl;
}

void test2() {
	// Mark the entry as deleted
	constexpr int count = 5;

	vector<int> keys;
	for (int i = 0; i < count; ++i) {
		keys.push_back(rand() % 100);
	}

	HashTable2<int, int> group;
	for (int i = 0; i < count; ++i) {
		group.insert(keys[i], rand() % 100 + 1);
	}

	// cout << "===== Initial HashTable =====" << endl;
	// print(group);

	// group.insert(keys[2], 55);

	// cout << "=====  HashTable Updated(" << keys[2] << ") =====" << endl;
	// print(group);

	// group.remove(keys[keys.size() - 1]);

	// cout << "=====  HashTable Removed(" << keys[keys.size() - 1] << ") =====" << endl;
	// print(group);

	// cout << "Get Keys[" << keys.size() - 2 << "](" << keys[keys.size() - 2] << "): " << group.get(keys[keys.size() - 2]) << endl;

	HashTable2<int, Player> group2;
	for (int i = 0; i < count; ++i) {
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
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	std::srand(std::time(NULL));

	// test1();
	test2();


	return 0;
}
