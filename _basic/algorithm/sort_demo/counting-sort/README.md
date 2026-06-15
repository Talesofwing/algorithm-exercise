# Counting-Sort

> - Time Complexity: $O(n + k)$
> - Space Complexity: $O(n + k)$
> - Stability : Yes
> - Adaptability : No

Counting Sort is a non-comparative sorting algorithm that does not rely on numerical comparisons and can achieve linear time complexity.

It is only suitable for integers or data that can be mapped to an integer range.

The core idea is to create an array ranging from 0 to max and map the values into the array. This allows for fast sorting, but the drawback is that it requires a significant amount of additional memory.

The algorithm proceeds as follows.

1. **Find the Maximum Value**: Identify the largest element in the input array.
2. **Initialize the Counting Array**: Create a counting array `count` with a size of `max + 1` and initialize all values to 0.
3. **Count the Elements**: Traverse the input array, and for each element `x`, increment `count[x]` by 1.
4. **Calculate Cumulative Counts**:  Iterate through the count array and compute the cumulative count for each element using the formula:
`count[x] = count[x - 1] + count[x]`
5. **Build the Sorted Array**: For each element `x` in the input array, use `count[x]` to determine its position in the sorted array. Place `x` at `output[count[x] - 1]` and decrement `count[x]` by 1.

Heap sort is preferred when:
1. **Small Range of Data**: Counting Sort is efficient when the range of data is small. For large ranges, the counting array becomes too large and consumes excessive memory.
2. **Subroutine in [Radix Sort](../radix-sort/)**: Counting Sort is often used as a subroutine in Radix Sort.
3. **Data Preprocessing**: In some cases, Counting Sort can be used for data preprocessing, such as calculating the frequency of each value or constructing histograms.

## Handling Negative Numbers
There are two common approaches:
- Handle positives and negatives separately
- Handle positives and negatives together
    by applying an offset. For example, if the smallest negative number is -3, adding 3 to every value makes the smallest number 0.

## Non-Numeric Data

Non-numeric data (such as structs or objects) requires more than just sorting the numeric keys. You must also keep the actual original objects in order, so you need to care about both stability and how to preserve the original items.

Key difference:
- **Counting array**: only suitable for **pure numeric values** (the value itself is the data), not complex objects
- **Prefix sum**: suitable for **complex objects** (sort by key while preserving all original object fields)

### Why can't a counting array handle complex objects?

Suppose we have the following array (each number is an object key, and color/symbol represent other object attributes):

> Input: `[3🟦, 1🟥, 3🟩, 2🟨, 1🟧, 3🟪, 2🟫]`

#### Counting array (unstable × cannot handle objects)

```
        🟦     🟥     🟩     🟨     🟧     🟪     🟫      ← original objects
Input:  [ 3 ,   1 ,   3 ,   2 ,   1 ,   3 ,   2 ]          ← keys
         │     │     │     │     │     │     │
         │     │     │     │     │     │     │
         └──┬──┘     │     │     │     │     │
            │        │     │     │     │     │
            ▼        ▼     ▼     ▼     ▼     ▼
         ┌──────────────────────────────────────┐
         │   count[1] = 2   ← know there are 2 ones     │
         │   count[2] = 2   ← know there are 2 twos     │
         │   count[3] = 3   ← know there are 3 threes   │
         │   but completely lost track of 🟦🟥🟩🟨🟧🟪🟫  │
         └────────────────┬─────────────────────┘
                          │ rebuild by key order
                          ▼
         ┌──────────────────────────────────────┐
         │   Output: [1, 1, 2, 2, 3, 3, 3]        │
         │         ↑  ↑  ↑  ↑  ↑  ↑  ↑          │
         │      only keys remain, original objects are lost!  │
         └──────────────────────────────────────┘
```

A counting array only records the frequency of each key. It does not track the original objects' positions or references, so it cannot place the original objects back into the output — it never stored them in the first place.

Therefore, for non-numeric data, a counting array alone is not feasible. You must use prefix sums.

#### Prefix sum (stable ✅ preserves original objects)
The prefix sum approach is completely different from a counting array — **it does not rebuild keys only, it places each original object into its correct position**.

**The prefix sum value represents the last position of that key in the output array**:
```
prefix[1] = 2   → the last key=1 goes to output[1] (index 2-1)
prefix[2] = 4   → the last key=2 goes to output[3] (index 4-1)
prefix[3] = 7   → the last key=3 goes to output[6] (index 7-1)
```

Traverse the original array from **right to left** (this is the key to stability!), and place each original object into the target position. The output array evolves as follows:
```
← 2🟫: [  ?,   ?,   ?, 🟫,   ?,   ?,   ?]   prefix[2]: 4→3
← 3🟪: [  ?,   ?,   ?, 🟫,   ?,   ?, 🟪]   prefix[3]: 7→6
← 1🟧: [  ?, 🟧,   ?, 🟫,   ?,   ?, 🟪]   prefix[1]: 2→1
← 2🟨: [  ?, 🟧, 🟨, 🟫,   ?,   ?, 🟪]   prefix[2]: 3→2
← 3🟩: [  ?, 🟧, 🟨, 🟫,   ?, 🟩, 🟪]   prefix[3]: 6→5
← 1🟥: [🟥, 🟧, 🟨, 🟫,   ?, 🟩, 🟪]   prefix[1]: 1→0
← 3🟦: [🟥, 🟧, 🟨, 🟫, 🟦, 🟩, 🟪]   prefix[3]: 5→4
```

✅ Result `[1🟥, 1🟧, 2🟨, 2🟫, 3🟦, 3🟩, 3🟪]` — the original objects are preserved, and the relative order of equal keys is retained.

## References
- [Wiki](https://en.wikipedia.org/wiki/Counting_sort)
