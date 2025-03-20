# Encyclopedia of Parentheses(★3)

This problem can be understood in two parts:

Part 1: Counting All Possible Cases
The conditions in the problem align perfectly with binary values of 0 and 1, where 0 represents '(' and 1 represents ')'.
Therefore, the total number of possible cases is $2^N$.

Part 2: Checking Whether a Certain Combination Meets the Conditions

- When encountering '(', add 1 point.
- When encountering ')', subtract 1 point.

To be valid, the number of '(' to the left of ')' should be sufficient to avoid a negative score at any point.

Therefore, if the score becomes negative at any point, the combination is invalid.

Finally, the total score should be zero at the end.
