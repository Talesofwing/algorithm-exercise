#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>

// Base on vector implementation of segment tree, but with lazy propagation for range updates and queries
class SegmentTree {
private:
	struct Node {
		int L, R;
		int Value;
		int LChild, RChild;

		int LazyIncrementValue;
		bool HasLazyAssign;
		int LazyAssignValue;

		Node(int l, int r) : L(l), R(r), Value(0), LChild(-1), RChild(-1), LazyIncrementValue(0), HasLazyAssign(false), LazyAssignValue(0) {}
	};

public:
	enum class Mode {
		Sum,
		Max,
		Min,
	};

public:
	SegmentTree(int l, int r, Mode mode) : _mode(mode) {
		if (l > r) {
			throw std::invalid_argument("Invalid range: l should be less than or equal to r");
		}

		_nodes.emplace_back(l, r);
	}
	SegmentTree(const SegmentTree&) = delete; // Disable copy constructor

	~SegmentTree() {}

public:
	SegmentTree& operator=(const SegmentTree&) = delete; // Disable copy assignment

public:
	void Assign(int index, int val) {
		AssignRange(index, index, val);
	}

	void AssignRange(int l, int r, int val) {
		Assign_Internal(0, l, r, val);
	}

	void Increment(int index, int increment) {
		IncrementRange(index, index, increment);
	}

	void IncrementRange(int l, int r, int increment) {
		Increment_Internal(0, l, r, increment);
	}

	int QueryRange(int l, int r) {
		return Query_Internal(0, l, r);
	}

private:
	void Assign_Internal(int nodeIndex, int l, int r, int val) {
		if (nodeIndex == -1) {
			return;
		}

		if (_nodes[nodeIndex].R < l || _nodes[nodeIndex].L > r) {
			return;
		}

		if (l <= _nodes[nodeIndex].L && _nodes[nodeIndex].R <= r) {
			_nodes[nodeIndex].HasLazyAssign = true;
			_nodes[nodeIndex].LazyAssignValue = val;
			_nodes[nodeIndex].LazyIncrementValue = 0;
			_nodes[nodeIndex].Value = ComputeRangeValue(_nodes[nodeIndex].L, _nodes[nodeIndex].R, val);
			return;
		}

		CreateChildrenIfNeeded(nodeIndex);
		PushDown(nodeIndex);

		Assign_Internal(_nodes[nodeIndex].LChild, l, r, val);
		Assign_Internal(_nodes[nodeIndex].RChild, l, r, val);

		_nodes[nodeIndex].Value = Merge(_nodes[_nodes[nodeIndex].LChild].Value, _nodes[_nodes[nodeIndex].RChild].Value);
	}

	void Increment_Internal(int nodeIndex, int l, int r, int increment) {
		if (nodeIndex == -1) {
			return;
		}

		if (_nodes[nodeIndex].R < l || _nodes[nodeIndex].L > r) {
			return;
		}

		if (l <= _nodes[nodeIndex].L && _nodes[nodeIndex].R <= r) {
			if (_nodes[nodeIndex].HasLazyAssign) {
				_nodes[nodeIndex].LazyAssignValue += increment;
				_nodes[nodeIndex].Value = ComputeRangeValue(_nodes[nodeIndex].L, _nodes[nodeIndex].R, _nodes[nodeIndex].LazyAssignValue);
			} else {
				_nodes[nodeIndex].LazyIncrementValue += increment;
				_nodes[nodeIndex].Value = ComputeRangeValue(_nodes[nodeIndex], increment);
			}
			return;
		}

		CreateChildrenIfNeeded(nodeIndex);
		PushDown(nodeIndex);

		Increment_Internal(_nodes[nodeIndex].LChild, l, r, increment);
		Increment_Internal(_nodes[nodeIndex].RChild, l, r, increment);

		_nodes[nodeIndex].Value = Merge(_nodes[_nodes[nodeIndex].LChild].Value, _nodes[_nodes[nodeIndex].RChild].Value);
	}

