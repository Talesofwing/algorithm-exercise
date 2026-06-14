# Shell Sort

> - Time Complexity: $<O(n^2)$
> - Space Complexity: $O(1)$
> - Stability: No
> - Adaptability: Yes

It is a simple improvement based on [Insertion Sort](../insertion-sort/), which increases the array’s local order through preprocessing and breaks through Insertion Sort’s $O(N^2)$ time complexity.

[Insertion Sort](../insertion-sort/) is very efficient for arrays that are already quite ordered, but it is inefficient when the initial order is low. Shell Sort’s idea is essentially to first increase order step by step with $h > 1$, and finally use [Insertion Sort](../insertion-sort/) with $h = 1$.

For example, start from $h = 8$, make the array into subsequences that are sorted with gap 8, then move to $h = 4$, then $h = 2$. At this point, because of [Insertion Sort](../insertion-sort/)'s nature, sorting becomes very fast, since local order has already been formed and the inner loop can terminate early. Finally when $h = 1$, the array already has high local order, so this traversal is also fast.

> In practice it is rarely used
> because [Insertion Sort](../insertion-sort/) is usually only used for small datasets. In that case, using Shell Sort adds more setup overhead;
> for large datasets, more efficient algorithms like [Quick Sort](../quick-sort/) and [Heap Sort](../heap-sort/) are used.

Generally use
$$
h = \frac{3^k - 1}{2}
$$
Its worst-case complexity is $O(n^{3/2})$. Here
- $k$: integer index used to generate the $k$-th gap value $h$ in the increasing sequence.

```cpp
int n = datas.size();
int h = 1;
while (h < n / 3) {
    h = 3 * h + 1;
}
// This does not use /2; the code uses recurrence to generate the sequence
// rather than computing the closed-form formula.
// The main goal is to find the largest value not greater than n.
```


## References
- [Wiki](https://en.wikipedia.org/wiki/Shellsort)
