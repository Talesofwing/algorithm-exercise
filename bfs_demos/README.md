# BFS(廣度優先搜索)

### Introduction
廣度優先搜索(Breadth First Search, BFS)是一種用於遍歷或搜索圖和樹的算法。與DFS不同，BFS通過探索圖的所有鄰接頂點來進行搜索，然後再向外擴展到下一層的鄰接頂點。

BFS通常使用隊列來存儲待訪問的頂點。從起始頂點開始，入隊，在循環中出隊並標記，並將其所有未被標記的邻接頂點入隊。

需要注意，圖的廣度愈大，隊列中存儲的待訪問節點就會愈多，因此會消耗更多的內存甚至溢出。

``` cpp
BFS(start_node):
    create a queue
    enqueue start_node
    mark start_node as visited

    while queue is not empty:
        node = front element of queue
        dequeue

        process node's value

        for each unvisited adjacent next_node:
            enqueue next_node
            mark next_node as visited

```