	int Query_Internal(int nodeIndex, int l, int r) {
		if (nodeIndex == -1) {
			return Identity();
		}

		if (_nodes[nodeIndex].R < l || _nodes[nodeIndex].L > r) {
			return Identity();
		}

		if (l <= _nodes[nodeIndex].L && _nodes[nodeIndex].R <= r) {
			return _nodes[nodeIndex].Value;
		}

		CreateChildrenIfNeeded(nodeIndex);
		PushDown(nodeIndex);

		int leftValue = Query_Internal(_nodes[nodeIndex].LChild, l, r);
		int rightValue = Query_Internal(_nodes[nodeIndex].RChild, l, r);

		return Merge(leftValue, rightValue);
	}

	// Common
	// ====================================================================================================

	// Create child nodes if they do not exist
	void CreateChildrenIfNeeded(int nodeIndex) {
		if (_nodes[nodeIndex].LChild != -1)
			return;

		int l = _nodes[nodeIndex].L;
		int r = _nodes[nodeIndex].R;

		if (l == r)
			return;

		int mid = l + (r - l) / 2;

		int leftIndex = static_cast<int>(_nodes.size());
		_nodes.emplace_back(l, mid);

		int rightIndex = static_cast<int>(_nodes.size());
		_nodes.emplace_back(mid + 1, r);

		_nodes[nodeIndex].LChild = leftIndex;
		_nodes[nodeIndex].RChild = rightIndex;
	}

	// Push down the lazy values to the child nodes
	void PushDown(int nodeIndex) {
		int leftChild = _nodes[nodeIndex].LChild;
		int rightChild = _nodes[nodeIndex].RChild;

		if (_nodes[nodeIndex].HasLazyAssign) {
			int val = _nodes[nodeIndex].LazyAssignValue;
			PushDown_Assign(leftChild, val);
			PushDown_Assign(rightChild, val);
			_nodes[nodeIndex].HasLazyAssign = false;
			_nodes[nodeIndex].LazyAssignValue = 0;
		}

		if (_nodes[nodeIndex].LazyIncrementValue != 0) {
			int increment = _nodes[nodeIndex].LazyIncrementValue;
			PushDown_Increment(leftChild, increment);
			PushDown_Increment(rightChild, increment);
			_nodes[nodeIndex].LazyIncrementValue = 0;
		}
	}

	// Push down the assign value to the child node
	void PushDown_Assign(int childIndex, int val) {
		_nodes[childIndex].HasLazyAssign = true;
		_nodes[childIndex].LazyAssignValue = val;
		_nodes[childIndex].LazyIncrementValue = 0;
		_nodes[childIndex].Value = ComputeRangeValue(_nodes[childIndex].L, _nodes[childIndex].R, val);
	}

	// Push down the increment value to the child node
	void PushDown_Increment(int childIndex, int increment) {
		if (_nodes[childIndex].HasLazyAssign) {
			_nodes[childIndex].LazyAssignValue += increment;
			_nodes[childIndex].Value = ComputeRangeValue(_nodes[childIndex].L, _nodes[childIndex].R, _nodes[childIndex].LazyAssignValue);
		} else {
			_nodes[childIndex].LazyIncrementValue += increment;
			_nodes[childIndex].Value = ComputeRangeValue(_nodes[childIndex], increment);
		}
	}

	// Compute the value of a range based on the mode and the range it covers
	int ComputeRangeValue(int l, int r, int val) const {
		switch (_mode) {
			case Mode::Sum:
				return (r - l + 1) * val;
			default:
				return val;
		}
	}

	// Compute the value of a node based on the mode and the range it covers
	int ComputeRangeValue(const Node& node, int val) const {
		switch (_mode) {
			case Mode::Sum:
				return node.Value + (node.R - node.L + 1) * val;
			default:
				return node.Value + val;
		}
	}

	// Merge two values based on the mode
	int Merge(int leftValue, int rightValue) const {
		switch (_mode) {
			case Mode::Sum:
				return leftValue + rightValue;
			case Mode::Max:
				return std::max(leftValue, rightValue);
			case Mode::Min:
				return std::min(leftValue, rightValue);
			default:
				return Identity(); // Should not reach here
		}
	}

	int Identity() const {
		switch (_mode) {
			case Mode::Sum:
				return 0;

			case Mode::Max:
				return std::numeric_limits<int>::lowest();

			case Mode::Min:
				return std::numeric_limits<int>::max();

			default:
				throw std::logic_error("Invalid mode");
		}
	}

private:
	std::vector<Node> _nodes;
	Mode _mode;
};
