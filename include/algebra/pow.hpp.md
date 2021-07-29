---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/algebra/pow/1.test.cpp
    title: test/algebra/pow/1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"include/algebra/pow.hpp\"\n\n//! @file pow.hpp\n\n#ifndef\
    \ POW_HPP\n#define POW_HPP\n\nnamespace lib {\n\n//! @tparam ValueType base type\
    \ (deduced from parameter).\n//! @tparam IntType index type (deduced from parameter).\n\
    //! @param base base. This doesn't have to be an integer.\n//! @param index index.\
    \ This must be an integer, but doesn't have to be primitive.\n//! @param id multiplicative\
    \ identity\n//! @return the index-th power of base\n//! @note Time complexity:\
    \ O(log(index) * (time needed to calculate (base * base)))\ntemplate <typename\
    \ ValueType, typename IntType>\n[[nodiscard]] ValueType pow(ValueType base, IntType\
    \ index, ValueType id = 1) {\n  // Use id as result in this function\n  while\
    \ (index != 0) {\n    if ((index & 1) == 1)\n      id *= base;\n    base *= base;\n\
    \    index >>= 1;\n  }\n  return id;\n}\n\n}  // namespace lib\n\n#endif  // POW_HPP\n"
  code: "\n//! @file pow.hpp\n\n#ifndef POW_HPP\n#define POW_HPP\n\nnamespace lib\
    \ {\n\n//! @tparam ValueType base type (deduced from parameter).\n//! @tparam\
    \ IntType index type (deduced from parameter).\n//! @param base base. This doesn't\
    \ have to be an integer.\n//! @param index index. This must be an integer, but\
    \ doesn't have to be primitive.\n//! @param id multiplicative identity\n//! @return\
    \ the index-th power of base\n//! @note Time complexity: O(log(index) * (time\
    \ needed to calculate (base * base)))\ntemplate <typename ValueType, typename\
    \ IntType>\n[[nodiscard]] ValueType pow(ValueType base, IntType index, ValueType\
    \ id = 1) {\n  // Use id as result in this function\n  while (index != 0) {\n\
    \    if ((index & 1) == 1)\n      id *= base;\n    base *= base;\n    index >>=\
    \ 1;\n  }\n  return id;\n}\n\n}  // namespace lib\n\n#endif  // POW_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/algebra/pow.hpp
  requiredBy: []
  timestamp: '2021-07-30 01:41:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/algebra/pow/1.test.cpp
documentation_of: include/algebra/pow.hpp
layout: document
title: Binary exponentation
---

二分累乗法によって冪乗を対数時間で計算する関数が定義されています。

## `pow(a, b, e = 1)`

乗法の単位元を $e$ として、$a^b$ を返します。
