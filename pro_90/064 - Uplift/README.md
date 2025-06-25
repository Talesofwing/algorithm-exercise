# Dice Product(★3)

Record the difference values, because the differences within the interval $[L, R]$ do not change. The only positions where the difference changes are at $L - 1$ and $R + 1$. Moreover, if $L = 0$ or $R = N$, these cases can be ignored.

Therefore, for each operation, it is only necessary to consider the positions $L - 1$ and $R + 1$. By comparing the new and old values at these positions, the change in value can be determined and added to `ans`.
