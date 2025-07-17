# Counting Numbers(★3)

In practice, it is simply calculating the product of the total quantity and the number of digits, as shown in the following formula:

$$
\frac{(L + R) * (R - L - 1)}{2} \times digit \mod m
$$
where $digit$ represents the number of digits.

There are two main points to note:

1. The issue of overflow.

2. Division and modulo operations.

This problem primarily tests the developer’s knowledge of modular arithmetic.
