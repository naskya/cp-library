---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/algebra/eulers_totient_function/1.test.cpp
    title: test/algebra/eulers_totient_function/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/algebra/eulers_totient_function/2.test.cpp
    title: test/algebra/eulers_totient_function/2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Euler's totient function
    links: []
  bundledCode: "#line 1 \"include/algebra/eulers_totient_function.hpp\"\n\n//! @file\
    \ eulers_totient_function.hpp\n\n#ifndef CP_LIBRARY_EULERS_TOTIENT_FUNCTION_HPP\n\
    #define CP_LIBRARY_EULERS_TOTIENT_FUNCTION_HPP\n\n#include <numeric>\n#include\
    \ <type_traits>\n#include <vector>\n\nnamespace lib {\n\n//! @brief Euler's totient\
    \ function\n//! @tparam Tp return type (deduced from parameter)\n//! @param n\
    \ positive integer\n//! @return number of positive integers in [1, n] that are\
    \ coprime to n\n//! @note Time complexity: O(sqrt(n))\ntemplate <typename Tp>\n\
    [[nodiscard]] Tp totient_function(Tp n) {\n  Tp res = n;\n\n  using primitive_t\
    \ = std::conditional_t<std::is_integral_v<Tp>, Tp, long long>;\n\n  for (primitive_t\
    \ i = 2; i <= n / i; ++i) {\n    if (n % i == 0)\n      res -= res / i;\n    while\
    \ (n % i == 0)\n      n /= i;\n  }\n\n  if (n > 1)\n    res -= res / n;\n\n  return\
    \ res;\n}\n\n//! @brief Euler's totient function (from 1 to n)\n//! @tparam Tp\
    \ return type (deduced from parameter)\n//! @param n positive integer\n//! @return\
    \ a vector of length n+1 that contains 0, phi(1), phi(2), ..., phi(n) where phi\
    \ is Euler's totient function\n//! @note Time complexity: O(n log(log n))\ntemplate\
    \ <typename Tp>\n[[nodiscard]] std::vector<Tp> totient_function_sequence(Tp n)\
    \ {\n  std::vector<Tp> res(n + 1);\n  std::iota(std::begin(res), std::end(res),\
    \ (Tp) 0);\n\n  using primitive_t = std::conditional_t<std::is_integral_v<Tp>,\
    \ Tp, long long>;\n\n  for (primitive_t i = 2; i <= n; ++i) {\n    if (res[i]\
    \ == i) {\n      for (primitive_t j = i; j <= n; j += i) {\n        res[j] /=\
    \ i;\n        res[j] *= i - 1;\n      }\n    }\n  }\n\n  return res;\n}\n\n} \
    \ // namespace lib\n\n#endif  // CP_LIBRARY_EULERS_TOTIENT_FUNCTION_HPP\n"
  code: "\n//! @file eulers_totient_function.hpp\n\n#ifndef CP_LIBRARY_EULERS_TOTIENT_FUNCTION_HPP\n\
    #define CP_LIBRARY_EULERS_TOTIENT_FUNCTION_HPP\n\n#include <numeric>\n#include\
    \ <type_traits>\n#include <vector>\n\nnamespace lib {\n\n//! @brief Euler's totient\
    \ function\n//! @tparam Tp return type (deduced from parameter)\n//! @param n\
    \ positive integer\n//! @return number of positive integers in [1, n] that are\
    \ coprime to n\n//! @note Time complexity: O(sqrt(n))\ntemplate <typename Tp>\n\
    [[nodiscard]] Tp totient_function(Tp n) {\n  Tp res = n;\n\n  using primitive_t\
    \ = std::conditional_t<std::is_integral_v<Tp>, Tp, long long>;\n\n  for (primitive_t\
    \ i = 2; i <= n / i; ++i) {\n    if (n % i == 0)\n      res -= res / i;\n    while\
    \ (n % i == 0)\n      n /= i;\n  }\n\n  if (n > 1)\n    res -= res / n;\n\n  return\
    \ res;\n}\n\n//! @brief Euler's totient function (from 1 to n)\n//! @tparam Tp\
    \ return type (deduced from parameter)\n//! @param n positive integer\n//! @return\
    \ a vector of length n+1 that contains 0, phi(1), phi(2), ..., phi(n) where phi\
    \ is Euler's totient function\n//! @note Time complexity: O(n log(log n))\ntemplate\
    \ <typename Tp>\n[[nodiscard]] std::vector<Tp> totient_function_sequence(Tp n)\
    \ {\n  std::vector<Tp> res(n + 1);\n  std::iota(std::begin(res), std::end(res),\
    \ (Tp) 0);\n\n  using primitive_t = std::conditional_t<std::is_integral_v<Tp>,\
    \ Tp, long long>;\n\n  for (primitive_t i = 2; i <= n; ++i) {\n    if (res[i]\
    \ == i) {\n      for (primitive_t j = i; j <= n; j += i) {\n        res[j] /=\
    \ i;\n        res[j] *= i - 1;\n      }\n    }\n  }\n\n  return res;\n}\n\n} \
    \ // namespace lib\n\n#endif  // CP_LIBRARY_EULERS_TOTIENT_FUNCTION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/algebra/eulers_totient_function.hpp
  requiredBy: []
  timestamp: '2021-08-11 13:32:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/algebra/eulers_totient_function/1.test.cpp
  - test/algebra/eulers_totient_function/2.test.cpp
documentation_of: include/algebra/eulers_totient_function.hpp
layout: document
title: Euler's totient function
---

[Euler の $\varphi$ 関数](https://ja.wikipedia.org/wiki/%E3%82%AA%E3%82%A4%E3%83%A9%E3%83%BC%E3%81%AE%CF%86%E9%96%A2%E6%95%B0)が定義されています。

---

### `totient_function(n)`

$\varphi (n)$ の値、すなわち $n$ 以下の正整数のうち $n$ と互いに素であるものの個数を返します。

### `totient_function_sequence(n)`

$0, \varphi(1), \varphi(2), \ldots, \varphi(n-1), \varphi(n)$ が格納された、要素数 $n + 1$ の配列 ([`std::vector`](https://cpprefjp.github.io/reference/vector/vector.html)) を返します。

<!-- ToDo: totient_function_sum(n) \sum_{i = 1}^n \varphi(i) -->

---
