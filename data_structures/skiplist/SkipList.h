#include <vector>
#include <assert.h>
#include <iostream>
#include <limits>

template<typename T>
struct SkipList {
private:
	const unsigned int MAX_LEVEL = 32;
	const double P = 0.5;

private:
	struct SkipListNode {
	public:
		struct SkipListLevel {
		public:
			SkipListLevel() : forward(nullptr), span(0) {}
			SkipListLevel(SkipListNode* f, unsigned int s) : forward(f), span(s) {}

			~SkipListLevel() {
				// Don't delete forward, it's managed by SkipList

				// delete forward;
			}

		public:
			SkipListNode* forward;
			unsigned int span;
		};

	public:
		SkipListNode() : score(0), backward(nullptr), obj() {}
		SkipListNode(const T& o, double s) : score(s), backward(nullptr), obj(o) {}
		SkipListNode(T&& o, double s) : score(s), backward(nullptr), obj(std::move(o)) {}

		~SkipListNode() = default;

	public:
		void insert_level(SkipListNode* forward, unsigned int span) {
			levels.emplace_back(forward, span);
		}

	public:
		SkipListNode* backward;
		double score;
		T obj;

		std::vector<SkipListLevel> levels;
	};

public:
	SkipList() : header(new SkipListNode()), tail(nullptr), length(0), level(0) {
		header->score = -std::numeric_limits<double>::infinity();
		for (int i = 0; i < MAX_LEVEL; ++i) {
			header->levels.emplace_back(nullptr, 0);
		}
	}

	~SkipList() {
		delete header;
		delete tail;
	}

public:
	void insert(const T& obj, double score) {
		std::cout << "Insert: " << obj << ", " << score << std::endl;

		std::vector<SkipListNode*> nodes(MAX_LEVEL);
		std::vector<int> spans(MAX_LEVEL, 0);
		SkipListNode* cur_node = header;

		// Step 1 : Find the insertion positions at each level and calculate the spans at each level
		for (int i = level - 1; i >= 0; i--) {
			spans[i] = (i == level - 1) ? 0 : spans[i + 1];
			while (cur_node->levels[i].forward != nullptr &&
				   (cur_node->levels[i].forward->score < score ||
					(cur_node->levels[i].forward->score == score && cur_node->levels[i].forward->obj < obj))) {

				spans[i] += cur_node->levels[i].span;
				cur_node = cur_node->levels[i].forward;
			}
			nodes[i] = cur_node;
		}

		// Step 2 : Calculate the new level
		int new_level = 1;
		while (new_level < MAX_LEVEL && (double)rand() / RAND_MAX < P) {
			new_level++;
		}

		// Step 3 : Update the links and spans
		if (new_level > level) {
			for (int i = level; i < new_level; i++) {
				spans[i] = 0;
				nodes[i] = header;
				nodes[i]->levels[i].span = length;
			}
			level = new_level;
		}

		// Step 4 : Insert the new node
		SkipListNode* new_node = new SkipListNode(obj, score);
		new_node->levels.resize(new_level);
		for (int i = 0; i < new_level; i++) {
			new_node->levels[i].forward = nodes[i]->levels[i].forward;
			nodes[i]->levels[i].forward = new_node;

			new_node->levels[i].span = nodes[i]->levels[i].span - (spans[0] - spans[i]);
			nodes[i]->levels[i].span = (spans[0] - spans[i]) + 1;
		}

		for (int i = new_level; i < level; ++i) {
			++nodes[i]->levels[i].span;
		}

		// Step 5 : Update the links
		new_node->backward = (nodes[0] == header) ? nullptr : nodes[0];
		if (new_node->levels[0].forward != nullptr) {
			new_node->levels[0].forward->backward = new_node;
		} else {
			tail = new_node;
		}

		length++;
	}

