# Not Too Bright(2★)

The maximum number of LEDs when the number of cells is odd is $(N+1)/2$, and when it's even, it $(N/2)$. Using the properties of `int`, we get:

```cpp
int answer = ((H + 1) / 2) * ((W + 1) / 2);
```

Additionally, it is important to note that when $H = 1$ or $W = 1$, the condition will never be satisfied, so special handling is required.
