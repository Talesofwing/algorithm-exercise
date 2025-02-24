# Insertion-Sort

> - Time Complexity: $O(n^2)$
> - Space Complexity: $O(1)$
> - Stability : Yes
> - Adaptability : Yes

Insertion sort is a simple sorting algorithm. The process is as follows:

1. The first element is considered sorted
2. Take the next element and search backward through the sorted portion
3. If a currently sorted element is greater than the taken element, shift the sorted element one position to the right and insert the taken element at the correct position.
4. Repeat step 3 until all elements are sorted.

The core idea is to divide the data into sorted and unsorted portions. Each element from the unsorted portion is compared with the elements in the sorted portion, from tail to head, to determine its correct position, and then inserted into that position.

> The example implements a binary search

Insertion Sort is generally used in the following cases:
- **Small data size**
- **Nearly sorted data**: Adaptive
- **As a subroutine for other sorting algorithms**: Used for handling subarrays, typically when the size of the subarray is below a certain threshold, insertion sort is applied to improve efficiency.

## References
- [Wiki](https://en.wikipedia.org/wiki/Insertion_sort)
