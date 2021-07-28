---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/string/z_algorithm/1.test.cpp
    title: test/string/z_algorithm/1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Z algorithm
    links: []
  bundledCode: "#line 1 \"include/string/z_algorithm.hpp\"\n\n//! @file z_algorithm.hpp\n\
    //! @brief Z algorithm\n//! @details Provide a function to calculate the length\
    \ of the longest common prefix.\n\n#ifndef Z_ALGORITHM_HPP\n#define Z_ALGORITHM_HPP\n\
    \n#include <iterator>\n#include <vector>\n\nnamespace lib {\n\n//! @tparam Container\
    \ container type (deduced by parameter). operator[] and size(Container) must be\
    \ defined.\n//! @param src Source (container)\n//! @return Vector contains the\
    \ length of the longest common prefix\n//! @note Time complexity: O(size(s))\n\
    template <typename Container>\n[[nodiscard]] std::vector<int> z_algorithm(const\
    \ Container& src) {\n  const int size = static_cast<int>(std::size(src));\n\n\
    \  std::vector<int> res(size);\n  res[0] = size;\n\n  for (int i = 1, l = 0, r\
    \ = 0; i < size; ++i) {\n    if (i <= r) {\n      res[i] = std::min(r - i + 1,\
    \ res[i - l]);\n    }\n    while (i + res[i] < size && src[i + res[i]] == src[res[i]])\
    \ {\n      ++res[i];\n    }\n    if (i + res[i] - 1 > r) {\n      l = i;\n   \
    \   r = i + res[i] - 1;\n    }\n  }\n\n  return res;\n}\n\n}  // namespace lib\n\
    \n#endif  // Z_ALGORITHM_HPP\n"
  code: "\n//! @file z_algorithm.hpp\n//! @brief Z algorithm\n//! @details Provide\
    \ a function to calculate the length of the longest common prefix.\n\n#ifndef\
    \ Z_ALGORITHM_HPP\n#define Z_ALGORITHM_HPP\n\n#include <iterator>\n#include <vector>\n\
    \nnamespace lib {\n\n//! @tparam Container container type (deduced by parameter).\
    \ operator[] and size(Container) must be defined.\n//! @param src Source (container)\n\
    //! @return Vector contains the length of the longest common prefix\n//! @note\
    \ Time complexity: O(size(s))\ntemplate <typename Container>\n[[nodiscard]] std::vector<int>\
    \ z_algorithm(const Container& src) {\n  const int size = static_cast<int>(std::size(src));\n\
    \n  std::vector<int> res(size);\n  res[0] = size;\n\n  for (int i = 1, l = 0,\
    \ r = 0; i < size; ++i) {\n    if (i <= r) {\n      res[i] = std::min(r - i +\
    \ 1, res[i - l]);\n    }\n    while (i + res[i] < size && src[i + res[i]] == src[res[i]])\
    \ {\n      ++res[i];\n    }\n    if (i + res[i] - 1 > r) {\n      l = i;\n   \
    \   r = i + res[i] - 1;\n    }\n  }\n\n  return res;\n}\n\n}  // namespace lib\n\
    \n#endif  // Z_ALGORITHM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/string/z_algorithm.hpp
  requiredBy: []
  timestamp: '2021-07-28 15:32:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/string/z_algorithm/1.test.cpp
documentation_of: include/string/z_algorithm.hpp
layout: document
redirect_from:
- /library/include/string/z_algorithm.hpp
- /library/include/string/z_algorithm.hpp.html
title: Z algorithm
---
