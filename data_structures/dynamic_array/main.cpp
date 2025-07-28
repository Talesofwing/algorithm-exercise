#include <iostream>
#include <vector>
#include <ctime>

#include "DynamicArray.h"

using namespace std;

class Player {
public:
	Player()
		: Hp(rand() % 100 + 1) {
		std::cout << "[Player] Constructor with Random(" << Hp << ")" << std::endl;
	}

	Player(int hp)
		: Hp(hp) {
		std::cout << "[Player] Constructor with Parameter(" << Hp << ")" << std::endl;
	}

	Player(const Player& other)
		: Hp(other.Hp) {
		std::cout << "[Player] Copy Constructor(" << Hp << ")" << std::endl;
	}

	Player(Player&& other) noexcept
		: Hp(other.Hp) {
		std::cout << "[Player] Move Constructor(" << Hp << ")" << std::endl;

		other.Hp = 0;
	}

	~Player() {
		std::cout << "[Player] Destructor()" << std::endl;
	}

public:
	int Hp;
};

ostream& operator<<(ostream& os, const Player& player) {
	return os << player.Hp;
}

template<typename T>
void Print(string name, const DynamicArray<T>& arr) {
	cout << "[Print] Name: " << name << ", Array Size: " << arr.Size() << ", Array Capacity: " << arr.Capacity() << endl;
	for (int i = 0; i < arr.Size(); i++) {
		if (i == 0) {
			cout << "\t";
		}
		cout << arr[i] << " ";
		if (i == arr.Size() - 1) {
			cout << endl;
		}
	}
}

void Print(string name, const DynamicArray<Player>& arr) {
	cout << "[Print] Name: " << name << ", Array Size: " << arr.Size() << ", Array Capacity: " << arr.Capacity() << endl;
	for (int i = 0; i < arr.Size(); i++) {
		if (i == 0) {
			cout << "\t";
		}
		cout << arr[i].Hp << " ";
		if (i == arr.Size() - 1) {
			cout << endl;
		}
	}
}

void Test_ConstructorAndDescructor() {
	DynamicArray<int> a = DynamicArray<int>();
	DynamicArray<int> a2 = DynamicArray<int>(2);
	DynamicArray<int> a3 = DynamicArray<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

	Print("a", a);
	Print("a2", a2);
	Print("a3", a3);

	DynamicArray<int> a4 = a3;
	DynamicArray<int> a5 = std::move(a3);

	Print("a3", a3);
	Print("a4", a4);
	Print("a5", a5);
}

void Test_ConstructorAndDescructor2() {
	DynamicArray<Player> a = DynamicArray<Player>();
	DynamicArray<Player> a2 = DynamicArray<Player>(2);
	DynamicArray<Player> a3 = DynamicArray<Player>({Player(), Player(), Player(), Player(), Player(), Player(), Player(), Player(), Player(), Player()});

	Print("a", a);
	Print("a2", a2);
	Print("a3", a3);

	DynamicArray<Player> a4 = a3;
	DynamicArray<Player> a5 = std::move(a3);

	Print("a3", a3);
	Print("a4", a4);
	Print("a5", a5);
}

void Test_Operators() {
	DynamicArray<int> a = DynamicArray<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

	Print("a", a);

	DynamicArray<int> a2;
	a2 = a;

	DynamicArray<int> a3;
	a3 = std::move(a);

	Print("a", a);
	Print("a2", a2);
	Print("a3", a3);
}

void Test_Operators2() {
	DynamicArray<Player> a = DynamicArray<Player>({Player(), Player(), Player(), Player(), Player(), Player(), Player(), Player(), Player(), Player()});

	Print("a", a);

	DynamicArray<Player> a2;
	a2 = a;

	DynamicArray<Player> a3;
	a3 = std::move(a);

	Print("a", a);
	Print("a2", a2);
	Print("a3", a3);

	a3[1].Hp = 100000;

	std::cout << a3[1] << std::endl;

	const int hp = a3[1].Hp;
	std::cout << hp << std::endl;
}

void Test_Methods() {
	DynamicArray<int> a = DynamicArray<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

	Print("a", a);

	a.Reserve(100);

	Print("a", a);

	a.Resize(5);

	Print("a", a);

	// std::cout << "a[-1]: " << a.At(-1) << std::endl;	// error
	std::cout << "a[2]: " << a.At(2) << std::endl;
	std::cout << "a.Front(): " << a.Front() << std::endl;
	std::cout << "a.Back(): " << a.Back() << std::endl;

	a.Clear();

	Print("a", a);

	a.shrink_to_fit();

	Print("a", a);

	a.Insert(5);

	Print("a", a);

	a.Insert(1, 8);
	a.Insert(1, 81);
	a.Insert(1, 85);
	a.Insert(1, 23);
	a.Insert(1, 84);

	Print("a", a);

	a.Remove();
	a.Remove(1);
	a.Remove(1, 2);

	Print("a", a);

	a.Emplace(4);
	a.EmplaceAt(1, 100);

	Print("a", a);
}

void Test_Methods2() {
	DynamicArray<Player> a = DynamicArray<Player>({Player(), Player(), Player(), Player(), Player(), Player(), Player(), Player(), Player(), Player()});

	Print("a", a);

	a.Reserve(100);

	Print("a", a);

	a.Resize(5);

	Print("a", a);

	// std::cout << "a[-1]: " << a.At(-1) << std::endl;	// error
	std::cout << "a[2]: " << a.At(2) << std::endl;
	std::cout << "a.Front(): " << a.Front() << std::endl;
	std::cout << "a.Back(): " << a.Back() << std::endl;

	a.Clear();

	Print("a", a);

	a.shrink_to_fit();

	Print("a", a);

	a.Insert(Player());

	Print("a", a);

	a.Insert(1, Player());
	a.Insert(1, Player());
	a.Insert(1, Player());
	a.Insert(1, Player());
	a.Insert(1, Player());

	Print("a", a);

	a.Remove();
	a.Remove(1);
	a.Remove(1, 2);

	Print("a", a);

	// a.Emplace(Player());	// Extra constructor
	a.Emplace(10);
	a.EmplaceAt(1, 200);

	Print("a", a);
}

void Test_Iterator() {
	DynamicArray<int> a = DynamicArray<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

	for (auto& it : a) {
		cout << it << " ";
	}
	cout << endl;
}

void Test_Iterator2() {
	DynamicArray<Player> a = DynamicArray<Player>({Player(), Player(), Player(), Player(), Player(), Player(), Player(), Player(), Player(), Player()});

	for (auto& it : a) {
		cout << it << " ";
	}
	cout << endl;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	std::srand(std::time(NULL));

	// Test_ConstructorAndDescructor();
	// Test_ConstructorAndDescructor2();
	// Test_Operators();
	// Test_Operators2();

	// Test_Methods();
	// Test_Methods2();

	// Test_Iterator();
	Test_Iterator2();

	return 0;
}
