# Intro-Sort

> - Time Complexity: $O(n \log n)$
> - Space Complexity: $O(\log n)$
> - Stability : No
> - Adaptability : Yes

> [!NOTE]
> In C++, the threshold for switching to insertion sort in the sort function is 16 elements.

The core idea is to combine the advantages of [Quick Sort](../quick-sort/), [Heap Sort](../heap-sort/), and [Insertion Sort](../insertion-sort/) to achieve efficient sorting in various scenarios. The strategy is as follows:

1. **Recursion Depth Limit**: A recursion depth limit is set, typically $2\log_2(n)$, where $n$ is the number of elements to be sorted.
2. **Quick Sort**: [Quick Sort](../quick-sort/) is primarily used for sorting.
3. **Recursion Depth Check**: Before each recursive call to [Quick Sort](../quick-sort/), Intro Sort checks whether the current recursion depth has exceeded the limit.
4. **Heap Sort**: If the recursion depth exceeds the limit, Intro Sort switches to [Heap Sort](../heap-sort/).
5. **Insertion Sort**: When the number of elements to be sorted is below a certain threshold (commonly 16), Intro Sort switches to [Insertion Sort](../insertion-sort/).

The core concept is to use the most suitable sorting method based on the specific situation, optimizing both time and space.

Intro sort is preferred when:
1. **General Sorting Needs**: It is suitable for most cases where general data needs to be sorted because Intro Sort balances speed and stability effectively.

## References
- [Wiki](https://en.wikipedia.org/wiki/Introsort)