	T remove(int index) {
		assert(index >= 0 && index < length && "Index out of range");

		// Step 1 : Find the insertion positions at each level
		std::vector<SkipListNode*> nodes(level + 1);
		SkipListNode* node = header;
		int traveled_span = 0;
		for (int i = level; i >= 0; --i) {
			// Find the preceding node of the node to be removed
			while (node->levels[i].forward != nullptr && (traveled_span + node->levels[i].span) < index) {
				traveled_span += node->levels[i].span;
				node = node->levels[i].forward;
			}
			nodes[i] = node;
		}

		SkipListNode* node_to_delete = nodes[0]->levels[0].forward;

		// Step 2 : Updates links and spans, then delete the node
		for (int i = 0; i <= level; ++i) {
			if (nodes[i]->levels[i].forward == node_to_delete) {
				nodes[i]->levels[i].forward = node_to_delete->levels[i].forward;
				nodes[i]->levels[i].span += node_to_delete->levels[i].span - 1;
			}
		}

		if (node_to_delete->levels[0].forward != nullptr) {
			node_to_delete->levels[0].forward->backward = node_to_delete->backward;
		} else {
			tail = node_to_delete->backward;
		}

		while (level > 0 && header->levels[level].forward == nullptr) {
			--level;
		}

		T obj = node_to_delete->obj;
		delete node_to_delete;
		--length;
		return obj;
	}

	T& at(int index) {
		SkipListNode* node = find_by_index(index);
		return node->obj;
	}

	const T& at(int index) const {
		SkipListNode* node = find_by_index(index);
		return node->obj;
	}

	void display() {
		std::cout << "Length: " << length << ", Level: " << level << std::endl;
		SkipListNode* node = header;
		int index = 1;
		while (node->levels[0].forward != nullptr) {
			node = node->levels[0].forward;
			std::cout << "\tNode(" << (index++) << ") Obj: " << node->obj << ", Score: " << node->score << ", Level: " << node->levels.size() << ", Spans: ";
			for (int i = 0; i < node->levels.size(); ++i) {
				std::cout << node->levels[i].span << "\n,"[i < node->levels.size() - 1];
			}
		}

		std::cout << "\nHeads: " << std::endl;
		for (int i = 0; i < level; ++i) {
			std::cout << "\tLevel: " << (i + 1) << ", Node(" << header->levels[i].span << ") Obj: " << header->levels[i].forward->obj << ", Score: " << header->levels[i].forward->score << std::endl;
		}

		std::cout << "Tail: " << "\n\tNode(" << length << ") Obj: " << tail->obj << ", Score : " << tail->score << std::endl;
	}

	void display_revser() {

	}

private:
	// Find the node with the given index; O(n)
	SkipListNode* find_by_index(int index) {
		assert(index >= 0 && index < length && "Index out of range");

		SkipListNode* node = header->levels[0].forward;
		for (int i = 0; i < index; ++i) {
			node = node->levels[0].forward;
		}

		return node;
	}

	// Find the node with the given object; O(n)
	SkipListNode* find(const T& obj) {
		SkipListNode* node = header->levels[0].forward;
		while (node != nullptr) {
			if (node->obj == obj) {
				return node;
			}

			node = node->levels[0].forward;
		}

		return nullptr;
	}

	// Find the node with the given score; O(log n)
	SkipListNode* find(const T& obj, double score) {
		SkipListNode* node = header;
		for (int i = level; i >= 0; --i) {
			while (node->levels[i].forward != nullptr && node->levels[i].forward->score < score) {
				node = node->levels[i].forward;
			}
		}

		node = node->levels[0].forward;
		while (node != nullptr && node->score == score) {
			if (node->obj == obj) return node;
			node = node->levels[0].forward;
		}

		return nullptr;
	}

public:
	SkipListNode* header;
	SkipListNode* tail;

	unsigned long length;
	unsigned int level;			// 1 ~ 32
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const SkipList<T>& list) {
	os << "Length: " << list.length << ", Level: " << list.level << std::endl;
	return os;
}
