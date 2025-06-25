# Dice Product(★3)

The problem can be solved by using factorization. Take two dice, $A(A_1, A_2, A_3, A_4, A_5, A_6)$ and $B(B_1, B_2, B_3, B_4, B_5, B_6)$, as an example.

We have

$$
A_1 \times (B_1 + B_2 + B_3 + ... + B_6) +
A_2 \times (B_1 + B_2 + B_3 + ... + B_6) +
...
A_6 \times (B_1 + B_2 + B_3 + ... + B_6)
$$

Therefore, we obtain

$$
(A_1 + A_2 + ... + A_6) \times (B_1 + B_2 + ... + B_6)
$$

The same reasoning applies for $N$ dice as well. In this way, the calculation can be completed in $O(N)$ time complexity.

