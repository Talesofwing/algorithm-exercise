#include <vector>
#include <stdexcept>
#include <limits>
#include <algorithm>

enum class SegmentTreeMode {
	Sum,
	Max,
	Min,
};

// Base on vector implementation of segment tree, but with lazy propagation for range updates and queries
template<typename T>
class SegmentTree {
private:
	struct Node {
		int L, R;
		T Value;
		int LChild, RChild;

		T LazyIncrementValue;
		bool HasLazyAssign;
		T LazyAssignValue;

		Node(int l, int r) : L(l), R(r), Value(T()), LChild(-1), RChild(-1), LazyIncrementValue(T()), HasLazyAssign(false), LazyAssignValue(T()) {}
	};

public:
	SegmentTree(int l, int r, SegmentTreeMode mode) : _mode(mode) {
		if (l > r) {
			throw std::invalid_argument("Invalid range: l should be less than or equal to r");
		}

		if (static_cast<long long>(r) - l >= std::numeric_limits<int>::max()) {
			throw std::invalid_argument("Range is too large: r - l should be less than INT_MAX");
		}

		_lo = l;
		_hi = r;
		_nodes.emplace_back(l, r);
	}
	SegmentTree(const SegmentTree&) = delete; // Disable copy constructor

	~SegmentTree() {}

public:
	SegmentTree& operator=(const SegmentTree&) = delete; // Disable copy assignment

public:
	void Assign(int index, T val) {
		AssignRange(index, index, val);
	}

	void AssignRange(int l, int r, T val) {
		CheckRange(l, r);

		Assign_Internal(0, l, r, val);
	}

	void Increment(int index, T increment) {
		IncrementRange(index, index, increment);
	}

	void IncrementRange(int l, int r, T increment) {
		CheckRange(l, r);

		Increment_Internal(0, l, r, increment);
	}

	T QueryRange(int l, int r) {
		CheckRange(l, r);

		return Query_Internal(0, l, r);
	}

private:
	void Assign_Internal(int nodeIndex, int l, int r, T val) {
		if (_nodes[nodeIndex].R < l || _nodes[nodeIndex].L > r) {
			return;
		}

		if (l <= _nodes[nodeIndex].L && _nodes[nodeIndex].R <= r) {
			_nodes[nodeIndex].HasLazyAssign = true;
			_nodes[nodeIndex].LazyAssignValue = val;
			_nodes[nodeIndex].LazyIncrementValue = T();
			_nodes[nodeIndex].Value = ComputeAssignValue(_nodes[nodeIndex].L, _nodes[nodeIndex].R, val);
			return;
		}

		CreateChildrenIfNeeded(nodeIndex);
		PushDown(nodeIndex);

		Assign_Internal(_nodes[nodeIndex].LChild, l, r, val);
		Assign_Internal(_nodes[nodeIndex].RChild, l, r, val);

		_nodes[nodeIndex].Value = Merge(_nodes[_nodes[nodeIndex].LChild].Value, _nodes[_nodes[nodeIndex].RChild].Value);
	}

	void Increment_Internal(int nodeIndex, int l, int r, T increment) {
		if (_nodes[nodeIndex].R < l || _nodes[nodeIndex].L > r) {
			return;
		}

		if (l <= _nodes[nodeIndex].L && _nodes[nodeIndex].R <= r) {
			if (_nodes[nodeIndex].HasLazyAssign) {
				_nodes[nodeIndex].LazyAssignValue += increment;
				_nodes[nodeIndex].Value = ComputeAssignValue(_nodes[nodeIndex].L, _nodes[nodeIndex].R, _nodes[nodeIndex].LazyAssignValue);
			} else {
				_nodes[nodeIndex].LazyIncrementValue += increment;
				_nodes[nodeIndex].Value = ComputeIncrementedValue(_nodes[nodeIndex], increment);
			}
			return;
		}

		CreateChildrenIfNeeded(nodeIndex);
		PushDown(nodeIndex);

		Increment_Internal(_nodes[nodeIndex].LChild, l, r, increment);
		Increment_Internal(_nodes[nodeIndex].RChild, l, r, increment);

		_nodes[nodeIndex].Value = Merge(_nodes[_nodes[nodeIndex].LChild].Value, _nodes[_nodes[nodeIndex].RChild].Value);
	}

