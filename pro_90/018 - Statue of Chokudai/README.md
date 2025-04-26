# Statue of Chokudai(★3)

> In C++, the arguments of trigonometric functions are in radians.

The difficulty lies in calculating the position at time $E$.
$$
\theta = \frac{E}{T} 2\pi
$$
The above formula gives the rotated angle (in radians) at time $E$. Since the radius is $𝐿/2$, the position can then be determined
$$
x = 0 \\[5px]
y = \frac{L}{2} \sin\theta \\[5px]
z = \frac{L}{2} - \frac{L}{2} \cos\theta
$$
Once the position is obtained, calculating the top-down(overhead) angle becomes straightforward, again using trigonometric functions (noting that the result must be converted to degrees).
$$
angle = 90 - \cos^{-1}(\frac{z}{\sqrt{(X - x)^2 + (Y - y)^2 + (0 - z)^2}})\frac{180}{\pi}
$$
