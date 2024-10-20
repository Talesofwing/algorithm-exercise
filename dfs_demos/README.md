# DFS (深度優先搜索)

### Introduction

深度優先搜索算法(Depth First Search, DFS)是一種用於遍歷或搜尋樹或圖的全探索算法。需要注意，圖的深度越深，調用棧就會越大，因此會消耗更多的內存甚至溢出。

一般有兩種實現方法
1. Recrusive: 代碼簡潔直觀，但性能較差且可能會導致棧溢出
2. Stack: 代碼較為複雜，但比Recrusive算法使用的內存來得少，且少了呼叫函數的開銷

``` C++
// Recrusive implement
DFS(node):
    mark node as visited
    process node's value

    for each unvisited adjacent next_node
        DFS(next_node)

// Stack implement
DFS(start_node):
    create an empty stack
    push start_node onto the stack

    while stack is not empty:
        node = top element of stack
        pop top element

        if node is not visited:
            mark node as visited
            process node's value
            
            for each unvisited adjacent next_node
                push next_node onto the stack
```

### References
- [DFS Wiki](https://zh.wikipedia.org/zh-hant/%E6%B7%B1%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2)