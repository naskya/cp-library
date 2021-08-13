---
title: Manacher's algorithm
documentation_of: //include/string/manachers_algorithm.hpp
---

[Manacher's algorithm](https://en.wikipedia.org/wiki/Longest_palindromic_substring#Manacher's_algorithm) を用いて、配列中の各位置を中心とする最長の回文である連続部分文字列の長さを求める関数が定義されています。

---

### `palindrome_length_array(S)`

`S` の各位置を中心とする最長の回文である連続部分文字列の長さを格納した配列 ([`std::deque<int>`](https://cpprefjp.github.io/reference/deque/deque.html)) を返します。例えば [`std::string`](https://cpprefjp.github.io/reference/string/basic_string.html) 型の値 `S` が `"abbba"` である場合、それぞれの位置に対して最長の回文の長さは

![](https://latex.codecogs.com/gif.latex?%5Cdpi%7B250%7D%20%5Cbegin%7Btabular%7D%7Bl%7Clllllllll%7D%20%5Chline%20center%20%26%20a%20%26%20%26%20b%20%26%20%26%20b%20%26%20%26%20b%20%26%20%26%20a%20%5C%5C%20%5Chline%20length%20%26%201%20%26%200%20%26%201%20%26%202%20%26%205%20%26%202%20%26%201%20%26%200%20%26%201%20%5C%5C%20%5Chline%20%5Cend%7Btabular%7D)

となるため、返り値は `{1 0 1 2 5 2 1 0 1}` です。

---
