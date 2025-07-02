# Magic For Balls(★3)

There are two main points
- How to isolate prime numbers
- Calculating the height of a tree

An integer greater than 1 can be decomposed into a product of multiple prime numbers. Additionally, assume that $n = p \times q$. If $p \ge \sqrt{n}$, then $q \le \sqrt{n}$. This illustrates that they appear in pairs. Therefore, you only need to iterate up to ∣\sqrt{n}∣, that is, integers smaller than $n$.

Since the magic works for all numbers, every number(non-prime) will be decomposed into a combination of two numbers, forming a binary tree. The deepest level of a binary tree can be easily calculated.
