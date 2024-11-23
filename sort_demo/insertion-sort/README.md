# Insertion-Sort

> - Time Complexity: $O(n^2)$
> - Space Complexity: $O(1)$
> - Stability : Yes
> - Adaptability : Yes

Insertion sort is a simple sorting algorithm. The process is as follows:

1. The first element is considered sorted
2. Take the next element and search backward through the sorted portion
3. If a currently sorted element is greater than the taken element, shift the sorted element one position to the right
4. Repeat step 3 until a sorted element less than or equal to the taken element is found

The core idea is to divide the data into sorted and unsorted portions. Each element from the unsorted portion is compared with the elements in the sorted portion, from tail to head, to determine its correct position, and then inserted into that position.

> The example implements a binary search

## References
- [Wiki](https://en.wikipedia.org/wiki/Insertion_sort)
