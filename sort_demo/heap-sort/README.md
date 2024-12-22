# Heap-Sort

> - Time Complexity: $O(n \log n)$
> - Space Complexity: $O(n)$
> - Stability : No
> - Adaptability : No

Heap sort utilizes [Heap Data-Structure](https://en.wikipedia.org/wiki/Heap_(data_structure)).

> Heap Data-Structure isn't Heap memory!

The algorithm proceeds as follows.

1. Construct heap data-structure
2. Repeat to extract the max/min element(head element)
	1. Exchange the root(largest or smallest element) with the last element
	2. Ignore the new last element(it's now in its sorted position)
	3. Reconstruct heap data-structure
	4. Repeats 1~3 steps, until the heap is empty

The example uses max-heap.

Heapsort is preferred when:
1. Guaranteed performance is crucial: $O(n\log n)$ time complexity in all cases
2. Memory is limited: Requires only constant extra space (O(1))
3. Partial sorting is acceptable: Provides a partially soted array even if interrupted.

## References
- [Wiki](https://en.wikipedia.org/wiki/Heapsort)
