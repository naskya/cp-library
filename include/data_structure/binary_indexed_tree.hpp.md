---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structure/binary_indexed_tree/1.test.cpp
    title: test/data_structure/binary_indexed_tree/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/binary_indexed_tree/2.test.cpp
    title: test/data_structure/binary_indexed_tree/2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Assert macro
    links: []
  bundledCode: "#line 1 \"include/data_structure/binary_indexed_tree.hpp\"\n\n//!\
    \ @file binary_indexed_tree.hpp\n\n#ifndef BINARY_INDEXED_TREE_HPP\n#define BINARY_INDEXED_TREE_HPP\n\
    \n#include <cassert>\n#include <iostream>\n#include <string>\n#include <vector>\n\
    \n#ifndef O_assert\n//! @brief Assert macro\n#  define O_assert(...) assert(__VA_ARGS__)\n\
    #  define O_assert_not_defined\n#endif\n\nnamespace lib {\n\nnamespace internal\
    \ {\n  //! @brief Normal binary indexed tree.\n  //! @tparam Elem Element type.\
    \ Watch out for overflows.\n  template <typename Elem>\n  class binary_indexed_tree_impl\
    \ {\n  private:\n    int length;\n    std::vector<Elem> data;\n\n    //! @return\
    \ Sum of the elements within [0, index) (0-indexed, half-open interval)\n    [[nodiscard]]\
    \ Elem partial_sum(int index) const {\n      Elem res = 0;\n      for (; index\
    \ > 0; index -= (index & -index))\n        res += data[index];\n      return res;\n\
    \    }\n\n  public:\n    //! @brief Construct a vector of n zeroes.\n    //! @param\
    \ n vector length\n    explicit binary_indexed_tree_impl(const int n) : length(n),\
    \ data(n + 1, (Elem) 0) {}\n\n    //! @brief Construct a vector from an existing\
    \ container.\n    //! @tparam Container Container container type (deduced from\
    \ parameter).\n    //! @param src Source (container)\n    template <typename Container>\n\
    \    explicit binary_indexed_tree_impl(const Container& src)\n        : length(static_cast<int>(std::size(src))),\
    \ data(length + 1, (Elem) 0) {\n      for (int i = 0; i < length; ++i)\n     \
    \   add(i, src[i]);\n    }\n\n    //! @brief Construct a vector of length n filled\
    \ with init_vals.\n    //! @param n vector length\n    //! @param init_val initial\
    \ value for all elements\n    binary_indexed_tree_impl(const int n, const Elem&\
    \ init_val) : length(n), data(n + 1, (Elem) 0) {\n      for (int i = 0; i < length;\
    \ ++i)\n        add(i, init_val);\n    }\n\n    //! @return Vector length\n  \
    \  [[nodiscard]] int size() const noexcept {\n      return length;\n    }\n\n\
    \    //! @brief Add val to the index-th element.\n    //! @param index index of\
    \ the element to be added (0-indexed)\n    //! @param val value to be added\n\
    \    //! @note Time complexity: O(log n) where n is the vector length\n    void\
    \ add(int index, const Elem& val) {\n      O_assert(0 <= index && index < length);\n\
    \      for (++index; index <= length; index += (index & -index))\n        data[index]\
    \ += val;\n    }\n\n    //! @brief Calculate interval sum.\n    //! @param left\
    \ lower limit of interval (0-indexed)\n    //! @param right upper limit of interval\
    \ (0-indexed)\n    //! @return Sum of the elements within [left, right) (half-open\
    \ interval)\n    //! @note Time complexity: O(log n) where n is the vector length\n\
    \    [[nodiscard]] Elem sum(int left, int right) const {\n      O_assert(0 <=\
    \ left && left <= right && right <= length);\n      if (left == 0)\n        return\
    \ partial_sum(right);\n      else\n        return partial_sum(right) - partial_sum(left\
    \ - 1);\n    }\n\n    //! @brief Get the value of the index-th element.\n    //!\
    \ @param index index (0-indexed)\n    //! @note Time complexity: O(log n) where\
    \ n is the vector length\n    [[nodiscard]] Elem get(int index) const {\n    \
    \  return partial_sum(index + 1) - partial_sum(index);\n    }\n\n    //! @brief\
    \ Set the value of the index-th element to val.\n    //! @param index index (0-indexed)\n\
    \    //! @param val value to be set\n    //! @note Time complexity: O(log n) where\
    \ n is the vector length\n    void set(const int index, const Elem& val) {\n \
    \     add(index, val - get(index));\n    }\n  };\n}  // namespace internal\n\n\
    //! @brief Binary indexed tree with uniform add function.\n//! @tparam Elem Element\
    \ type. Watch out for overflows.\ntemplate <typename Elem>\nclass binary_indexed_tree\
    \ {\nprivate:\n  internal::binary_indexed_tree_impl<Elem> bit_0, bit_1;\n\n  //!\
    \ @return Sum of the elements within [0, index) (0-indexed, half-open interval)\n\
    \  [[nodiscard]] Elem partial_sum(int index) const {\n    return bit_0.sum(0,\
    \ index) + bit_1.sum(0, index) * (index - 1);\n  }\n\npublic:\n  //! @brief Construct\
    \ a vector of n zeroes.\n  //! @param n vector length\n  explicit binary_indexed_tree(const\
    \ int n) : bit_0(n), bit_1(n) {}\n\n  //! @brief Construct a vector from an existing\
    \ container.\n  //! @tparam Container Container container type (deduced from parameter).\n\
    \  //! @param src Source (container)\n  template <typename Container>\n  explicit\
    \ binary_indexed_tree(const Container& src) : bit_0(src), bit_1(static_cast<int>(std::size(src)))\
    \ {}\n\n  //! @brief Construct a vector of length n filled with init_vals.\n \
    \ //! @param n vector length\n  //! @param init_val initial value for all elements\n\
    \  binary_indexed_tree(const int n, const Elem& init_val) : bit_0(n, init_val),\
    \ bit_1(n) {}\n\n  //! @return Vector length\n  [[nodiscard]] int size() const\
    \ noexcept {\n    return bit_0.size();\n  }\n\n  //! @brief Add val to the index-th\
    \ element.\n  //! @param index index of the element to be added (0-indexed)\n\
    \  //! @param val value to be added\n  //! @note Time complexity: O(log n) where\
    \ n is the vector length\n  void add(int index, const Elem& val) {\n    bit_0.add(index,\
    \ val);\n  }\n\n  //! @brief Add val to the elements within [left, right) (half-open\
    \ interval)\n  //! @param left lower limit of interval (0-indexed)\n  //! @param\
    \ right upper limit of interval (0-indexed)\n  //! @param val value to be added\n\
    \  //! @note Time complexity: O(log n) where n is the vector length\n  void uniform_add(int\
    \ left, int right, const Elem& val) {\n    O_assert(0 <= left && left <= right\
    \ && right <= size());\n    if (left != size()) {\n      bit_0.add(left, val *\
    \ (-1) * (left - 1));\n      bit_1.add(left, val);\n    }\n    if (right != size())\
    \ {\n      bit_0.add(right, val * (right - 1));\n      bit_1.add(right, val *\
    \ (-1));\n    }\n  }\n\n  //! @brief Calculate interval sum.\n  //! @param left\
    \ lower limit of interval (0-indexed)\n  //! @param right upper limit of interval\
    \ (0-indexed)\n  //! @return Sum of the elements within [left, right) (half-open\
    \ interval)\n  //! @note Time complexity: O(log n) where n is the vector length\n\
    \  [[nodiscard]] Elem sum(int left, int right) const {\n    if (left == 0)\n \
    \     return partial_sum(right);\n    else\n      return partial_sum(right) -\
    \ partial_sum(left - 1);\n  }\n\n  //! @brief Get the value of the index-th element.\n\
    \  //! @param index index (0-indexed)\n  //! @note Time complexity: O(log n) where\
    \ n is the vector length\n  [[nodiscard]] Elem get(int index) const {\n    return\
    \ partial_sum(index + 1) - partial_sum(index);\n  }\n\n  //! @brief Set the value\
    \ of the index-th element to val.\n  //! @param index index (0-indexed)\n  //!\
    \ @param val value to be set\n  //! @note Time complexity: O(log n) where n is\
    \ the vector length\n  void set(const int index, const Elem& val) {\n    bit_0.add(index,\
    \ val - get(index));\n  }\n\n  //! @brief Print debug information.\n  //! @param\
    \ name variable name\n  //! @param os output stream\n  void debug_print(const\
    \ std::string& name = \"\", std::ostream& os = std::cerr) const {\n    if (!name.empty())\n\
    \      os << name << \": \";\n\n    os << \"val [ \";\n    for (int i = 0; i <\
    \ size(); ++i)\n      os << get(i) << ' ';\n    os << \"]\\n\";\n\n    if (!name.empty())\n\
    \      os << std::string(std::size(name) + 2, ' ');\n\n    os << \"sum [ \";\n\
    \    for (int i = 0; i <= size(); ++i)\n      os << partial_sum(i) << ' ';\n \
    \   os << \"]\\n\";\n  }\n};\n\n}  // namespace lib\n\n#ifdef O_assert_not_defined\n\
    #  undef O_assert\n#  undef O_assert_not_defined\n#endif\n\n#endif  // BINARY_INDEXED_TREE_HPP\n"
  code: "\n//! @file binary_indexed_tree.hpp\n\n#ifndef BINARY_INDEXED_TREE_HPP\n\
    #define BINARY_INDEXED_TREE_HPP\n\n#include <cassert>\n#include <iostream>\n#include\
    \ <string>\n#include <vector>\n\n#ifndef O_assert\n//! @brief Assert macro\n#\
    \  define O_assert(...) assert(__VA_ARGS__)\n#  define O_assert_not_defined\n\
    #endif\n\nnamespace lib {\n\nnamespace internal {\n  //! @brief Normal binary\
    \ indexed tree.\n  //! @tparam Elem Element type. Watch out for overflows.\n \
    \ template <typename Elem>\n  class binary_indexed_tree_impl {\n  private:\n \
    \   int length;\n    std::vector<Elem> data;\n\n    //! @return Sum of the elements\
    \ within [0, index) (0-indexed, half-open interval)\n    [[nodiscard]] Elem partial_sum(int\
    \ index) const {\n      Elem res = 0;\n      for (; index > 0; index -= (index\
    \ & -index))\n        res += data[index];\n      return res;\n    }\n\n  public:\n\
    \    //! @brief Construct a vector of n zeroes.\n    //! @param n vector length\n\
    \    explicit binary_indexed_tree_impl(const int n) : length(n), data(n + 1, (Elem)\
    \ 0) {}\n\n    //! @brief Construct a vector from an existing container.\n   \
    \ //! @tparam Container Container container type (deduced from parameter).\n \
    \   //! @param src Source (container)\n    template <typename Container>\n   \
    \ explicit binary_indexed_tree_impl(const Container& src)\n        : length(static_cast<int>(std::size(src))),\
    \ data(length + 1, (Elem) 0) {\n      for (int i = 0; i < length; ++i)\n     \
    \   add(i, src[i]);\n    }\n\n    //! @brief Construct a vector of length n filled\
    \ with init_vals.\n    //! @param n vector length\n    //! @param init_val initial\
    \ value for all elements\n    binary_indexed_tree_impl(const int n, const Elem&\
    \ init_val) : length(n), data(n + 1, (Elem) 0) {\n      for (int i = 0; i < length;\
    \ ++i)\n        add(i, init_val);\n    }\n\n    //! @return Vector length\n  \
    \  [[nodiscard]] int size() const noexcept {\n      return length;\n    }\n\n\
    \    //! @brief Add val to the index-th element.\n    //! @param index index of\
    \ the element to be added (0-indexed)\n    //! @param val value to be added\n\
    \    //! @note Time complexity: O(log n) where n is the vector length\n    void\
    \ add(int index, const Elem& val) {\n      O_assert(0 <= index && index < length);\n\
    \      for (++index; index <= length; index += (index & -index))\n        data[index]\
    \ += val;\n    }\n\n    //! @brief Calculate interval sum.\n    //! @param left\
    \ lower limit of interval (0-indexed)\n    //! @param right upper limit of interval\
    \ (0-indexed)\n    //! @return Sum of the elements within [left, right) (half-open\
    \ interval)\n    //! @note Time complexity: O(log n) where n is the vector length\n\
    \    [[nodiscard]] Elem sum(int left, int right) const {\n      O_assert(0 <=\
    \ left && left <= right && right <= length);\n      if (left == 0)\n        return\
    \ partial_sum(right);\n      else\n        return partial_sum(right) - partial_sum(left\
    \ - 1);\n    }\n\n    //! @brief Get the value of the index-th element.\n    //!\
    \ @param index index (0-indexed)\n    //! @note Time complexity: O(log n) where\
    \ n is the vector length\n    [[nodiscard]] Elem get(int index) const {\n    \
    \  return partial_sum(index + 1) - partial_sum(index);\n    }\n\n    //! @brief\
    \ Set the value of the index-th element to val.\n    //! @param index index (0-indexed)\n\
    \    //! @param val value to be set\n    //! @note Time complexity: O(log n) where\
    \ n is the vector length\n    void set(const int index, const Elem& val) {\n \
    \     add(index, val - get(index));\n    }\n  };\n}  // namespace internal\n\n\
    //! @brief Binary indexed tree with uniform add function.\n//! @tparam Elem Element\
    \ type. Watch out for overflows.\ntemplate <typename Elem>\nclass binary_indexed_tree\
    \ {\nprivate:\n  internal::binary_indexed_tree_impl<Elem> bit_0, bit_1;\n\n  //!\
    \ @return Sum of the elements within [0, index) (0-indexed, half-open interval)\n\
    \  [[nodiscard]] Elem partial_sum(int index) const {\n    return bit_0.sum(0,\
    \ index) + bit_1.sum(0, index) * (index - 1);\n  }\n\npublic:\n  //! @brief Construct\
    \ a vector of n zeroes.\n  //! @param n vector length\n  explicit binary_indexed_tree(const\
    \ int n) : bit_0(n), bit_1(n) {}\n\n  //! @brief Construct a vector from an existing\
    \ container.\n  //! @tparam Container Container container type (deduced from parameter).\n\
    \  //! @param src Source (container)\n  template <typename Container>\n  explicit\
    \ binary_indexed_tree(const Container& src) : bit_0(src), bit_1(static_cast<int>(std::size(src)))\
    \ {}\n\n  //! @brief Construct a vector of length n filled with init_vals.\n \
    \ //! @param n vector length\n  //! @param init_val initial value for all elements\n\
    \  binary_indexed_tree(const int n, const Elem& init_val) : bit_0(n, init_val),\
    \ bit_1(n) {}\n\n  //! @return Vector length\n  [[nodiscard]] int size() const\
    \ noexcept {\n    return bit_0.size();\n  }\n\n  //! @brief Add val to the index-th\
    \ element.\n  //! @param index index of the element to be added (0-indexed)\n\
    \  //! @param val value to be added\n  //! @note Time complexity: O(log n) where\
    \ n is the vector length\n  void add(int index, const Elem& val) {\n    bit_0.add(index,\
    \ val);\n  }\n\n  //! @brief Add val to the elements within [left, right) (half-open\
    \ interval)\n  //! @param left lower limit of interval (0-indexed)\n  //! @param\
    \ right upper limit of interval (0-indexed)\n  //! @param val value to be added\n\
    \  //! @note Time complexity: O(log n) where n is the vector length\n  void uniform_add(int\
    \ left, int right, const Elem& val) {\n    O_assert(0 <= left && left <= right\
    \ && right <= size());\n    if (left != size()) {\n      bit_0.add(left, val *\
    \ (-1) * (left - 1));\n      bit_1.add(left, val);\n    }\n    if (right != size())\
    \ {\n      bit_0.add(right, val * (right - 1));\n      bit_1.add(right, val *\
    \ (-1));\n    }\n  }\n\n  //! @brief Calculate interval sum.\n  //! @param left\
    \ lower limit of interval (0-indexed)\n  //! @param right upper limit of interval\
    \ (0-indexed)\n  //! @return Sum of the elements within [left, right) (half-open\
    \ interval)\n  //! @note Time complexity: O(log n) where n is the vector length\n\
    \  [[nodiscard]] Elem sum(int left, int right) const {\n    if (left == 0)\n \
    \     return partial_sum(right);\n    else\n      return partial_sum(right) -\
    \ partial_sum(left - 1);\n  }\n\n  //! @brief Get the value of the index-th element.\n\
    \  //! @param index index (0-indexed)\n  //! @note Time complexity: O(log n) where\
    \ n is the vector length\n  [[nodiscard]] Elem get(int index) const {\n    return\
    \ partial_sum(index + 1) - partial_sum(index);\n  }\n\n  //! @brief Set the value\
    \ of the index-th element to val.\n  //! @param index index (0-indexed)\n  //!\
    \ @param val value to be set\n  //! @note Time complexity: O(log n) where n is\
    \ the vector length\n  void set(const int index, const Elem& val) {\n    bit_0.add(index,\
    \ val - get(index));\n  }\n\n  //! @brief Print debug information.\n  //! @param\
    \ name variable name\n  //! @param os output stream\n  void debug_print(const\
    \ std::string& name = \"\", std::ostream& os = std::cerr) const {\n    if (!name.empty())\n\
    \      os << name << \": \";\n\n    os << \"val [ \";\n    for (int i = 0; i <\
    \ size(); ++i)\n      os << get(i) << ' ';\n    os << \"]\\n\";\n\n    if (!name.empty())\n\
    \      os << std::string(std::size(name) + 2, ' ');\n\n    os << \"sum [ \";\n\
    \    for (int i = 0; i <= size(); ++i)\n      os << partial_sum(i) << ' ';\n \
    \   os << \"]\\n\";\n  }\n};\n\n}  // namespace lib\n\n#ifdef O_assert_not_defined\n\
    #  undef O_assert\n#  undef O_assert_not_defined\n#endif\n\n#endif  // BINARY_INDEXED_TREE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/data_structure/binary_indexed_tree.hpp
  requiredBy: []
  timestamp: '2021-07-30 02:08:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structure/binary_indexed_tree/1.test.cpp
  - test/data_structure/binary_indexed_tree/2.test.cpp
