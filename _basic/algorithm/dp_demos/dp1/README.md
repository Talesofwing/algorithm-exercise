# Dynamic Programming 001

[AtCoder D - 禁止された数字](https://atcoder.jp/contests/abc007/tasks/abc007_4)

The problem can be decomposed into the following subproblems:

1. Whether the value has reached the digit corresponding to the input value

	If it is, then the next iteration will only go up to the current digit's value; otherwise, it will iterate through 0 to 9.

	For example, if the input value is $45$ and the tens digit has already reached 4, then when iterating through the ones digit, you can no longer iterate from 0 to 9 but should only iterate from 0 to 5.

	Since the corresponding digit's value hasn't been reached, in the next iteration, it can go through 0 to 9. Therefore, the number of restricted values obtained in these two cases will be different.

2. Whether the value is a restricted digit, such as "4" or "9"

	This can be divided into two cases: when the current value is restricted and when it is not. The number of restricted values obtained will differ depending on whether the current digit is restricted or not.

	For example, if the input value is $549$, when the tens digit is restricted, there will be 9 restricted values, but if it is not restricted, there will be 2 restricted values. Therefore, when iterating through the hundreds digit, you can immediately determine the number of restricted values by checking whether the tens digit is a restricted digit.

3. Digit index

	The highest digit index is 0.

	This is mainly used to distinguish the situation when processing the value at the $i^{th}$ digit.

	For example, if the input value is $1024$, you first process the thousands digit, then the hundreds digit, followed by the tens digit, and finally the ones digit. When processing the thousands digit, you can quickly know the number of restricted values for i = 1 (hundreds digit) in certain cases, without having to compute it directly.

	For example, when the hundreds digit is less than the corresponding input value digit and is not a restricted digit, the tens digit is less than the corresponding input value digit and is a restricted digit, and the ones digit is greater than the corresponding input value digit and is not a restricted digit. If this case has already been computed before, you can immediately get the result. Otherwise, the calculation will be necessary.

In the example problem, "入力例2" has a range of [40, 49].

- Case 40:
	1. Iterate from 0 to 4.
	2. In the first operation, when the tens digit is 0, and at the ones digit (idx=1) where the tens digit is less than 4 (less=true), there will be 2 restricted numbers: {04, 09}. This will set memo[1][1][0] (less=true, hasForbidden=false) to 2, which means it corresponds to the case where there are no restricted digits and the value has not yet reached its maximum for the tens digit.
	3. In the second operation, when the tens digit is 1, the condition is the same as when the tens digit is 0, so the number of restricted digits can be directly obtained as 2.
	4. In the third operation, when the tens digit is 2, the condition is the same as when the tens digit is 0, so the number of restricted digits can be directly obtained as 2.
	5. In the fourth operation, when the tens digit is 3, the condition is the same as when the tens digit is 0, so the number of restricted digits can be directly obtained as 2.
	6. In the fifth operation, when the tens digit is 4, since less=false, it requires re-iteration up to the value of the ones digit, which is 0 here. Therefore, only one iteration is needed, yielding 1 restricted number: {40}.
	7. In total, there are 9 restricted numbers for 40.

- Case 49: The situation is the same as Case 40, except that there are 9 additional restricted numbers: {41, 42, ..., 49}. Therefore, the total number of restricted values for 49 is 9 more than that of 40, resulting in a total of 18 restricted numbers for 49.

- Final: Since the range is $[40, 49]$, we should actually consider the restricted numbers for 39. Ultimately, by subtracting the number of restricted values for 39 from the number of restricted values for 49, we can determine the number of restricted values in this interval: 10.

Other examples:

- Case 45: This situation is also similar to Case 40. However, it is important to note that when the tens digit is 4, we should not iterate from 0 to 9, but rather from 0 to 5.

If this operation needs to be used multiple times, the `memo` can be set as a global variable, allowing the computed results to be reused. However, this will occupy additional memory.
