---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/search/golden_ratio_search/1.test.cpp
    title: test/search/golden_ratio_search/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/search/golden_ratio_search/2.test.cpp
    title: test/search/golden_ratio_search/2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Assert macro
    links: []
  bundledCode: "#line 1 \"include/search/golden_ratio_search.hpp\"\n\n//! @file golden_ratio_search.hpp\n\
    \n#ifndef GOLDEN_RATIO_SEARCH_HPP\n#define GOLDEN_RATIO_SEARCH_HPP\n\n#include\
    \ <cassert>\n#include <cmath>\n#include <type_traits>\n#include <utility>\n\n\
    #ifndef O_assert\n//! @brief Assert macro\n#  define O_assert(...) assert(__VA_ARGS__)\n\
    #  define O_assert_not_defined\n#endif\n\nnamespace lib {\n\n//! @brief Function\
    \ to find the maximum or minimum value of a convex function f(x) when x is in\
    \ [a, b]\n//! @tparam minimize Set to true if you want to minimize the f(x), otherwise\
    \ set to false.\n//! @tparam RealType type of x (deduced from parameters)\n//!\
    \ @tparam Func type of f (deduced from parameters)\n//! @param low lower bound\
    \ (a)\n//! @param high upper bound (b)\n//! @param f function to minimize or maximize\n\
    //! @param diff acceptable error\n//! @return std::pair { argmin(f(x)), min(f(x))\
    \ } (or argmax & max)\n//! @note time complexity: O(log((high - low) / diff *\
    \ (time needed to calculate f(x))))\ntemplate <bool minimize, typename RealType,\
    \ typename Func>\n[[nodiscard]] auto golden_ratio_search(RealType low, RealType\
    \ high, const Func& f, const RealType diff = 1e-9L) {\n  using F_ResType = decltype(f(std::declval<RealType>()));\n\
    \  O_assert(low <= high);\n\n  using std::sqrt;\n  const RealType phi        =\
    \ (1 + sqrt(RealType(5.0L))) / 2;\n  const RealType phi_plus_1 = phi + 1;\n\n\
    \  RealType mid_low     = (low * phi + high) / phi_plus_1;\n  RealType mid_high\
    \    = (low + high * phi) / phi_plus_1;\n  F_ResType score_low  = f(mid_low);\n\
    \  F_ResType score_high = f(mid_high);\n\n  while (high - low > diff) {\n    if\
    \ (minimize ^ (score_low < score_high)) {\n      low        = mid_low;\n     \
    \ mid_low    = mid_high;\n      score_low  = score_high;\n      mid_high   = (low\
    \ + high * phi) / phi_plus_1;\n      score_high = f(mid_high);\n    } else {\n\
    \      high       = mid_high;\n      mid_high   = mid_low;\n      score_high =\
    \ score_low;\n      mid_low    = (low * phi + high) / phi_plus_1;\n      score_low\
    \  = f(mid_low);\n    }\n  }\n\n  return std::pair {low, score_low};\n}\n\n} \
    \ // namespace lib\n\n#ifdef O_assert_not_defined\n#  undef O_assert\n#  undef\
    \ O_assert_not_defined\n#endif\n\n#endif  // GOLDEN_RATIO_SEARCH_HPP\n"
  code: "\n//! @file golden_ratio_search.hpp\n\n#ifndef GOLDEN_RATIO_SEARCH_HPP\n\
    #define GOLDEN_RATIO_SEARCH_HPP\n\n#include <cassert>\n#include <cmath>\n#include\
    \ <type_traits>\n#include <utility>\n\n#ifndef O_assert\n//! @brief Assert macro\n\
    #  define O_assert(...) assert(__VA_ARGS__)\n#  define O_assert_not_defined\n\
    #endif\n\nnamespace lib {\n\n//! @brief Function to find the maximum or minimum\
    \ value of a convex function f(x) when x is in [a, b]\n//! @tparam minimize Set\
    \ to true if you want to minimize the f(x), otherwise set to false.\n//! @tparam\
    \ RealType type of x (deduced from parameters)\n//! @tparam Func type of f (deduced\
    \ from parameters)\n//! @param low lower bound (a)\n//! @param high upper bound\
    \ (b)\n//! @param f function to minimize or maximize\n//! @param diff acceptable\
    \ error\n//! @return std::pair { argmin(f(x)), min(f(x)) } (or argmax & max)\n\
    //! @note time complexity: O(log((high - low) / diff * (time needed to calculate\
    \ f(x))))\ntemplate <bool minimize, typename RealType, typename Func>\n[[nodiscard]]\
    \ auto golden_ratio_search(RealType low, RealType high, const Func& f, const RealType\
    \ diff = 1e-9L) {\n  using F_ResType = decltype(f(std::declval<RealType>()));\n\
    \  O_assert(low <= high);\n\n  using std::sqrt;\n  const RealType phi        =\
    \ (1 + sqrt(RealType(5.0L))) / 2;\n  const RealType phi_plus_1 = phi + 1;\n\n\
    \  RealType mid_low     = (low * phi + high) / phi_plus_1;\n  RealType mid_high\
    \    = (low + high * phi) / phi_plus_1;\n  F_ResType score_low  = f(mid_low);\n\
    \  F_ResType score_high = f(mid_high);\n\n  while (high - low > diff) {\n    if\
    \ (minimize ^ (score_low < score_high)) {\n      low        = mid_low;\n     \
    \ mid_low    = mid_high;\n      score_low  = score_high;\n      mid_high   = (low\
    \ + high * phi) / phi_plus_1;\n      score_high = f(mid_high);\n    } else {\n\
    \      high       = mid_high;\n      mid_high   = mid_low;\n      score_high =\
    \ score_low;\n      mid_low    = (low * phi + high) / phi_plus_1;\n      score_low\
    \  = f(mid_low);\n    }\n  }\n\n  return std::pair {low, score_low};\n}\n\n} \
    \ // namespace lib\n\n#ifdef O_assert_not_defined\n#  undef O_assert\n#  undef\
    \ O_assert_not_defined\n#endif\n\n#endif  // GOLDEN_RATIO_SEARCH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/search/golden_ratio_search.hpp
  requiredBy: []
  timestamp: '2021-08-04 05:43:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/search/golden_ratio_search/1.test.cpp
  - test/search/golden_ratio_search/2.test.cpp
documentation_of: include/search/golden_ratio_search.hpp
layout: document
title: Golden ratio search
---

[黄金分割探索](https://ja.wikipedia.org/wiki/%E9%BB%84%E9%87%91%E5%88%86%E5%89%B2%E6%8E%A2%E7%B4%A2)によって凸関数の区間内の最小値(または最大値)とそれを達成する引数を求める関数が定義されています。

---

### `golden_ratio_search<true>(a, b, f, diff)`

区間 $I = [a, b]$ で定義される凸関数 $f: I \to \mathbf{R}$ に対して $\displaystyle\argmin_{x \in I} f(x)$ と $\displaystyle\min_{x \in I} f(x)$ をこの順番で持つ `std::pair` 型の値を返します。

`diff` は $\argmin$ に対する許容誤差です。

### `golden_ratio_search<false>(a, b, f, diff)`

区間 $I = [a, b]$ で定義される凸関数 $f: I \to \mathbf{R}$ に対して $\displaystyle\argmax_{x \in I} f(x)$ と $\displaystyle\max_{x \in I} f(x)$ をこの順番で持つ `std::pair` 型の値を返します。

`diff` は $\argmax$ に対する許容誤差です。

---
