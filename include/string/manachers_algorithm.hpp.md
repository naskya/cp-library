---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/string/manachers_algorithm/1.test.cpp
    title: test/string/manachers_algorithm/1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Compute the longest palindrome lengths centered at each position
      using Manacher's Algorithm.
    links: []
  bundledCode: "#line 1 \"include/string/manachers_algorithm.hpp\"\n\n//! @file manachers_algorithm.hpp\n\
    \n#ifndef CP_LIBRARY_MANACHERS_ALGORITHM_HPP\n#define CP_LIBRARY_MANACHERS_ALGORITHM_HPP\n\
    \n#include <deque>\n\nnamespace lib {\n\n//! @brief Compute the longest palindrome\
    \ lengths centered at each position using Manacher's Algorithm.\n//! @tparam Container\
    \ container type (deduced from parameter)\n//! @param src source container (std::string,\
    \ std::vector, std::deque, ...)\n//! @return std::deque<int> containing palindrome\
    \ lengths (\"abbba\" -> {1 0 1 2 5 2 1 0 1})\n//! @note Time complexity: O(size(src))\n\
    template <typename Container>\n[[nodiscard]] std::deque<int> palindrome_length_array(const\
    \ Container& src) {\n  const int N = 2 * static_cast<int>(std::size(src)) + 1;\n\
    \  std::deque<int> res(N);\n  int i = 0, j = 0;\n  while (i < N) {\n    while\
    \ (i - j >= 0 && i + j < N && ((((i + j) % 2) == 0) || src[(i - j) / 2] == src[(i\
    \ + j) / 2])) {\n      ++j;\n    }\n    res[i] = j - 1;\n    int k  = 1;\n   \
    \ while (i - k >= 0 && k + res[i - k] + 1 < j) {\n      res[i + k] = res[i - k];\n\
    \      ++k;\n    }\n    i += k;\n    j -= k;\n  }\n  res.pop_front();\n  res.pop_back();\n\
    \  return res;\n}\n\n}  // namespace lib\n\n#endif  // CP_LIBRARY_MANACHERS_ALGORITHM_HPP\n"
  code: "\n//! @file manachers_algorithm.hpp\n\n#ifndef CP_LIBRARY_MANACHERS_ALGORITHM_HPP\n\
    #define CP_LIBRARY_MANACHERS_ALGORITHM_HPP\n\n#include <deque>\n\nnamespace lib\
    \ {\n\n//! @brief Compute the longest palindrome lengths centered at each position\
    \ using Manacher's Algorithm.\n//! @tparam Container container type (deduced from\
    \ parameter)\n//! @param src source container (std::string, std::vector, std::deque,\
    \ ...)\n//! @return std::deque<int> containing palindrome lengths (\"abbba\" ->\
    \ {1 0 1 2 5 2 1 0 1})\n//! @note Time complexity: O(size(src))\ntemplate <typename\
    \ Container>\n[[nodiscard]] std::deque<int> palindrome_length_array(const Container&\
    \ src) {\n  const int N = 2 * static_cast<int>(std::size(src)) + 1;\n  std::deque<int>\
    \ res(N);\n  int i = 0, j = 0;\n  while (i < N) {\n    while (i - j >= 0 && i\
    \ + j < N && ((((i + j) % 2) == 0) || src[(i - j) / 2] == src[(i + j) / 2])) {\n\
    \      ++j;\n    }\n    res[i] = j - 1;\n    int k  = 1;\n    while (i - k >=\
    \ 0 && k + res[i - k] + 1 < j) {\n      res[i + k] = res[i - k];\n      ++k;\n\
    \    }\n    i += k;\n    j -= k;\n  }\n  res.pop_front();\n  res.pop_back();\n\
    \  return res;\n}\n\n}  // namespace lib\n\n#endif  // CP_LIBRARY_MANACHERS_ALGORITHM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/string/manachers_algorithm.hpp
  requiredBy: []
  timestamp: '2022-03-23 16:30:51+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/string/manachers_algorithm/1.test.cpp
documentation_of: include/string/manachers_algorithm.hpp
layout: document
title: Manacher's algorithm
---

[Manacher's algorithm](https://en.wikipedia.org/wiki/Longest_palindromic_substring#Manacher's_algorithm) を用いて、配列中の各位置を中心とする最長の回文である連続部分文字列の長さを求める関数が定義されています。

---

### `palindrome_length_array(S)`

`S` の各位置を中心とする最長の回文である連続部分文字列の長さを格納した配列 ([`std::deque<int>`](https://cpprefjp.github.io/reference/deque/deque.html)) を返します。例えば [`std::string`](https://cpprefjp.github.io/reference/string/basic_string.html) 型の値 `S` が `"abbba"` である場合、それぞれの位置に対して最長の回文の長さは

![](https://latex.codecogs.com/gif.latex?%5Cdpi%7B250%7D%20%5Cbegin%7Btabular%7D%7Bl%7Clllllllll%7D%20%5Chline%20center%20%26%20a%20%26%20%26%20b%20%26%20%26%20b%20%26%20%26%20b%20%26%20%26%20a%20%5C%5C%20%5Chline%20length%20%26%201%20%26%200%20%26%201%20%26%202%20%26%205%20%26%202%20%26%201%20%26%200%20%26%201%20%5C%5C%20%5Chline%20%5Cend%7Btabular%7D)

となるため、返り値は `{1 0 1 2 5 2 1 0 1}` です。

---
