# Cross Sum(★2)

This problem is quite simple. The value of each cell equals the sum of its corresponding row and column. However, one important point to note is that if we recalculate the row and column sums for each cell, the time complexity will reach $O(HW(H+W))$. Therefore, we can store the sums of each row and each column in advance, achieving a final time complexity of $O(HW)$.

Additionally, it is important to note that the value of each cell will be counted twice, so we need to subtract the value of that cell at the end.
