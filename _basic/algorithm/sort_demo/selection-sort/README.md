# Selection-Sort

> - Time Complexity: $O(n^2)$
> - Space Complexity: $O(1)$
> - Stability : No
> - Adaptability : No

Selection sort is a simple sorting algorithm, primarily used for educational purposes to illustrate the basic concepts of sorting. While easy to understand and implement, it's not very efficient with $O(n^2)$ time complexity and is rarely used in practical applications due to the availability of more efficient algorithms. The process is as follows:

1. Find the minimum(or maximum) element in the unsorted sublist
2. Swap the minimum (or maximum) element with the first element of the unsorted sublist and mark it as sorted.
3. Repeat steps 1 and 2 until the unsorted sublist is empty

The core idea is to find the smallest(or largest) element from the unsorted portion of the array, swap it with the first element of the unsorted portion, effectively placing it at the end of the sorted portion.

## References
- [Wiki](https://en.wikipedia.org/wiki/Selection_sort)
