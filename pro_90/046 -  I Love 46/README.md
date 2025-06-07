# I Love 46(★3)

The modulo operation satisfies the following equality:

$$
(a + b + c) \% d = 0 \\[5px]
((a \% d) + (b \% d) + (c \% d)) \% d = 0
$$

Since $𝑑=46$, we can create three arrays of length 46 to record the frequency of each remainder.

There are a total of $46^3$ combinations, so we can use three nested $for$ to enumerate all possible cases.
