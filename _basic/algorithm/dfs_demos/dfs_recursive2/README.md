# dfs_recrusive2

### Environment

- C++ 20

### Examples

- [AtCoder](https://atcoder.jp/contests/abs/tasks/arc065_a)

**關鍵: 字符串反轉**

順序字符串存在歧義性，如`erase`和`eraser`。如果不消除歧義，使用全探索的方式，在字符串愈來愈長的情況下，可能會導致`超時`或`內存超出限制`。

反轉字符串得: `maerd`, `remaerd`, `esare`, `resare`。反轉順序下不存在歧義性，因此可以簡單且快速地進行判斷。

### References

- [dfs_recrusive](../dfs_recursive/README.md)