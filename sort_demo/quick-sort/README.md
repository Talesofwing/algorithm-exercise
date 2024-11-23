# Quick-Sort

> - Time Complexity: $O(n \log n)$ (worst $O(n^2)$)
> - Space Complexity: $O(\log n) \to O(n)$
> - Stability : No
> - Adaptability : No


Quick sort is a sorting algorithm based on the [divide-and-conquer]((https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm))

The core idea is to select an element as the pivot, then partition the array into two subarrays: the subset smaller than the pivot is on the left, and the subset larger than the pivot is on the right. The steps are as follow:

1. Select pivot

	The choice of pivot affects the performance of the algorithm.

	- Fixed Position Selection

		- First or Last Element

			If the input data is already sorted or nearly sorted, this will lead to a time complexity of $O(n^2)$.

		- Middle Element

			Performs better than using the first or last element, but it still encounters the worst-case scenario in some cases.

	- Random Selection

		This can effectively avoid the worst-case scenario and offers better average performance for various input datasets.

		However, generating random numbers incurs additional overhead, and the results of the sorting may differ each time.

	- Median-of-Three

		Select the first element, last element, and middle element, then choose the median of these three as the pivot.

		This approach performs well for nearly sorted and completely random datasets, and is more stable than fixed-position selection.

		For example, with the list $[8, 2, 4, 5, 7, 1]$, the three elements would be [8, 4, 1]. Sorting these and selecting the median value as the pivot (or using comparisons) will yield the pivot 4.

	- Median-of-Five

		In addition to the first, middle, and last elements, two more elements are typically chosen from the 1/4 and 3/4 positions of the list.

		This provides a more precise pivot selection, further reducing the probability of the worst-case scenario.

2. Partitioning

	Rearrange the array such that all elements smaller than the pivot are placed to the left of it, and all elements larger than the pivot are placed to the right of it.

	There are various methods for partitioning, with two common ones being the `Lomuto partition` scheme and the `Hoare partition` scheme.

3. Recursively Sort the Subarrays

	Apply the `Quick Sort` algorithm recursively to the subarrays on the left and right of the pivot. The recursion stops when the length of the subarray is 0 or 1.

> [!Info]
>
> In this example, the `Median-of-Three` and `Hoare Partition` are used.

### Example

Taking the array $[8, 2, 1, 4, 3]$ as an example:

1. First, get $[8, 1, 3]$, and the median value of 3 is chosen as the pivot.

2. Create two pointers, one starting from the left and moving right, and the other starting from the right and moving left. The loop checks the relationship of the elements with the pivot:

	- On the left pointer, if the element is greater than 3, stop.
	- On the right pointer, if the element is less than or equal to 3, stop.
	- Swap the elements pointed to by the two pointers.
	- The loop stops when the left pointer is greater than or equal to the right pointer.

3. After the loop, the array becomes $[3, 2, 1, 4, 8]$, with the right pointer pointing to 1 (index = 2).

4. The next loop will operate on the two subarrays $[3, 2, 1]$ and $[4, 8]$.

5. In the subarray $[3, 2, 1]$, the pivot is 2, so it becomes $[1, 2, 3]$.

6. In the subarray $[4, 8]$, it remains $[4, 8]$.

7. The final result is $[1, 2, 3, 4, 8]$.

> Generally, when the number of elements in a set is less than or equal to 3, sorting is done using comparisons.
>
> Additionally, when the number of elements is below a certain threshold, Insertion Sort is typically used.

## References
- [Wiki](https://en.wikipedia.org/wiki/Quicksort)
