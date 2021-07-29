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
    document_title: Binary search
    links: []
  bundledCode: "#line 1 \"include/search/binary_search.hpp\"\n\n//! @file binary_search.hpp\n\
    //! @brief Binary search\n\n#ifndef BINARY_SEARCH_HPP\n#define BINARY_SEARCH_HPP\n\
    \n#include <cassert>\n#include <type_traits>\n#include <utility>\n\n#ifndef O_assert\n\
    //! @brief Assert macro\n#  define O_assert(...) assert(__VA_ARGS__)\n#  define\
    \ O_assert_not_defined\n#endif\n\nnamespace lib {\n\n//! @brief Find the minimum\
    \ or maximum value that satisfies the condition.\n//! @tparam Tp Return type (deduced\
    \ from parameters)\n//! @tparam Func callable type (function reference, class\
    \ with operator(), ...)\n//! @param ok Initial value for which the condition is\
    \ satisfied\n//! @param ng Initial value for which the condition is not satisfied\n\
    //! @param f Callable object that takes 1 parameter of Tp and returns bool indicating\
    \ if the condition is satisfied\n//! @param diff Difference (end condition of\
    \ binary search). 1 for integers, small value (e.g. 1e-9) for real numbers\n//!\
    \ @return minimum value (if ok < ng) or maximum value (if ok > ng)\n//! @note\
    \ One and only one boundary value between ok and ng must exist.\n//! @note Time\
    \ complexity: O(log(|ok - ng|))\ntemplate <typename Tp, typename Func>\n[[nodiscard]]\
    \ Tp binary_search(Tp ok, Tp ng, const Func& f, const Tp diff = 1) {\n  static_assert(std::is_same_v<decltype(std::declval<Func>()(std::declval<Tp>())),\
    \ bool>);\n  O_assert(f(ok) && !f(ng));\n\n  if (ok < ng)\n    while (ng - ok\
    \ > diff) {\n      const Tp mid       = ok + (ng - ok) / 2;\n      (f(mid) ? ok\
    \ : ng) = mid;\n    }\n  else\n    while (ok - ng > diff) {\n      const Tp mid\
    \       = ng + (ok - ng) / 2;\n      (f(mid) ? ok : ng) = mid;\n    }\n\n  return\
    \ ok;\n}\n\n}  // namespace lib\n\n#ifdef O_assert_not_defined\n#  undef O_assert\n\
    #  undef O_assert_not_defined\n#endif\n\n#endif  // BINARY_SEARCH_HPP\n"
  code: "\n//! @file binary_search.hpp\n//! @brief Binary search\n\n#ifndef BINARY_SEARCH_HPP\n\
    #define BINARY_SEARCH_HPP\n\n#include <cassert>\n#include <type_traits>\n#include\
    \ <utility>\n\n#ifndef O_assert\n//! @brief Assert macro\n#  define O_assert(...)\
    \ assert(__VA_ARGS__)\n#  define O_assert_not_defined\n#endif\n\nnamespace lib\
    \ {\n\n//! @brief Find the minimum or maximum value that satisfies the condition.\n\
    //! @tparam Tp Return type (deduced from parameters)\n//! @tparam Func callable\
    \ type (function reference, class with operator(), ...)\n//! @param ok Initial\
    \ value for which the condition is satisfied\n//! @param ng Initial value for\
    \ which the condition is not satisfied\n//! @param f Callable object that takes\
    \ 1 parameter of Tp and returns bool indicating if the condition is satisfied\n\
    //! @param diff Difference (end condition of binary search). 1 for integers, small\
    \ value (e.g. 1e-9) for real numbers\n//! @return minimum value (if ok < ng) or\
    \ maximum value (if ok > ng)\n//! @note One and only one boundary value between\
    \ ok and ng must exist.\n//! @note Time complexity: O(log(|ok - ng|))\ntemplate\
    \ <typename Tp, typename Func>\n[[nodiscard]] Tp binary_search(Tp ok, Tp ng, const\
    \ Func& f, const Tp diff = 1) {\n  static_assert(std::is_same_v<decltype(std::declval<Func>()(std::declval<Tp>())),\
    \ bool>);\n  O_assert(f(ok) && !f(ng));\n\n  if (ok < ng)\n    while (ng - ok\
    \ > diff) {\n      const Tp mid       = ok + (ng - ok) / 2;\n      (f(mid) ? ok\
    \ : ng) = mid;\n    }\n  else\n    while (ok - ng > diff) {\n      const Tp mid\
    \       = ng + (ok - ng) / 2;\n      (f(mid) ? ok : ng) = mid;\n    }\n\n  return\
    \ ok;\n}\n\n}  // namespace lib\n\n#ifdef O_assert_not_defined\n#  undef O_assert\n\
    #  undef O_assert_not_defined\n#endif\n\n#endif  // BINARY_SEARCH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/search/binary_search.hpp
  requiredBy: []
  timestamp: '2021-07-28 19:20:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/search/binary_search/3.test.cpp
  - test/search/binary_search/1.test.cpp
  - test/search/binary_search/2.test.cpp
documentation_of: include/search/binary_search.hpp
layout: document
redirect_from:
- /library/include/search/binary_search.hpp
- /library/include/search/binary_search.hpp.html
title: Binary search
---
