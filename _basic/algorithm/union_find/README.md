# union-find

The Union-Find data structure, also know as Disjoint Set Union(DSU), is primarily used to manage a collection of [disjoint sets](https://en.wikipedia.org/wiki/Disjoint_sets) and efficiently supports two key operations:

- union: Merges two disjoint sets into one set
- find: Finds the representative element of the set containing a specific element, typically used to determine if two elements belong to the same set.

Union-Find typically uses an integer array to represent the sets, where each element's value points to its parent node. If an element is the root of the set, it points to itself.
For example, consider the following:

|Index|0|1|2|3|4|5|
|-|-|-|-|-|-|-|
|Parent Node|1|2|1|2|5|2|

Commonly used in several scenarios, including:
1. Graph Connectivity
2. Minimum Spanning Tree (MST)
3. Dynamic Connectivity Problem

To optimize Union-Find operations, two key techniques are typically used:
1. Path Compression: Applied during the find operation, this technique flattens the structure of the tree by making nodes point directly to the root, reducing the height of the tree and speeding up future operations.
2. Union by Rank: Used during the union operation, this method ensures that the tree with a lower rank (or smaller height) is attached under the root of the tree with a higher rank. This minimizes the growth of the tree's height, thus improving the efficiency of the structure over time.

```c++
Initialize(parent, size):
    for each node i:
        parent[i] = i
        size[i] = 1

Root(node):
    // Path Compression
    return node is root ? node : node = Root(node);

Same(node1, node2):
    return Root(node1) == Root(node2);

Union(node1, node2):
    root1 = Root(node1)
    root2 = Root(node2)
    if root1 != root2:
        // Union by Rank
        if size[root1] < size[root2]:
            swap(root1, root2)
        parent[root2] = root1
        size[root1] += size[root2]
```

### Examples
- [AtCoder](https://atcoder.jp/contests/atc001/tasks/unionfind_a)

The problem involves multiple nodes, where each node has a different parent node. The task is to find the root (the topmost parent) of a node and merge two groups of nodes (trees). Each time the `Find` operation is called, the node should be set to its root. When merging two groups, the merge should be done based on rank to minimize the height of the resulting tree.
