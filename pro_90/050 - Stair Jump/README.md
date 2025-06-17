# Stair Jump(★3)

Use a dynamic programming algorithm to record all possible ways to reach the current step.

There are two cases for the current step:
- Move forward one step from the previous step — that is, the number of ways to reach the previous step.
- Move forward L steps from the (current–L)th step — that is, the number of ways to reach the (current–L)th step.
By adding these two values together, you obtain the total number of ways to reach the current step.
