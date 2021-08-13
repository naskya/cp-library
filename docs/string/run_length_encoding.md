---
title: Run length encoding
documentation_of: //include/string/run_length_encoding.hpp
---

[連長圧縮](https://ja.wikipedia.org/wiki/%E9%80%A3%E9%95%B7%E5%9C%A7%E7%B8%AE)を行う関数が定義されています。

---

### `run_length_encoding(S)`

`S` に対する連長圧縮の結果を返します。`S` として文字列だけではなく [`std::vector<int>`](https://cpprefjp.github.io/reference/vector/vector.html) 等のコンテナを渡すこともできます。

例えば `std::string` 型の値 `S` が `"aabbbccccd"` の時、`run_length_encoding(S)` の値は [`std::vector<std::pair<char, int>>`](https://cpprefjp.github.io/reference/vector/vector.html) 型の値 `{ ('a', 2) ('b', 3) ('c', 4) ('d', 1) }` となります。

空のコンテナを渡した場合、返り値の要素数は $0$ です。

---
