# Select +／- One(★2)

### Environment

- C++ 20

### Introduction

可以運用奇偶性(パリティ)作為主要的判斷依據。

首先，當總相差數值是奇數時，需要的步數也應該是奇數才能剛好用完所有步數。同理，當總相差數值為偶數時，步數亦應為偶數。基於此，第一步驟是確定總相差值與給定的步數k是否具有相同的奇偶性。除此之外，還必須檢查總相差值是否小於或等於k，以確保可以在k步內完成所需的所有變更。

### References

- [AtCoder - Select +／- One(★2)](https://atcoder.jp/contests/typical90/tasks/typical90_x)