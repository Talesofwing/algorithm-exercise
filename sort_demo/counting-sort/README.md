# Counting-Sort

> - Time Complexity: $O(n + k)$
> - Space Complexity: $O(n + k)$
> - Stability : Yes
> - Adaptability : No

Counting Sort is a non-comparative sorting algorithm that does not rely on numerical comparisons and can achieve linear time complexity.

It is only suitable for integers or data that can be mapped to an integer range.

The algorithm proceeds as follows.

1. **Find the Maximum Value**: Identify the largest element in the input array.
2. **Initialize the Counting Array**: Create a counting array `count` with a size of `max + 1` and initialize all values to 0.
3. **Count the Elements**: Traverse the input array, and for each element `x`, increment `count[x]` by 1.
4. **Calculate Cumulative Counts**: Traverse the counting array to compute the cumulative count for each element. `count[i]` will store the total number of elements less than or equal to `i`.
5. **Build the Sorted Array**: For each element `x` in the input array, use `count[x]` to determine its position in the sorted array. Place `x` at `output[count[x] - 1]` and decrement `count[x]` by 1.

Heap sort is preferred when:
1. **Small Range of Data**: Counting Sort is efficient when the range of data is small. For large ranges, the counting array becomes too large and consumes excessive memory.
2. **Subroutine in [Radix Sort](../radix-sort/)**: Counting Sort is often used as a subroutine in Radix Sort.
3. **Data Preprocessing**: In some cases, Counting Sort can be used for data preprocessing, such as calculating the frequency of each value or constructing histograms.

## References
- [Wiki](https://en.wikipedia.org/wiki/Counting_sort)
