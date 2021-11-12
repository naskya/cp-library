---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/search/binary_search/1.test.cpp
    title: test/search/binary_search/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/search/binary_search/2.test.cpp
    title: test/search/binary_search/2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/search/binary_search/3.test.cpp
    title: test/search/binary_search/3.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Assert macro
    links: []
  bundledCode: "#line 1 \"include/search/binary_search.hpp\"\n\n//! @file binary_search.hpp\n\
    \n#ifndef CP_LIBRARY_BINARY_SEARCH_HPP\n#define CP_LIBRARY_BINARY_SEARCH_HPP\n\
    \n#include <cassert>\n#include <type_traits>\n#include <utility>\n\n#ifndef CP_LIBRARY_ASSERT\n\
    //! @brief Assert macro\n#  define CP_LIBRARY_ASSERT(...) assert(__VA_ARGS__)\n\
    #  define CP_LIBRARY_ASSERT_NOT_DEFINED\n#endif\n\nnamespace lib {\n\n//! @brief\
    \ Find the minimum or maximum value that satisfies the condition.\n//! @tparam\
    \ Tp Return type (deduced from parameters)\n//! @tparam Func callable type (function\
    \ reference, class with operator(), ...)\n//! @param ok Initial value for which\
    \ the condition is satisfied\n//! @param ng Initial value for which the condition\
    \ is not satisfied\n//! @param f Callable object that takes 1 parameter of Tp\
    \ and returns bool indicating if the condition is satisfied\n//! @param diff Difference\
    \ (end condition of binary search). 1 for integers, small value (e.g. 1e-9) for\
    \ real numbers\n//! @return minimum value (if ok < ng) or maximum value (if ok\
    \ > ng)\n//! @note One and only one boundary value between ok and ng must exist.\n\
    //! @note Time complexity: O(log(|ok - ng|))\ntemplate <typename Tp, typename\
    \ Func>\n[[nodiscard]] Tp binary_search(Tp ok, Tp ng, const Func& f, const Tp\
    \ diff = 1) {\n  static_assert(std::is_same_v<decltype(std::declval<Func>()(std::declval<Tp>())),\
    \ bool>);\n  CP_LIBRARY_ASSERT(f(ok));\n  CP_LIBRARY_ASSERT(!f(ng));\n\n  if (ok\
    \ < ng)\n    while (ng - ok > diff) {\n      const Tp mid       = ok + (ng - ok)\
    \ / 2;\n      (f(mid) ? ok : ng) = mid;\n    }\n  else\n    while (ok - ng > diff)\
    \ {\n      const Tp mid       = ng + (ok - ng) / 2;\n      (f(mid) ? ok : ng)\
    \ = mid;\n    }\n\n  return ok;\n}\n\n}  // namespace lib\n\n#ifdef CP_LIBRARY_ASSERT_NOT_DEFINED\n\
    #  undef CP_LIBRARY_ASSERT\n#  undef CP_LIBRARY_ASSERT_NOT_DEFINED\n#endif\n\n\
    #endif  // CP_LIBRARY_BINARY_SEARCH_HPP\n"
  code: "\n//! @file binary_search.hpp\n\n#ifndef CP_LIBRARY_BINARY_SEARCH_HPP\n#define\
    \ CP_LIBRARY_BINARY_SEARCH_HPP\n\n#include <cassert>\n#include <type_traits>\n\
    #include <utility>\n\n#ifndef CP_LIBRARY_ASSERT\n//! @brief Assert macro\n#  define\
    \ CP_LIBRARY_ASSERT(...) assert(__VA_ARGS__)\n#  define CP_LIBRARY_ASSERT_NOT_DEFINED\n\
    #endif\n\nnamespace lib {\n\n//! @brief Find the minimum or maximum value that\
    \ satisfies the condition.\n//! @tparam Tp Return type (deduced from parameters)\n\
    //! @tparam Func callable type (function reference, class with operator(), ...)\n\
    //! @param ok Initial value for which the condition is satisfied\n//! @param ng\
    \ Initial value for which the condition is not satisfied\n//! @param f Callable\
    \ object that takes 1 parameter of Tp and returns bool indicating if the condition\
    \ is satisfied\n//! @param diff Difference (end condition of binary search). 1\
    \ for integers, small value (e.g. 1e-9) for real numbers\n//! @return minimum\
    \ value (if ok < ng) or maximum value (if ok > ng)\n//! @note One and only one\
    \ boundary value between ok and ng must exist.\n//! @note Time complexity: O(log(|ok\
    \ - ng|))\ntemplate <typename Tp, typename Func>\n[[nodiscard]] Tp binary_search(Tp\
    \ ok, Tp ng, const Func& f, const Tp diff = 1) {\n  static_assert(std::is_same_v<decltype(std::declval<Func>()(std::declval<Tp>())),\
    \ bool>);\n  CP_LIBRARY_ASSERT(f(ok));\n  CP_LIBRARY_ASSERT(!f(ng));\n\n  if (ok\
    \ < ng)\n    while (ng - ok > diff) {\n      const Tp mid       = ok + (ng - ok)\
    \ / 2;\n      (f(mid) ? ok : ng) = mid;\n    }\n  else\n    while (ok - ng > diff)\
    \ {\n      const Tp mid       = ng + (ok - ng) / 2;\n      (f(mid) ? ok : ng)\
    \ = mid;\n    }\n\n  return ok;\n}\n\n}  // namespace lib\n\n#ifdef CP_LIBRARY_ASSERT_NOT_DEFINED\n\
    #  undef CP_LIBRARY_ASSERT\n#  undef CP_LIBRARY_ASSERT_NOT_DEFINED\n#endif\n\n\
    #endif  // CP_LIBRARY_BINARY_SEARCH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/search/binary_search.hpp
  requiredBy: []
  timestamp: '2021-11-12 22:57:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/search/binary_search/2.test.cpp
  - test/search/binary_search/1.test.cpp
  - test/search/binary_search/3.test.cpp
documentation_of: include/search/binary_search.hpp
layout: document
title: Binary search
---

[二分探索](https://ja.wikipedia.org/wiki/%E4%BA%8C%E5%88%86%E6%8E%A2%E7%B4%A2)をする関数が定義されています。

---

### `binary_search(ok, ng, f, diff)`

#### 引数

- `ok` - `f(ok)` が真となる十分大きい(または十分小さい)値
- `ng` - `f(ng)` が偽となる十分小さい(または十分大きい)値
- `f` - `f(x)` というコードで呼び出せて、`bool` 型の値を返すもの(関数への参照, `operator()` が定義されているクラスのオブジェクト 等)
- `diff` - 整数値の二分探索では $1$、実数値の二分探索では許容誤差 ($10^{-9}$ など)

#### 戻り値

`ok` と `ng` の間の値で、`f(x)` が真となるギリギリの値

より厳密に言うと `ok` と `ng` の中間の値 `mid` で `f(mid)` を呼び出し、結果が真なら `ok = mid` と、偽なら `ng = mid` とすることを繰り返して探索範囲を狭めていき、`ok` と `ng` の差が `diff` 以下になった時の `ok` の値を返します。

---
