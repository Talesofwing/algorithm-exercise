# Sign Up Requests(2★)

The difficulty lies in quickly determining whether a string already exists.

If we use an array and perform a linear search, the time complexity would reach $O(N^2)$, which is clearly inefficient.

The key, therefore, is to accelerate the search process. One effective solution is to use an `unordered_set`, which is implemented internally as a `HashTable`. The time complexity for seacrhing in this structure is $O(1)$.

As a result, the overall time complexity becomes $O(N)$, which satisfies the performance requirements.
