# Colorful Blocks 2(★3)

The formula for the number of ways is as follows:

$$
k(k - 1)(k - 2)^{n - 2}
$$

It is necessary to break down $(k - 2)^{n - 2}$.

By using exponentiation by squaring, for example:

$$
\displaylines {
a^8 = a^4a^4 = a^2a^2a^2a^2 \\
a^9 = a^1a^4a^4 = a^1a^2a^2a^2a^2
}
$$

Through such decomposition, the time complexity can be reduced to $O(\log n)$.