documentation_of: include/data_structure/binary_indexed_tree.hpp
layout: document
title: Binary indexed tree
---

`binary_indexed_tree` クラスが定義されています。

## `binary_indexed_tree` クラス

区間一様加算の機能がついた [Binary indexed tree](https://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A7%E3%83%8B%E3%83%83%E3%82%AF%E6%9C%A8) です。

### クラステンプレート

`binary_indexed_tree` クラスは要素の型を表す 1 つのテンプレート引数をとります。

```C++
lib::binary_indexed_tree<int>  // int 型の要素を持つ binary indexed tree
```

要素の型には `int`, `long long` 等の整数型の他に、`double` 等の浮動小数点数型や `__int128`, [`cpp_int`](https://www.boost.org/doc/libs/1_76_0/libs/multiprecision/doc/html/boost_multiprecision/tut/ints/cpp_int.html), [`static_modint`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) 等の加減算の演算子が適切に定義された型を用いることができます。

### コンストラクタ

```C++
lib::binary_indexed_tree<int> tree_1(N);     // 1.
lib::binary_indexed_tree<int> tree_2(N, x);  // 2.

std::vector<int> v {1, 2, 3, 4, 5};
lib::binary_indexed_tree<int> tree_3(v);  // 3.
```

1. 要素数 $N$ の、全ての要素が $0$ で初期化された Binary indexed tree を構築します。
1. 要素数 $N$ の、全ての要素が $x$ で初期化された Binary indexed tree を構築します。
1. $v$ の要素で初期化された、$v$ と同じ要素数の Binary indexed tree を構築します。

### メンバ関数

#### `size()`

要素数を返します。

#### `add(i, x)`

$i$ 番目 (0-indexed) の要素に $x$ を加算します。

#### `uniform_add(l, r, x)`

半開区間 $[l, r)$ (0-indexed) に含まれる全ての要素に $x$ を加算します。

#### `sum(l, r)`

半開区間 $[l, r)$ (0-indexed) に含まれる要素の総和を返します。

#### `get(i)`

$i$ 番目 (0-indexed) の要素の値を返します。

#### `set(i, x)`

$i$ 番目 (0-indexed) の要素の値を $x$ にします。


#### `debug_print()`

標準エラー出力にデバッグ情報を出力します。
