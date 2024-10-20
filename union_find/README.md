# union-find

### Introduction
主要用於管理一系列不相交的集合，並能高效地實現兩個主要操作

- union(合併): 將兩個不相交的集合合併為一個集合
- find(查找): 用於查找某個元素所在集合的代表元素，通常用於判定兩個元素是否屬於同一個集合

union-find通常使用一個整數數組來表示，其中每個元素的值指向其父節點，如果元素是集合的根節點，則指向其自身。例如有

|索引|0|1|2|3|4|5|
|-|-|-|-|-|-|-|
|父節點|1|2|1|2|5|2|

一般可用於
1. 圖的連通性
2. 最小生成樹
3. 動態連通性問題

在實現時一般會使用兩種方式進行優化
1. 路徑壓縮(Path Compression): 在Find操作中實現，有效減少樹的高度，加快未來操作的速度。
2. 按秩合併(Union by Rank)：用於在Union操作中將較小的樹連接到較大的樹上，進一步減少樹的高度。

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

題目中有多個節點，每個節點的父節點都不同。需求是找到節點的最上根節點，以及能合併兩個組節點(樹)。每一次的Find都會將其設置成最上根節點，且合併時會按照秩(rank)進行合併，使樹的高度最小化。