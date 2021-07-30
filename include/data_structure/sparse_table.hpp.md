---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structure/sparse_table/1.test.cpp
    title: test/data_structure/sparse_table/1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Assert macro
    links: []
  bundledCode: "#line 1 \"include/data_structure/sparse_table.hpp\"\n\n//! @file sparse_table.hpp\n\
    //! @details Provide a data structure to calculate interval products of associative\
    \ and idempotent operations.\n\n#ifndef SPARSE_TABLE_HPP\n#define SPARSE_TABLE_HPP\n\
    \n#include <cassert>\n#include <limits>\n#include <type_traits>\n#include <vector>\n\
    \n#ifndef O_assert\n//! @brief Assert macro\n#  define O_assert(...) assert(__VA_ARGS__)\n\
    #  define O_assert_not_defined\n#endif\n\nnamespace lib {\n\nnamespace internal\
    \ {\n  int int_log2(const int n) {\n    return std::numeric_limits<int>::digits\
    \ - __builtin_clz(n);\n  }\n}  // namespace internal\n\n//! @brief data structure\
    \ to calculate interval products of associative and idempotent operations (for\
    \ static array)\n//! @tparam Elem element type (deduced from constructor's parameters\
    \ but can be set manually if needed)\n//! @tparam Func functor type (deduced from\
    \ constructor's parameters but has to be specified if you set Elem manually)\n\
    template <typename Elem, typename Func>\nclass sparse_table {\nprivate:\n  const\
    \ int length;\n  const Func& binary_op;\n  std::vector<std::vector<Elem>> table;\n\
    \npublic:\n  //! @brief Construct a sparse table from source container\n  //!\
    \ @tparam Container container type (deduced from parameter)\n  //! @param src\
    \ source container\n  //! @param binary_op_functor functor (must be associative\
    \ & idempotent)\n  //! @note Time complexity: O(N log N) where N = size(src)\n\
    \  template <typename Container>\n  sparse_table(const Container& src, const Func&\
    \ binary_op_functor)\n      : length(static_cast<int>(std::size(src))), binary_op(binary_op_functor)\
    \ {\n    const int M = internal::int_log2(length) + 1;\n\n    table = std::vector(length,\
    \ std::vector<Elem>(M));\n\n    for (int i = 0; i < length; ++i)\n      table[i][0]\
    \ = src[i];\n    for (int j = 1; j < M; ++j)\n      for (int i = 0; i + (1 <<\
    \ j) <= length; ++i)\n        table[i][j] = binary_op(table[i][j - 1], table[i\
    \ + (1 << (j - 1))][j - 1]);\n  }\n\n  //! @return Vector length\n  [[nodiscard]]\
    \ int size() const noexcept {\n    return length;\n  }\n\n  //! @brief Get the\
    \ value of the index-th element.\n  //! @param index index (0-indexed)\n  [[nodiscard]]\
    \ Elem get(const int index) const {\n    return table[index][0];\n  }\n\n  //!\
    \ @param left lower limit of interval (0-indexed)\n  //! @param right upper limit\
    \ of interval (0-indexed)\n  //! @return product of the elements of an interval\
    \ [left, right) (half-open interval)\n  //! @note Time complexity: O(1)\n  [[nodiscard]]\
    \ Elem query(const int left, const int right) const {\n    O_assert(0 <= left\
    \ && left < right && right <= length);\n    const int j = internal::int_log2(right\
    \ - left);\n    return binary_op(table[left][j], table[right - (1 << j)][j]);\n\
    \  }\n};\n\n//! @brief Deduction guide\ntemplate <typename Container, typename\
    \ Func>\nsparse_table(const Container&, const Func&)\n  -> sparse_table<std::decay_t<decltype(*std::begin(std::declval<Container>()))>,\
    \ Func>;\n\n}  // namespace lib\n\n#ifdef O_assert_not_defined\n#  undef O_assert\n\
    #  undef O_assert_not_defined\n#endif\n\n#endif  // SPARSE_TABLE_HPP\n"
  code: "\n//! @file sparse_table.hpp\n//! @details Provide a data structure to calculate\
    \ interval products of associative and idempotent operations.\n\n#ifndef SPARSE_TABLE_HPP\n\
    #define SPARSE_TABLE_HPP\n\n#include <cassert>\n#include <limits>\n#include <type_traits>\n\
    #include <vector>\n\n#ifndef O_assert\n//! @brief Assert macro\n#  define O_assert(...)\
    \ assert(__VA_ARGS__)\n#  define O_assert_not_defined\n#endif\n\nnamespace lib\
    \ {\n\nnamespace internal {\n  int int_log2(const int n) {\n    return std::numeric_limits<int>::digits\
    \ - __builtin_clz(n);\n  }\n}  // namespace internal\n\n//! @brief data structure\
    \ to calculate interval products of associative and idempotent operations (for\
    \ static array)\n//! @tparam Elem element type (deduced from constructor's parameters\
    \ but can be set manually if needed)\n//! @tparam Func functor type (deduced from\
    \ constructor's parameters but has to be specified if you set Elem manually)\n\
    template <typename Elem, typename Func>\nclass sparse_table {\nprivate:\n  const\
    \ int length;\n  const Func& binary_op;\n  std::vector<std::vector<Elem>> table;\n\
    \npublic:\n  //! @brief Construct a sparse table from source container\n  //!\
    \ @tparam Container container type (deduced from parameter)\n  //! @param src\
    \ source container\n  //! @param binary_op_functor functor (must be associative\
    \ & idempotent)\n  //! @note Time complexity: O(N log N) where N = size(src)\n\
    \  template <typename Container>\n  sparse_table(const Container& src, const Func&\
    \ binary_op_functor)\n      : length(static_cast<int>(std::size(src))), binary_op(binary_op_functor)\
    \ {\n    const int M = internal::int_log2(length) + 1;\n\n    table = std::vector(length,\
    \ std::vector<Elem>(M));\n\n    for (int i = 0; i < length; ++i)\n      table[i][0]\
    \ = src[i];\n    for (int j = 1; j < M; ++j)\n      for (int i = 0; i + (1 <<\
    \ j) <= length; ++i)\n        table[i][j] = binary_op(table[i][j - 1], table[i\
    \ + (1 << (j - 1))][j - 1]);\n  }\n\n  //! @return Vector length\n  [[nodiscard]]\
    \ int size() const noexcept {\n    return length;\n  }\n\n  //! @brief Get the\
    \ value of the index-th element.\n  //! @param index index (0-indexed)\n  [[nodiscard]]\
    \ Elem get(const int index) const {\n    return table[index][0];\n  }\n\n  //!\
    \ @param left lower limit of interval (0-indexed)\n  //! @param right upper limit\
    \ of interval (0-indexed)\n  //! @return product of the elements of an interval\
    \ [left, right) (half-open interval)\n  //! @note Time complexity: O(1)\n  [[nodiscard]]\
    \ Elem query(const int left, const int right) const {\n    O_assert(0 <= left\
    \ && left < right && right <= length);\n    const int j = internal::int_log2(right\
    \ - left);\n    return binary_op(table[left][j], table[right - (1 << j)][j]);\n\
    \  }\n};\n\n//! @brief Deduction guide\ntemplate <typename Container, typename\
    \ Func>\nsparse_table(const Container&, const Func&)\n  -> sparse_table<std::decay_t<decltype(*std::begin(std::declval<Container>()))>,\
    \ Func>;\n\n}  // namespace lib\n\n#ifdef O_assert_not_defined\n#  undef O_assert\n\
    #  undef O_assert_not_defined\n#endif\n\n#endif  // SPARSE_TABLE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/data_structure/sparse_table.hpp
  requiredBy: []
  timestamp: '2021-07-30 03:55:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structure/sparse_table/1.test.cpp
