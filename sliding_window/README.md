# sliding window

The core concept is managing a "window". Two pointers are used, pointing to the left and right sides of the array. Typically, at the beginning, both pointers point to the leftmost element.

The main operations include:
- Expanding/Shrinking the window:
- Move the right pointer to the right to expand the window.
- Move the left pointer to the right to shrink the window.

The concept of the sliding window is mainly used to solve:
- Sliding range problems.
- Calculations involving subarrays or subranges:
- Maximum/minimum value within a certain range.
- Sum of elements.

### References
- [しゃくとり法 (尺取り法) の解説と、それを用いる問題のまとめ](https://qiita.com/drken/items/ecd1a472d3a0e7db8dce)
