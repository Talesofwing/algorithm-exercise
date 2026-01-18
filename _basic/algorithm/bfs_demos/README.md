# Breadth First Search(BFS)

Breadth First Search(BFS) is an algorithm used for traversing or searching graphs and trees. Unlike DFS, BFS explores all adjacent vertices of a graph before expanding to the next level of adjacent vertices.

BFS typically uses a `Queue` to store vertices waiting to be visited. Starting from the initial vertex, it enqueues it, then in a loop dequeues and marks vertices as visited, enqueueing all unmarked adjacent vertices.

Note that as the graph's breadth increases, more nodes waiting to be visited will be stored in the queue, thus consuming more memory and potentially causing overflow.

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