	T Query_Internal(int nodeIndex, int l, int r) {
		if (_nodes[nodeIndex].R < l || _nodes[nodeIndex].L > r) {
			return Identity();
		}

		if (l <= _nodes[nodeIndex].L && _nodes[nodeIndex].R <= r) {
			return _nodes[nodeIndex].Value;
		}

		if (_nodes[nodeIndex].LChild == -1) {
			const Node& node = _nodes[nodeIndex];
			int lo = std::max(l, node.L);
			int hi = std::min(r, node.R);
			if (_mode == SegmentTreeMode::Sum) {
				T each = node.Value / static_cast<T>(node.R - node.L + 1);
				return each * static_cast<T>(hi - lo + 1);
			}
			return node.Value;
		}

		PushDown(nodeIndex);

		T leftValue = Query_Internal(_nodes[nodeIndex].LChild, l, r);
		T rightValue = Query_Internal(_nodes[nodeIndex].RChild, l, r);

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
			T val = _nodes[nodeIndex].LazyAssignValue;
			PushDown_Assign(leftChild, val);
			PushDown_Assign(rightChild, val);
			_nodes[nodeIndex].HasLazyAssign = false;
			_nodes[nodeIndex].LazyAssignValue = T();
		}

		if (_nodes[nodeIndex].LazyIncrementValue != T()) {
			T increment = _nodes[nodeIndex].LazyIncrementValue;
			PushDown_Increment(leftChild, increment);
			PushDown_Increment(rightChild, increment);
			_nodes[nodeIndex].LazyIncrementValue = T();
		}
	}

	// Push down the assign value to the child node
	void PushDown_Assign(int childIndex, T val) {
		_nodes[childIndex].HasLazyAssign = true;
		_nodes[childIndex].LazyAssignValue = val;
		_nodes[childIndex].LazyIncrementValue = T();
		_nodes[childIndex].Value = ComputeAssignValue(_nodes[childIndex].L, _nodes[childIndex].R, val);
	}

	// Push down the increment value to the child node
	void PushDown_Increment(int childIndex, T increment) {
		if (_nodes[childIndex].HasLazyAssign) {
			_nodes[childIndex].LazyAssignValue += increment;
			_nodes[childIndex].Value = ComputeAssignValue(_nodes[childIndex].L, _nodes[childIndex].R, _nodes[childIndex].LazyAssignValue);
		} else {
			_nodes[childIndex].LazyIncrementValue += increment;
			_nodes[childIndex].Value = ComputeIncrementedValue(_nodes[childIndex], increment);
		}
	}

	// Compute the value of a range based on the mode and the range it covers
	T ComputeAssignValue(int l, int r, T val) const {
		switch (_mode) {
			case SegmentTreeMode::Sum:
				return static_cast<T>(r - l + 1) * val;
			default:
				return val;
		}
	}

	// Compute the value of a node based on the mode and the range it covers
	T ComputeIncrementedValue(const Node& node, T val) const {
		switch (_mode) {
			case SegmentTreeMode::Sum:
				return node.Value + static_cast<T>(node.R - node.L + 1) * val;
			default:
				return node.Value + val;
		}
	}

	// Merge two values based on the mode
	T Merge(T leftValue, T rightValue) const {
		switch (_mode) {
			case SegmentTreeMode::Sum:
				return leftValue + rightValue;
			case SegmentTreeMode::Max:
				return std::max(leftValue, rightValue);
			case SegmentTreeMode::Min:
				return std::min(leftValue, rightValue);
			default:
				throw std::logic_error("Invalid mode");
		}
	}

	T Identity() const {
		switch (_mode) {
			case SegmentTreeMode::Sum:
				return T();
			case SegmentTreeMode::Max:
				return std::numeric_limits<T>::lowest();
			case SegmentTreeMode::Min:
				return std::numeric_limits<T>::max();
			default:
				throw std::logic_error("Invalid mode");
		}
	}

	void CheckRange(int l, int r) const {
		if (l > r) {
			throw std::invalid_argument("Invalid range: l should be less than or equal to r");
		}

		if (l < _lo || r > _hi) {
			throw std::out_of_range("Range is out of bounds");
		}
	}

private:
	std::vector<Node> _nodes;
	SegmentTreeMode _mode;
	int _lo, _hi;
};
