---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/combinatorics/factorial/1.test.cpp
    title: test/combinatorics/factorial/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/combinatorics/factorial/2.test.cpp
    title: test/combinatorics/factorial/2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Factorial, Permutation, Combination
    links: []
  bundledCode: "#line 1 \"include/combinatorics/factorial.hpp\"\n\n//! @file factorial.hpp\n\
    //! @brief Factorial, Permutation, Combination\n\n#ifndef FACTORIAL_HPP\n#define\
    \ FACTORIAL_HPP\n\n#include <array>\n#include <iostream>\n\n#ifndef warn\n//!\
    \ @brief Print warning message\n//! @note You can suppress the warning by uncommenting\
    \ line 15\n#  define warn(msg) (std::cerr << (msg) << '\\n')\n// #  define warn(msg)\
    \ (static_cast<void>(0))\n#  define warn_not_defined\n#endif\n\nnamespace lib\
    \ {\n\n//! @tparam Tp deduced from parameter\n//! @tparam ReturnType set appropriately\
    \ if there is a possibility of overflow (e.g. long long, __int128, modint)\n//!\
    \ @param n non-negative integer (doesn't have to be primitive)\n//! @return factorial\
    \ of n (n!), or number of ways to arrange n distinguishable objects in any order\n\
    //! @note Time complexity: O(n)\ntemplate <typename Tp, typename ReturnType =\
    \ Tp> ReturnType factorial(const Tp n) {\n  if (n < 0)\n    warn(\"n is negative.\"\
    );\n\n  ReturnType res = 1;\n  for (Tp i = 1; i <= n; ++i)\n    res *= i;\n  return\
    \ res;\n}\n\n//! @tparam Tp deduced from parameters\n//! @tparam ReturnType set\
    \ appropriately if there is a possibility of overflow (e.g. long long, __int128,\
    \ modint)\n//! @param n non-negative integer (doesn't have to be primitive)\n\
    //! @param r non-negative integer (doesn't have to be primitive)\n//! @return\
    \ nPr, or number of ways to select r out of n distinguishable objects and arrange\
    \ them in any order\n//! @note Time complexity: O(r)\ntemplate <typename Tp, typename\
    \ ReturnType = Tp>\n[[nodiscard]] ReturnType permutation(const Tp n, const Tp\
    \ r) {\n  if (n == 0)\n    warn(\"n is zero.\");\n  if (n < 0) {\n    warn(\"\
    n is negative.\");\n    return 0;\n  }\n  if (r < 0) {\n    warn(\"r is negative.\"\
    );\n    return 0;\n  }\n  if (n < r) {\n    warn(\"n is less than r.\");\n   \
    \ return 0;\n  }\n  ReturnType res = 1;\n  for (Tp i = n - r + 1; i <= n; ++i)\n\
    \    res *= i;\n  return res;\n}\n\n//! @tparam Tp deduced from parameters\n//!\
    \ @tparam ReturnType set appropriately if there is a possibility of overflow (e.g.\
    \ long long, __int128, modint)\n//! @param n non-negative integer (doesn't have\
    \ to be primitive)\n//! @param r non-negative integer (doesn't have to be primitive)\n\
    //! @return nCr, or number of ways to select r out of n distinguishable objects\n\
    //! @note Time complexity: O(r)\ntemplate <typename Tp, typename ReturnType =\
    \ Tp>\n[[nodiscard]] ReturnType combination(const Tp n, const Tp r) {\n  if (n\
    \ == 0)\n    warn(\"n is zero.\");\n  if (n < 0) {\n    warn(\"n is negative.\"\
    );\n    return 0;\n  }\n  if (r < 0) {\n    warn(\"r is negative.\");\n    return\
    \ 0;\n  }\n  if (n < r) {\n    warn(\"n is less than r.\");\n    return 0;\n \
    \ }\n  ReturnType res = 1;\n  for (Tp i = 1; i <= r; ++i) {\n    res *= (n - r\
    \ + i);\n    res /= i;\n  }\n  return res;\n}\n\n//! @tparam Max upper limit\n\
    //! @tparam ReturnType value type\n//! @return std::array which contains 0!, 1!,\
    \ ..., Max! (Max + 1 numbers)\n//! @note Time complexity: O(Max)\ntemplate <unsigned\
    \ Max, typename ReturnType>\n[[nodiscard]] constexpr std::array<ReturnType, Max\
    \ + 1> factorial_array() {\n  std::array<ReturnType, Max + 1> res;\n  res[0] =\
    \ 1;\n\n  for (unsigned i = 1; i <= Max; ++i)\n    res[i] = res[i - 1] * i;\n\n\
    \  return res;\n}\n\n//! @tparam Max upper limit\n//! @tparam Modint value type\
    \ (deduced from parameter, must be Modint)\n//! @param fact factorial of Max (which\
    \ is the result of factorial or factorial_array)\n//! @return std::array which\
    \ contains multiplicative inverse of 0!, 1!, ..., Max! (Max + 1 numbers)\n//!\
    \ @note nPr = factorial[n] * factorial_modinv[n - r]\n//! @note nCr = factorial[n]\
    \ * factorial_modinv[n - r] * factorial_modinv[r]\n//! @note Time complexity:\
    \ O(Max)\ntemplate <unsigned Max, typename Modint>\n[[nodiscard]] constexpr std::array<Modint,\
    \ Max + 1> factorial_modinv_array(const Modint fact) {\n  std::array<Modint, Max\
    \ + 1> res;\n  res[Max] = fact.inv();\n\n  for (unsigned i = Max; i > 0; --i)\n\
    \    res[i - 1] = res[i] * i;\n\n  return res;\n}\n\n}  // namespace lib\n\n#ifdef\
    \ warn_not_defined\n#  undef warn\n#  undef warn_not_defined\n#endif\n\n#endif\n"
  code: "\n//! @file factorial.hpp\n//! @brief Factorial, Permutation, Combination\n\
    \n#ifndef FACTORIAL_HPP\n#define FACTORIAL_HPP\n\n#include <array>\n#include <iostream>\n\
    \n#ifndef warn\n//! @brief Print warning message\n//! @note You can suppress the\
    \ warning by uncommenting line 15\n#  define warn(msg) (std::cerr << (msg) <<\
    \ '\\n')\n// #  define warn(msg) (static_cast<void>(0))\n#  define warn_not_defined\n\
    #endif\n\nnamespace lib {\n\n//! @tparam Tp deduced from parameter\n//! @tparam\
    \ ReturnType set appropriately if there is a possibility of overflow (e.g. long\
    \ long, __int128, modint)\n//! @param n non-negative integer (doesn't have to\
    \ be primitive)\n//! @return factorial of n (n!), or number of ways to arrange\
    \ n distinguishable objects in any order\n//! @note Time complexity: O(n)\ntemplate\
    \ <typename Tp, typename ReturnType = Tp> ReturnType factorial(const Tp n) {\n\
    \  if (n < 0)\n    warn(\"n is negative.\");\n\n  ReturnType res = 1;\n  for (Tp\
    \ i = 1; i <= n; ++i)\n    res *= i;\n  return res;\n}\n\n//! @tparam Tp deduced\
    \ from parameters\n//! @tparam ReturnType set appropriately if there is a possibility\
    \ of overflow (e.g. long long, __int128, modint)\n//! @param n non-negative integer\
    \ (doesn't have to be primitive)\n//! @param r non-negative integer (doesn't have\
    \ to be primitive)\n//! @return nPr, or number of ways to select r out of n distinguishable\
    \ objects and arrange them in any order\n//! @note Time complexity: O(r)\ntemplate\
    \ <typename Tp, typename ReturnType = Tp>\n[[nodiscard]] ReturnType permutation(const\
    \ Tp n, const Tp r) {\n  if (n == 0)\n    warn(\"n is zero.\");\n  if (n < 0)\
    \ {\n    warn(\"n is negative.\");\n    return 0;\n  }\n  if (r < 0) {\n    warn(\"\
    r is negative.\");\n    return 0;\n  }\n  if (n < r) {\n    warn(\"n is less than\
    \ r.\");\n    return 0;\n  }\n  ReturnType res = 1;\n  for (Tp i = n - r + 1;\
    \ i <= n; ++i)\n    res *= i;\n  return res;\n}\n\n//! @tparam Tp deduced from\
    \ parameters\n//! @tparam ReturnType set appropriately if there is a possibility\
    \ of overflow (e.g. long long, __int128, modint)\n//! @param n non-negative integer\
    \ (doesn't have to be primitive)\n//! @param r non-negative integer (doesn't have\
    \ to be primitive)\n//! @return nCr, or number of ways to select r out of n distinguishable\
    \ objects\n//! @note Time complexity: O(r)\ntemplate <typename Tp, typename ReturnType\
    \ = Tp>\n[[nodiscard]] ReturnType combination(const Tp n, const Tp r) {\n  if\
    \ (n == 0)\n    warn(\"n is zero.\");\n  if (n < 0) {\n    warn(\"n is negative.\"\
    );\n    return 0;\n  }\n  if (r < 0) {\n    warn(\"r is negative.\");\n    return\
    \ 0;\n  }\n  if (n < r) {\n    warn(\"n is less than r.\");\n    return 0;\n \
    \ }\n  ReturnType res = 1;\n  for (Tp i = 1; i <= r; ++i) {\n    res *= (n - r\
    \ + i);\n    res /= i;\n  }\n  return res;\n}\n\n//! @tparam Max upper limit\n\
    //! @tparam ReturnType value type\n//! @return std::array which contains 0!, 1!,\
    \ ..., Max! (Max + 1 numbers)\n//! @note Time complexity: O(Max)\ntemplate <unsigned\
    \ Max, typename ReturnType>\n[[nodiscard]] constexpr std::array<ReturnType, Max\
    \ + 1> factorial_array() {\n  std::array<ReturnType, Max + 1> res;\n  res[0] =\
    \ 1;\n\n  for (unsigned i = 1; i <= Max; ++i)\n    res[i] = res[i - 1] * i;\n\n\
    \  return res;\n}\n\n//! @tparam Max upper limit\n//! @tparam Modint value type\
    \ (deduced from parameter, must be Modint)\n//! @param fact factorial of Max (which\
    \ is the result of factorial or factorial_array)\n//! @return std::array which\
    \ contains multiplicative inverse of 0!, 1!, ..., Max! (Max + 1 numbers)\n//!\
    \ @note nPr = factorial[n] * factorial_modinv[n - r]\n//! @note nCr = factorial[n]\
    \ * factorial_modinv[n - r] * factorial_modinv[r]\n//! @note Time complexity:\
    \ O(Max)\ntemplate <unsigned Max, typename Modint>\n[[nodiscard]] constexpr std::array<Modint,\
    \ Max + 1> factorial_modinv_array(const Modint fact) {\n  std::array<Modint, Max\
    \ + 1> res;\n  res[Max] = fact.inv();\n\n  for (unsigned i = Max; i > 0; --i)\n\
    \    res[i - 1] = res[i] * i;\n\n  return res;\n}\n\n}  // namespace lib\n\n#ifdef\
    \ warn_not_defined\n#  undef warn\n#  undef warn_not_defined\n#endif\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: include/combinatorics/factorial.hpp
  requiredBy: []
  timestamp: '2021-07-29 12:37:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/combinatorics/factorial/1.test.cpp
  - test/combinatorics/factorial/2.test.cpp