documentation_of: include/data_structure/sparse_table.hpp
layout: document
title: Sparse table
---

`sparse_table` クラスが定義されています。

## `sparse_table` クラス

要素が変化しない配列を格納し、結合法則と冪等性を満たす演算(最小値, 最大値, 最小公倍数, 最大公約数 等)の区間積を高速に求めることができるデータ構造 (sparse table) です。

### コンストラクタ

```C++
std::vector<int> v {1, 2, 3, 4, 5, 6};
const auto lcm = [](const int x, const int y) constexpr -> int { return std::lcm(x, y); };

lib::sparse_table t1(v, lcm);  // 1.
lib::sparse_table<long long, decltype(lcm)> t2(v, lcm);  // 2.
```

1. 配列と関数オブジェクトを受け取って sparse table を構築します。
1. 最小公倍数のように関数が返す値が配列の要素よりも大きくオーバーフローの恐れがある場合等には(より大きな値を表現できる)要素の型を明示して構築をすることができます。

### メンバ関数

#### `size()`

配列の要素数を返します。

#### `get(i)`

$i$ 番目 (0-indexed) の要素の値を返します。

#### `query(l, r)`

半開区間 $[l, r)$ (0-indexed) に含まれる要素に対して演算を作用させた結果(区間積)を返します。
