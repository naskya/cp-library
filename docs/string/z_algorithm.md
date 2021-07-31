---
title: Z algorithm
documentation_of: //include/string/z_algorithm.hpp
---

[Z algorithm](https://codeforces.com/blog/entry/3107) を用いて最長共通接頭辞の長さを格納した配列を求める関数が定義されています。

---

### `z_algorithm(S)`

`S` 内の各位置についての最長共通接頭辞の長さを格納した配列を返します。`S` として文字列だけではなく `std::vector<int>` 等のコンテナを渡すこともできます。

例えば `std::string` 型の値 `S` が `"abcabcabc"` の時、`z_algorithm(S)` の値は `std::vector<int>` 型の値 `{ 9 0 0 6 0 0 3 0 0 }` となります。

---
