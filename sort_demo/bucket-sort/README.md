# Bucket-Sort

> - Time Complexity: $O(n + w)$, where $w$ is the number of buckets; in the worst case, $O(n^2)$
> - Space Complexity: $O(n + k)$
> - Stability : Yes
> - Adaptability : No

Bucket Sort distributes the data into multiple buckets, sorts the data within each bucket, and finally merges the data from all the buckets.

The core idea is to distribute the data into buckets, reducing the number of elements to sort in one go. Then, sorting is performed within each bucket, where algorithms like [Insertion Sort](../insertion-sort/) can be used for efficient sorting. Finally, the results from all the buckets are merged together.

The algorithm proceeds as follows.

1. **Create Buckets**: Each bucket can be implemented as an array, linked list, or similar structure.
2. **Distribute Data into Buckets**: Assign data to different buckets based on specific rules. A common approach is to distribute data into buckets based on its value range. For example, create 10 buckets for the range 0–99, with each bucket responsible for a range of 10 values.
3. **Sort Each Bucket**: Sort the data within each bucket using an appropriate sorting algorithm.
4. **Merge Buckets**: Concatenate the sorted data from all the buckets in order.

> The example uses [Insertion Sort](../insertion-sort/).

Bucket sort is preferred when:
1. **Uniformly Distributed Data**: If the data is uniformly distributed, it can be evenly divided among buckets, resulting in fewer elements per bucket. This reduces sorting time within buckets and improves overall efficiency.
2. **Known and Relatively Small Data Range**: Bucket Sort requires prior knowledge of the data range to create an appropriate number of buckets. If the data range is too large, it requires a large number of buckets, increasing space complexity.

## References
- [Wiki](https://en.wikipedia.org/wiki/Bucket_sort)
