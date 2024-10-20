# Cross Sum(★2)

### Environment

- C++ 20

### Introduction

若不進行任何預處理步驟，時間複雜度將達到$O(HW(H+W))$。為了優化效率，可以提前計算並儲存每一行和每一列的總和。採用這種方法，時間複雜度可以有效降低到 $O(HW)$，從而大幅提高了算法的執行效率。

請注意，在這個處理過程中，每個格子的值會被重複加算兩次。因此，需要從最終的結果中扣除格子的值一次。這樣做可以確保每個格子的值只被計算一次。

### References

- [AtCoder - Cross Sum(★2)](https://atcoder.jp/contests/typical90/tasks/typical90_d)