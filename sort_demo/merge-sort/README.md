# Merge-Sort

> - Time Complexity: $O(n\log n)$
> - Space Complexity: $O(n)$
> - Stability : Yes
> - Adaptability : No

Merge sort is a sorting algorithm based on the [divide-and-conquer]((https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm)).

It recursively divides the unsorted data into smaller subarrays until each subarray contains only one element (which is inherently sorted). These sorted subarrays are then merged to produce a fully sorted array.

Merge sort is generally described as having two main steps:
- Divide: This step recursively divides the unsorted list into smaller sublists until each sublist contains only one element (which is inherently sorted). This division is implicitly handled through recursive function calls.

- Conquer(Merge): This step merges the sorted sublists to produce larger sorted sublists. This can be implemented in two ways:
	- Recursive Merge: The merge operation itself is implemented recursively.
	- Iterative Merge: The merge operation is implemented iteratively using loops.

The iterative merge sort generally exhibits better performance than the recursive version because it avoids the overhead associated with recursive function calls.

Use Cases:

- Guaranteed O(n log n) time complexity (e.g., large datasets, predictable performance).
- Stable sorting (preserves the relative order of equal elements).

Caveats:
- Requires O(n) extra space for temporary arrays during the merge process, unlike some in-place sorting algorithms (e.g., quicksort).

## References
- [Wiki](https://en.wikipedia.org/wiki/Merge_sort)
