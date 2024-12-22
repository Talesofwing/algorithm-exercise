# Sorting

In this section, various sorting algorithms have been implemented. Specific examples can be found in different folders.

In every sorting algorithm, there are the following characteristics:
- Time Complexity

- Space Complexity

- Stability

	Whether the relative order of equal elements is preserved after sorting.
- Adaptability

	The ability of the algorithm to adjust its behavior based on the initial state of the input data. Specifically, an adaptive sorting algorithm will show significantly improved efficiency when handling nearly sorted data.

### Contents

1. [Bubble Sort](bubble-sort/)
2. [Selection Sort](selection-sort/)
3. [Insertion Sort](insertion-sort/)
4. [Merge Sort](merge-sort/)
5. [Quick Sort](quick-sort/)
6. [Heap Sort](heap-sort/)

### Test
Uses a total of 8 tests.
1. Empty Test
2. Single Element Test
3. Sorted Test
4. Reversed Test
5. Duplicate Elements Test
6. Same Elements Test
7. Large Elements Count Test
8. Boundary Test

|		Algorithm		| 	Element Count 	|                  Time(second) 			|
|     		-	 	    |     	  -     	|       				-			      	|
| Bubble Sort   		| 100,000   		| 36.29s 	   								|
| Selection Sort		| 100,000   		| 11.46s      								|
| Insertion Sort 		| 100,000   		| 5.94s <br> 3.83s(binary search) 			|
| Merge Sort     		| 1,000,000 		| 0.29s(recursive) <br> 0.28s(iterative)  	|
| Quick Sort     		| 1,000,000 		| 0.12s       								|
| Heap Sort 	 		| 1,000,000			| 0.26s       								|


### Comparison
#### Bubble Sort & Selection Sort
In general, `Selection Sort` performs better than `Bubble Sort` because `Bubble Sort` may require swapping elements more frequently during its iteration, whereas `Bubble Sort` swaps elements after every comparison if necessary.

#### Insertion Sort

In general, `Insertion Sort` performs better than `Bubble Sort` & `Selection Sort` because the follow reasons:
- Comparison Count
	Under nearly sorted conditions, the number of comparisons in `Insertion Sort` is fewer than that of `Bubble Sort` and `Selection Sort`.

- Swap Count
	Under nearly sorted conditions, the number of swap in `Insertion Sort` is fewer than that of `Bubble Sort` and `Selection Sort`.

This is because each element only needs to be compared with a small number of preceding elements to find its correct insertion point.

In conclusion, under the worst-case scenario, the performance of all three algorithms is similar. However, in more ordered datasets, `Insertion Sort` performs the best, which is why it is often chosen over the other two.

#### Merge Sort & Quick Sort

In general, `Quick Sort` performs better than `Merge Sort` because `Quick Sort` requires less memory.

However, in some cases, `Merge Sort` performs better, such as in:
- External sorting
- When stability is required"
