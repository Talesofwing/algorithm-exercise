# Heap-Sort

> - Time Complexity: $O(n \log n)$
> - Space Complexity: $O(1)$
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

Heap sort is preferred when:
1. **Guaranteed performance is crucial**: $O(n\log n)$ time complexity in all cases
2. **Memory is limited**: Requires only constant extra space (O(1))
3. **Partial sorting is acceptable**: Provides a partially soted array even if interrupted.

## Optimizations

1. Reduce the number of swaps

	A basic heap sort implementation often uses `swap` during each step of `sift-down`. This can be optimized.

	Instead of swapping the parent and child at every level, we can store the original parent value in a temporary variable, then move the larger child up into the parent position as the hole moves downward. When the correct position is found, we write the saved value into the final hole.

	This reduces the number of assignments/moves compared with repeated swaps, especially when the element type is expensive to move or copy.

2. Floyd sift-down

	In a standard `sift-down`, each level usually performs two comparisons:

	1. left child vs right child
	2. value vs larger child

	During heap sort, the `value` moved to the root after extracting the maximum is often taken from the end of the heap, so it is usually relatively small. In many cases, it will sink close to the bottom. Therefore, checking `if (value >= arr[child])` at every level can be wasted work.

	Floyd's idea is:

	1. First move the hole downward by repeatedly promoting the larger child.
	2. Then move the saved value upward until it reaches its correct position.

In practice, however, these optimizations may not produce a large difference for simple types such as `int`. Even with large inputs, for example around 10 million elements, the improvement in my test was only about 0.5 seconds.

For small inputs, the Floyd version may even be slightly slower because of its extra control flow and overhead.

## References
- [Wiki](https://en.wikipedia.org/wiki/Heapsort)
