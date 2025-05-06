# Log Inequality(★3)

Since the logarithmic function is monotonically increasing, it suffices to check whether
$$
a < b^c
$$
holds.

Note the follow points:
1. Use `unsigned long long`
2. Use a `for` loop to compute $b^c$ instead of `pow`, to avoid precision issues.
