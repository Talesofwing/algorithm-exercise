#include <vector>
#include <assert.h>
#include <iostream>
#include <limits>

template<typename T>
struct SkipList {
private:
	const unsigned int MAX_LEVEL = 32;
	const double P = 0.5;

public:
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
		};	// SkipListLevel

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
	};	// SkipListNode

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
				nodes[i]->levels[i].span = 0;
			}
			level = new_level;
		}

		// Step 4 : Insert the new node
		SkipListNode* new_node = new SkipListNode(obj, score);
		new_node->levels.resize(new_level);
		for (int i = 0; i < new_level; i++) {
			new_node->levels[i].forward = nodes[i]->levels[i].forward;
			nodes[i]->levels[i].forward = new_node;

			if (nodes[i]->levels[i].span == 0) {
				new_node->levels[i].span = 0;
			} else {
				new_node->levels[i].span = nodes[i]->levels[i].span - (spans[0] - spans[i]);
			}
			nodes[i]->levels[i].span = (spans[0] - spans[i]) + 1;
		}

		// Step 5 : Update the span of the previous node at each level
		for (int i = new_level; i < level; ++i) {
			if (nodes[i]->levels[i].forward != nullptr) {
				++nodes[i]->levels[i].span;
			}
		}

		// Step 6 : Update the links
		new_node->backward = (nodes[0] == header) ? nullptr : nodes[0];
		if (new_node->levels[0].forward != nullptr) {
			new_node->levels[0].forward->backward = new_node;
		} else {
			tail = new_node;
		}

		++length;
	}

	void remove_by_index(int index) {
		assert(index >= 0 && index < length && "Index out of range");

		std::vector<SkipListNode*> nodes(MAX_LEVEL);
		// std::vector<int> spans(MAX_LEVEL, 0);
		SkipListNode* node_to_remove = header;

		// Step 1 : Find the insertion positions at each level and calculate the spans at each level
		int span = 0;
		for (int i = level - 1; i >= 0; i--) {
			// spans[i] = (i == level - 1) ? 0 : spans[i + 1];
			while (node_to_remove->levels[i].forward != nullptr && span + node_to_remove->levels[i].span <= index) {
				span += node_to_remove->levels[i].span;
				// spans[i] += node_to_delete->levels[i].span;
				node_to_remove = node_to_remove->levels[i].forward;
			}
			nodes[i] = node_to_remove;
		}
		node_to_remove = nodes[0]->levels[0].forward;

		// Step 2 : Update the links (forward)
		for (int i = 0; i < node_to_remove->levels.size(); i++) {
			if (node_to_remove->levels[i].forward != nullptr) {
				nodes[i]->levels[i].forward = node_to_remove->levels[i].forward;
				nodes[i]->levels[i].span += node_to_remove->levels[i].span - 1;
			} else {
				nodes[i]->levels[i].forward = nullptr;
				nodes[i]->levels[i].span = 0;
			}
		}

		// Step 3 : Update the level
		while (level > 0 && header->levels[level - 1].forward == nullptr) {
			--level;
		}

		// Step 4 : Update the tail & backward
		if (node_to_remove->levels[0].forward == nullptr) {
			tail = node_to_remove->backward;
		} else {
			node_to_remove->levels[0].forward->backward = node_to_remove->backward;
		}

		// Step 5 : Update the length
		--length;

		delete node_to_remove;
	}

	void clear() {
		SkipListNode* node = header->levels[0].forward;
		while (node != nullptr) {
			SkipListNode* forward = node->levels[0].forward;
			delete node;
			node = forward;
		}

		for (int i = 0; i < MAX_LEVEL; ++i) {
			header->levels[i].forward = nullptr;
			header->levels[i].span = 0;
		}

		length = 0;
		level = 0;
		tail = nullptr;
	}

	// Find the node with the given index; O(log n)
	SkipListNode* find_by_index(int index) {
		assert(index >= 0 && index < length && "Index out of range");

		SkipListNode* node = header;
		int span = 0;
		for (int i = level - 1; i >= 0; --i) {
			while (node->levels[i].forward != nullptr && span + node->levels[i].span <= index) {
				span += node->levels[i].span;
				node = node->levels[i].forward;
			}
		}

		return node->levels[0].forward;
	}

	// Find the node with the given object; O(n)
	SkipListNode* find_by_obj(const T& obj) {
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
	SkipListNode* find_by_score(const T& obj, double score) {
		SkipListNode* node = header;
		for (int i = level - 1; i >= 0; --i) {
			while (node->levels[i].forward != nullptr && node->levels[i].forward->score < score) {
				node = node->levels[i].forward;
			}
		}

		node = node->levels[0].forward;
		while (node != nullptr && node->score == score) {
			if (node->obj == obj) return node;
			std::cout << "1" << std::endl;
			node = node->levels[0].forward;
		}

		return nullptr;
	}

	void display() {
		std::cout << "Length: " << length << ", Level: " << level << std::endl;
		if (length <= 0) {
			return;
		}

		SkipListNode* node = header;
		int index = 1;
		while (node->levels[0].forward != nullptr) {
			node = node->levels[0].forward;
			std::cout << "\tNode(" << (index++) << ") Obj: " << node->obj << ", Score: " << node->score << ", Level: " << node->levels.size() << ", Address: " << node << ", Backward: " << node->backward << ", Foreward: " << node->levels[0].forward << ", Spans: ";
			for (int i = 0; i < node->levels.size(); ++i) {
				std::cout << node->levels[i].span << "\n,"[i < node->levels.size() - 1];
			}
		}

		std::cout << "Heads: " << std::endl;
		for (int i = 0; i < level; ++i) {
			std::cout << "\tLevel: " << (i + 1) << ", Span: " << header->levels[i].span << ", Node(" << header->levels[i].span << ") Obj: " << header->levels[i].forward->obj << ", Score: " << header->levels[i].forward->score << std::endl;
		}

		std::cout << "Tail: " << "\n\tNode(" << length << ") Obj: " << tail->obj << ", Score : " << tail->score << std::endl;
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
