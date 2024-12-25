# Radix-Sort

> - Time Complexity: $O(wn)$, where $w$ is the maximum number of digits.
> - Space Complexity: $O(n + w)$
> - Stability : Yes
> - Adaptability : No

Radix Sort is a non-comparative sorting algorithm that can achieve linear time complexity without direct numerical comparisons. However, its efficiency may degrade when the number of digits in the maximum value is large.

It is primarily suitable for integers, strings, or data that can be numerically represented. Handling floating-point numbers requires additional complex operations.

Additionally, special handling is necessary when negative numbers are present.

The algorithm proceeds as follows.

1. Identify the maximum value in the dataset and calculate its digit length.
2. Starting from the least significant digit, sort the elements digit by digit using a stable sorting algorithm, such as [Counting Sort](../counting-sort/) or [Bucket Sort](../bucket-sort/). These algorithms perform sorting without comparisons, aligning with the characteristics of Radix Sort.
3. Collect the sorted elements in order after each round to form a new array.
4. Repeat steps 2 and 3 until the most significant digit is processed.

Radix sort is preferred when:
1. When the digit length of the data is relatively small

## References
- [Wiki](https://en.wikipedia.org/wiki/Radix_sort)
