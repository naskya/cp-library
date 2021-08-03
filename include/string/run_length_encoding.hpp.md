---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/string/run_length_encoding/1.test.cpp
    title: test/string/run_length_encoding/1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Print warning message
    links: []
  bundledCode: "#line 1 \"include/string/run_length_encoding.hpp\"\n\n//! @file run_length_encoding.hpp\n\
    \n#ifndef RUN_LENGTH_ENCODING_HPP\n#define RUN_LENGTH_ENCODING_HPP\n\n#include\
    \ <iostream>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\n\
    #ifndef warn\n#  ifndef ONLINE_JUDGE\n//! @brief Print warning message\n//! @note\
    \ You can suppress the warning by uncommenting line 17\n#    define warn(msg)\
    \ (std::cerr << (msg) << '\\n')\n// #  define warn(msg) (static_cast<void>(0))\n\
    #  else\n#    define warn(msg) (static_cast<void>(0))\n#  endif\n#  define warn_not_defined\n\
    #endif\n\nnamespace lib {\n\n//! @tparam Container container type (deduced from\
    \ parameters)\n//! @param src source container (std::string, std::vector, std::deque,\
    \ ...)\n//! @return A std::vector<std::pair<element type of src, int>> which contains\
    \ the RLE result.\n//! @note Time complexity: O(size(src))\ntemplate <typename\
    \ Container>\n[[nodiscard]] auto run_length_encoding(const Container& src) {\n\
    \  using Elem = std::decay_t<decltype(*std::cbegin(std::declval<Container>()))>;\n\
    \  if (src.empty()) {\n    warn(\"An empty container is provided.\");\n    return\
    \ std::vector<std::pair<Elem, int>> {};\n  }\n  std::vector<std::pair<Elem, int>>\
    \ res {{*std::cbegin(src), 1}};\n  for (auto iter1 = std::cbegin(src), iter2 =\
    \ iter1 + 1; iter2 != std::cend(src); iter2 += 2) {\n    if (*iter1 == *iter2)\n\
    \      ++res.back().second;\n    else\n      res.emplace_back(*iter2, 1);\n  \
    \  std::swap(iter1, iter2);\n  }\n  return res;\n}\n\n}  // namespace lib\n\n\
    #ifdef warn_not_defined\n#  undef warn\n#  undef warn_not_defined\n// warn may\
    \ be defined 2 times (by uncommenting line 17)\n#  ifdef warn\n#    undef warn\n\
    #  endif\n#endif\n\n#endif  // RUN_LENGTH_ENCODING_HPP\n"
  code: "\n//! @file run_length_encoding.hpp\n\n#ifndef RUN_LENGTH_ENCODING_HPP\n\
    #define RUN_LENGTH_ENCODING_HPP\n\n#include <iostream>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\n#ifndef warn\n#  ifndef ONLINE_JUDGE\n\
    //! @brief Print warning message\n//! @note You can suppress the warning by uncommenting\
    \ line 17\n#    define warn(msg) (std::cerr << (msg) << '\\n')\n// #  define warn(msg)\
    \ (static_cast<void>(0))\n#  else\n#    define warn(msg) (static_cast<void>(0))\n\
    #  endif\n#  define warn_not_defined\n#endif\n\nnamespace lib {\n\n//! @tparam\
    \ Container container type (deduced from parameters)\n//! @param src source container\
    \ (std::string, std::vector, std::deque, ...)\n//! @return A std::vector<std::pair<element\
    \ type of src, int>> which contains the RLE result.\n//! @note Time complexity:\
    \ O(size(src))\ntemplate <typename Container>\n[[nodiscard]] auto run_length_encoding(const\
    \ Container& src) {\n  using Elem = std::decay_t<decltype(*std::cbegin(std::declval<Container>()))>;\n\
    \  if (src.empty()) {\n    warn(\"An empty container is provided.\");\n    return\
    \ std::vector<std::pair<Elem, int>> {};\n  }\n  std::vector<std::pair<Elem, int>>\
    \ res {{*std::cbegin(src), 1}};\n  for (auto iter1 = std::cbegin(src), iter2 =\
    \ iter1 + 1; iter2 != std::cend(src); iter2 += 2) {\n    if (*iter1 == *iter2)\n\
    \      ++res.back().second;\n    else\n      res.emplace_back(*iter2, 1);\n  \
    \  std::swap(iter1, iter2);\n  }\n  return res;\n}\n\n}  // namespace lib\n\n\
    #ifdef warn_not_defined\n#  undef warn\n#  undef warn_not_defined\n// warn may\
    \ be defined 2 times (by uncommenting line 17)\n#  ifdef warn\n#    undef warn\n\
    #  endif\n#endif\n\n#endif  // RUN_LENGTH_ENCODING_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/string/run_length_encoding.hpp
  requiredBy: []
  timestamp: '2021-08-03 15:55:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/string/run_length_encoding/1.test.cpp
documentation_of: include/string/run_length_encoding.hpp
layout: document
title: Run length encoding
---

[連長圧縮](https://ja.wikipedia.org/wiki/%E9%80%A3%E9%95%B7%E5%9C%A7%E7%B8%AE)を行う関数が定義されています。

---

### `run_length_encoding(S)`

`S` に対する連長圧縮の結果を返します。`S` として文字列だけではなく `std::vector<int>` 等のコンテナを渡すこともできます。

例えば `std::string` 型の値 `S` が `"aabbbccccd"` の時、`run_length_encoding(S)` の値は `std::vector<std::pair<char, int>>` 型の値 `{ ('a', 2) ('b', 3) ('c', 4) ('d', 1) }` となります。

空のコンテナを渡した場合、返り値の要素数は $0$ です。

---
