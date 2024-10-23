# Score Sum Queries(★2)

Since the maximum values of $N$ and $Q$ can reach 100,000, in extreme cases, the required number of calculations may be as high as 10,000,000,000. To efficiently handle such a large computational demand, we can use the [cumulative sum algorithm](https://en.wikipedia.org/wiki/CUSUM). This algorithm is particularly suitable for calculating the sum of a specific interval in a sequence, providing a more efficient way to solve the problem.
