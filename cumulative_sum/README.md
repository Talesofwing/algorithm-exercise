# cumulative sum (累積和)

The cumulative sum algorithm maintains an additional array where each element stores the cumulative sum of the original array from the beginning to the current index `i`. Once the cumulative sum array is constructed, it allows for quick computation of the sum of elements within any range of the original array.

For a given range $[left, right]$, the cumulative sum within that range can be obtained using $sum[right] - sum[left - 1]$. If left is 0, the cumulative sum for the range is simply $sum[right]$.

This method is particularly suitable for scenarios where frequent range sum operations are required, as it reduces the time complexity of range sum queries from $O(n)$ to $O(1)$.

```c++
// Assuming there is an array named arr
sum[0] = arr[0];
sum[1] = arr[0] + arr[1];
...
sum[i] = arr[0] + arr[1] + ... + arr[i];
```

### Examples

- [AtCoder](https://atcoder.jp/contests/abc328/tasks/abc328_c)

The problem requires summing the occurrences of "two identical characters," making it suitable for the cumulative sum algorithm.

Taking "Sample Input 1" as an example, we have the string `mississippi`, which results in the cumulative sum array `{0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3}`. Assuming the interval is $[3, 9]$(assuming the array starts at 1), the cumulative sum for this interval is $2 - 0 = 2$, so the answer is 2.
