# Cubic Cake(★2)

### Environment

- C++ 20

### Introduction

源代碼提供了兩種不同的實現方法：

1. 分割法(split_cube): 正如其名，這種方法通過逐步將長方體分割成更小的單位，最終達到正方體的形狀。然而，這種方法的效率相對較低，當處理大型問題時，可能導致運行時間過長（overtime）或數據溢出（overflow），因此不適合應用於該題目。

2. GCD(最大公因數)方法: 這種方法涉及到計算長方體三邊的最大公因數。例如，對於一個邊長為 (3, 6, 9) 的長方體，其最大公因數為 3。透過將每邊長除以GCD，我們可以得出將長方體等分為若干個正方體所需的份數。每邊長除以GCD後的值，即表示將每邊分割成多少份時，每一份都形成正方體。再將這個分割數減去1，就能得到總共需要的分割次數。

求解最大公因數的常用算法是[輾轉相除法](https://zh.wikipedia.org/wiki/%E8%BC%BE%E8%BD%89%E7%9B%B8%E9%99%A4%E6%B3%95)，這是一種高效且常用的數學方法來計算兩個數字的最大公因數。在這個場景中，使用GCD方法不僅能大幅提升計算效率，也能確保準確無誤地求得分割次數。


### References

- [AtCoder - Cubic Cake(★2)](https://atcoder.jp/contests/typical90/tasks/typical90_v)