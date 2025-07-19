# There are two types of characters(★3)

There are two methods:
- Complementary counting
- Direct calculation

First, you need to use [Run-Length Encoding(RLE)](https://en.wikipedia.org/wiki/Run-length_encoding) to compress the data.

### Complementary Counting
$$
ans = total - contradiction
$$
Where
- $total = \frac{(N + 1)N}{2}$
- $contradiction = \frac{(L + 1)L}{2}$

	$L$ : The length of each element after [Run-Length Encoding](https://en.wikipedia.org/wiki/Run-length_encoding).

### Direct Calculation

After [Run-Length Encoding](https://en.wikipedia.org/wiki/Run-length_encoding), each element will be different from the previous one. Therefore, you only need to multiply the count of the current element by the count of all subsequent elements to get all possible interval combinations for the current element (this will also necessarily include `o` and `x` within the range).