documentation_of: include/combinatorics/factorial.hpp
layout: document
title: Factorial, Permutation, Combination
---

階乗を計算する関数・順列の数を計算する関数・二項係数を計算する関数が定義されています。

---

### `factorial(n)`

$n$ の階乗 ($n!$) を返します。

### `permutation(n, r)`

$n$ 個の区別できるものの中から $r$ 個を選んで任意の順番で横一列に並べるとき、考えられる並べ方の数 (${}_nP_r$) を返します。

### `combination(n, r)`

$n$ 個の区別できるものの中から $r$ 個を選ぶとき、考えられる選び方の数 (${}_nC_r$) を返します。

## `factorial_array<N, type>()`

$0$ から $N$ までの階乗が入った長さ $N + 1$ の `type` 型の配列 (`std::array`) を返します。

## `factorial_modinv_array<N, modint_type>(x)`

`modint_type` には [`static_modint`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) または [`dynamic_modint`](https://naskya.github.io/cp-library/include/algebra/dynamic_modint.hpp) または類似の型が指定できます。$x$ として $N$ の階乗 ($N!$) を与えると、$0$ から $N$ までの階乗の `modint_type` 型における乗法の逆元が入った長さ $N + 1$ の `modint_type` 型の配列 (`std::array`) を返します。

`factorial_array` と `factorial_modinv_array` を用いると、時間計算量 $\Theta(N)$ の前計算を行うことで ${}_nC_r$ や ${}_nP_r$ の値を $\Theta(1)$ の時間計算量で求めることができるようになります。

```cpp
using mint = lib::static_modint<1000000007>;
constexpr int N = 100000;

const auto fact     = lib::factorial_array<N, mint>();
const auto fact_inv = lib::factorial_modinv_array<N, mint>(fact.back());

assert(lib::permutation(n, r) == fact[n] * fact_inv[n - r]);
assert(lib::combination(n, r) == fact[n] * fact_inv[n - r] * fact_inv[r]);
```
