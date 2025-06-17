# I will not drop out(★3)

First, record the partial points as well as the difference between the full score and the partial points. Then, sort these scores in descending order and extract them in order to obtain the maximum total score.

Since a partial score can be ensured to be greater than half of the full score, the partial score for a given problem will always appear before the corresponding (full score - partial score) in the sorted list. In other words, when extracting scores, the partial score will always be selected before reaching the full score.
