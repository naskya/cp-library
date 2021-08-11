---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structure/segment_tree/1.test.cpp
    title: test/data_structure/segment_tree/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/segment_tree/2.test.cpp
    title: test/data_structure/segment_tree/2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/segment_tree/3.test.cpp
    title: test/data_structure/segment_tree/3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/segment_tree/4.test.cpp
    title: test/data_structure/segment_tree/4.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/segment_tree/5.test.cpp
    title: test/data_structure/segment_tree/5.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/segment_tree/6.test.cpp
    title: test/data_structure/segment_tree/6.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/segment_tree/7.test.cpp
    title: test/data_structure/segment_tree/7.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/segment_tree/8.test.cpp
    title: test/data_structure/segment_tree/8.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Print warning message
    links: []
  bundledCode: "#line 1 \"include/data_structure/segment_tree.hpp\"\n\n//! @file segment_tree.hpp\n\
    \n#ifndef CP_LIBRARY_SEGMENT_TREE_HPP\n#define CP_LIBRARY_SEGMENT_TREE_HPP\n\n\
    #include <algorithm>\n#include <cassert>\n#include <functional>\n#include <iostream>\n\
    #include <limits>\n#include <string>\n#include <type_traits>\n#include <vector>\n\
    \n#ifndef CP_LIBRARY_WARN\n#  if (CP_LIBRARY_DEBUG_LEVEL >= 1)\n//! @brief Print\
    \ warning message\n//! @note You can suppress the warning by uncommenting line\
    \ 21\n#    define CP_LIBRARY_WARN(msg) (std::cerr << (msg) << '\\n')\n// #  define\
    \ CP_LIBRARY_WARN(msg) (static_cast<void>(0))\n#  else\n#    define CP_LIBRARY_WARN(msg)\
    \ (static_cast<void>(0))\n#  endif\n#  define CP_LIBRARY_WARN_NOT_DEFINED\n#endif\n\
    \n#ifndef CP_LIBRARY_ASSERT\n//! @brief Assert macro\n#  define CP_LIBRARY_ASSERT(...)\
    \ assert(__VA_ARGS__)\n#  define CP_LIBRARY_ASSERT_NOT_DEFINED\n#endif\n\nnamespace\
    \ lib {\n\nnamespace internal::segment_tree_hpp {\n  template <typename Func,\
    \ typename Arg>\n  auto is_binary_op_of_impl(int) -> std::bool_constant<std::is_same_v<decltype(std::declval<Func>()(std::declval<Arg>(),\
    \ std::declval<Arg>())), Arg>>;\n  template <typename Func, typename Arg>\n  auto\
    \ is_binary_op_of_impl(...) -> std::false_type;\n\n  //! @brief Check if Func(Arg,\
    \ Arg) returns a value of type Arg.\n  template <typename Func, typename Arg>\n\
    \  [[maybe_unused]] constexpr bool is_binary_op_of_v = decltype(is_binary_op_of_impl<Func,\
    \ Arg>(int {}))::value;\n}  // namespace internal::segment_tree_hpp\n\n//! @brief\
    \ Segment tree\n//! @tparam Elem element type. Watch out for overflows.\n//! @tparam\
    \ Func binary op type.\ntemplate <typename Elem = long long, typename Func = std::plus<>,\n\
    \          std::enable_if_t<internal::segment_tree_hpp::is_binary_op_of_v<Func,\
    \ Elem>, std::nullptr_t> = nullptr>\nclass segment_tree {\nprivate:\n  const int\
    \ length;\n  const Elem id;\n  std::vector<Elem> data;\n  Func binary_op;\n  bool\
    \ locked;\n\n  //! @brief Propagate changes in the index-th element to its ancestors.\n\
    \  //! @note Time complexity: O(log size)\n  void propagate_impl(int index) {\n\
    \    index += length;\n    while (index > 0) {\n      index >>= 1;\n      data[index]\
    \ = binary_op(data[index << 1], data[index << 1 | 1]);\n    }\n  }\n\npublic:\n\
    \  //! @brief Construct a vector of n zeroes. Default operation (sum) will be\
    \ selected.\n  //! @param n vector size\n  explicit segment_tree(const int n)\n\
    \      : length(n),\n        id(0),\n        data(length << 1, id),\n        binary_op(),\n\
    \        locked(false) {}\n\n  //! @brief Construct a vector from an existing\
    \ container. Default operation (sum) will be selected.\n  //! @tparam Container\
    \ container type (deduced from parameter).\n  //! @param src Source (container)\n\
    \  template <typename Container>\n  explicit segment_tree(const Container& src)\n\
    \      : length(static_cast<int>(std::size(src))),\n        id(0),\n        data(length\
    \ << 1, id),\n        binary_op(),\n        locked(false) {\n    std::copy(std::cbegin(src),\
    \ std::cend(src), std::begin(data) + length);\n    for (int i = length - 1; i\
    \ > 0; --i)\n      data[i] = binary_op(data[i << 1], data[i << 1 | 1]);\n  }\n\
    \n  //! @brief Construct a vector of length n filled with init_vals. Default operation\
    \ (sum) will be selected.\n  //! @param n vector size\n  //! @param init_val initial\
    \ value for all elements\n  segment_tree(const int n, const Elem init_val)\n \
    \     : length(n),\n        id(0),\n        data(length << 1, id),\n        binary_op(),\n\
    \        locked(false) {\n    std::fill(std::begin(data) + length, std::end(data),\
    \ init_val);\n    for (int i = length - 1; i > 0; --i)\n      data[i] = binary_op(data[i\
    \ << 1], data[i << 1 | 1]);\n  }\n\n  //! @brief Construct a vector of n zeroes,\
    \ specifying a binary operation and its identity element.\n  //! @param n vector\
    \ size\n  //! @param identity_element identity element of the binary operation\n\
    \  //! @param binary_operation associative binary operation (sum, product, min,\
    \ max, ...)\n  segment_tree(const int n, const Elem identity_element, const Func&\
    \ binary_operation)\n      : length(n),\n        id(identity_element),\n     \
    \   data(length << 1, id),\n        binary_op(binary_operation),\n        locked(false)\
    \ {}\n\n  //! @brief Construct a vector from an existing container, specifying\
    \ a binary operation and its identity element.\n  //! @tparam Container container\
    \ type (deduced from parameter).\n  //! @param src Source (container)\n  //! @param\
    \ identity_element identity element of the binary operation\n  //! @param binary_operation\
    \ associative binary operation (sum, product, min, max, ...)\n  template <typename\
    \ Container>\n  segment_tree(const Container& src, const Elem identity_element,\
    \ const Func& binary_operation)\n      : length(static_cast<int>(std::size(src))),\n\
    \        id(identity_element),\n        data(length << 1, id),\n        binary_op(binary_operation),\n\
    \        locked(false) {\n    std::copy(std::cbegin(src), std::cend(src), std::begin(data)\
    \ + length);\n    for (int i = length - 1; i > 0; --i)\n      data[i] = binary_op(data[i\
    \ << 1], data[i << 1 | 1]);\n  }\n\n  //! @brief Construct a vector of length\
    \ n filled with init_vals, specifying a binary operation and its identity element.\n\
    \  //! @param n vector size\n  //! @param init_val initial value for all elements\n\
    \  //! @param identity_element identity element of the binary operation\n  //!\
    \ @param binary_operation associative binary operation (sum, product, min, max,\
    \ ...)\n  segment_tree(const int n, const Elem init_val, const Elem identity_element,\
    \ const Func& binary_operation)\n      : length(n),\n        id(identity_element),\n\
    \        data(length << 1, id),\n        binary_op(binary_operation),\n      \
    \  locked(false) {\n    std::fill(std::begin(data) + length, std::end(data), init_val);\n\
    \    for (int i = length - 1; i > 0; --i)\n      data[i] = binary_op(data[i <<\
    \ 1], data[i << 1 | 1]);\n  }\n\n  //! @brief Construct a vector of n zeroes,\
    \ specifying a binary operation and its identity element.\n  //! @param n vector\
    \ size\n  //! @param identity_element identity element of the binary operation\n\
    \  //! @param binary_operation associative binary operation (sum, product, min,\
    \ max, ...)\n  segment_tree(const int n, const Elem identity_element, Func&& binary_operation)\n\
    \      : length(n),\n        id(identity_element),\n        data(length << 1,\
    \ id),\n        binary_op(std::move(binary_operation)),\n        locked(false)\
    \ {}\n\n  //! @brief Construct a vector from an existing container, specifying\
    \ a binary operation and its identity element.\n  //! @tparam Container container\
    \ type (deduced from parameter).\n  //! @param src Source (container)\n  //! @param\
    \ identity_element identity element of the binary operation\n  //! @param binary_operation\
    \ associative binary operation (sum, product, min, max, ...)\n  template <typename\
    \ Container>\n  segment_tree(const Container& src, const Elem identity_element,\
    \ Func&& binary_operation)\n      : length(static_cast<int>(std::size(src))),\n\
    \        id(identity_element),\n        data(length << 1, id),\n        binary_op(std::move(binary_operation)),\n\
    \        locked(false) {\n    std::copy(std::cbegin(src), std::cend(src), std::begin(data)\
    \ + length);\n    for (int i = length - 1; i > 0; --i)\n      data[i] = binary_op(data[i\
    \ << 1], data[i << 1 | 1]);\n  }\n\n  //! @brief Construct a vector of n zeroes,\
    \ specifying a binary operation and its identity element.\n  //! @param n vector\
    \ size\n  //! @param identity_element identity element of the binary operation\n\
    \  //! @param binary_operation associative binary operation (sum, product, min,\
    \ max, ...)\n  segment_tree(const int n, const Elem init_val, const Elem identity_element,\
    \ Func&& binary_operation)\n      : length(n),\n        id(identity_element),\n\
    \        data(length << 1, id),\n        binary_op(std::move(binary_operation)),\n\
    \        locked(false) {\n    std::fill(std::begin(data) + length, std::end(data),\
    \ init_val);\n    for (int i = length - 1; i > 0; --i)\n      data[i] = binary_op(data[i\
    \ << 1], data[i << 1 | 1]);\n  }\n\n  ~segment_tree() {\n    if (locked)\n   \
    \   CP_LIBRARY_WARN(\"Segment tree is destructed in a locked state.\");\n  }\n\
    \n  //! @return Vector size (length)\n  [[nodiscard]] int size() const noexcept\
    \ {\n    return length;\n  }\n\n  //! @brief Add value to the index-th element.\n\
    \  //! @param index index of the element to be added (0-indexed)\n  //! @param\
    \ value value to be added\n  //! @note Time complexity: O(log size) if unlocked\n\
    \  //! @note Time complexity: O(1)        if locked\n  void add(const int index,\
    \ const Elem value) {\n    CP_LIBRARY_ASSERT(0 <= index && index < length);\n\
    \    data[index + length] = data[index + length] + value;\n    if (!locked)\n\
    \      propagate_impl(index);\n  }\n\n  //! @brief Set the value of the index-th\
    \ element to value.\n  //! @param index index (0-indexed)\n  //! @param value\
    \ value to be set\n  //! @note Time complexity: O(log size) if unlocked\n  //!\
    \ @note Time complexity: O(1)        if locked\n  void set(const int index, const\
    \ Elem value) {\n    CP_LIBRARY_ASSERT(0 <= index && index < length);\n    data[index\
    \ + length] = value;\n    if (!locked)\n      propagate_impl(index);\n  }\n\n\
    \  //! @brief Get the value of the index-th element.\n  //! @param index index\
    \ (0-indexed)\n  //! @note Time complexity: O(1)\n  [[nodiscard]] Elem get(const\
    \ int index) const {\n    CP_LIBRARY_ASSERT(0 <= index && index < length);\n \
    \   return data[index + length];\n  }\n\n  //! @brief Calculate interval product.\n\
    \  //! @param left lower limit of interval (0-indexed)\n  //! @param right upper\
    \ limit of interval (0-indexed)\n  //! @return product (result of the specified\
    \ binary operation) of the elements within [left, right) (half-open interval)\n\
    \  //! @note Time complexity: O(log size)\n  [[nodiscard]] Elem prod(int L, int\
    \ R) const {\n    CP_LIBRARY_ASSERT(!locked);\n    CP_LIBRARY_ASSERT(0 <= L &&\
    \ L <= R && R <= length);\n    L += length;\n    R += length;\n\n    Elem res_l\
    \ = id, res_r = id;\n\n    while (L < R) {\n      if (L & 1) {\n        res_l\
    \ = binary_op(res_l, data[L]);\n        ++L;\n      }\n      if (R & 1)\n    \
    \    res_r = binary_op(data[--R], res_r);\n      L >>= 1;\n      R >>= 1;\n  \
    \  }\n\n    return binary_op(res_l, res_r);\n  }\n\n  //! @brief Calculate product\
    \ of all elements.\n  //! @param left lower limit of interval (0-indexed)\n  //!\
    \ @param right upper limit of interval (0-indexed)\n  //! @return product (result\
    \ of the specified binary operation) of all elements\n  //! @note Time complexity:\
    \ O(1)\n  [[nodiscard]] Elem all_prod() const {\n    CP_LIBRARY_ASSERT(!locked);\n\
    \    return data[1];\n  }\n\n  //! @warning You need to call this function ONLY\
    \ IF you use lock()/unlock() function.\n  //! @brief Propagate changes in the\
    \ index-th element to its ancestors.\n  //! @note Time complexity: O(log size)\n\
    \  void propagate(int index) {\n    CP_LIBRARY_ASSERT(locked);\n    CP_LIBRARY_ASSERT(0\
    \ <= index && index < length);\n    propagate_impl(index);\n  }\n\n  //! @warning\
    \ You need to call this function ONLY IF you use lock()/unlock() function.\n \
    \ //! @brief Propagate changes of all elements to the ancestors.\n  //! @note\
    \ Time complexity: O(size)\n  void propagate_all() {\n    CP_LIBRARY_ASSERT(locked);\n\
    \    for (int i = length - 1; i > 0; --i)\n      data[i] = binary_op(data[i <<\
    \ 1], data[i << 1 | 1]);\n  }\n\n  //! @warning You need to call this function\
    \ ONLY IF you use lock()/unlock() function.\n  //! @brief Propagate changes of\
    \ all elements to the ancestors and resume automatic propagation.\n  //! @note\
    \ Time complexity: O(size)\n  void propagate_all_and_unlock() {\n    propagate_all();\n\
    \    unlock();\n  }\n\n  //! @warning You can call this function only if you can\
    \ promise not to call prod()/all_prod() until you call unlock().\n  //! @brief\
    \ Stop automatic propagation on element changes.\n  //! @note Time complexity:\
    \ O(1)\n  void lock() {\n    CP_LIBRARY_ASSERT(!locked);\n    locked = true;\n\
    \  }\n\n  //! @warning You can call this function only if this segment tree is\
    \ locked.\n  //! @warning This function will not perform propagation. You need\
    \ to call propagate()/propagate_all() manually.\n  //! @brief Resume automatic\
    \ propagation on element changes.\n  //! @note Time complexity: O(1)\n  void unlock()\
    \ {\n    CP_LIBRARY_ASSERT(locked);\n    locked = false;\n  }\n\n  //! @warning\
    \ You need to call this function ONLY IF you use lock()/unlock() function.\n \
    \ //! @return Whether the automatic propagation is stopped.\n  //! @note Time\
    \ complexity: O(1)\n  [[nodiscard]] bool is_locked() const {\n    return locked;\n\
    \  }\n\n  void debug_print([[maybe_unused]] const std::string& name = \"\", [[maybe_unused]]\
    \ std::ostream& os = std::cerr) const {\n#if (CP_LIBRARY_DEBUG_LEVEL >= 1)\n \
    \   if (!name.empty())\n      os << name << \": \";\n\n    os << \"val  [ \";\n\
    \    for (int i = 0; i < size(); ++i)\n      os << get(i) << ' ';\n    os << \"\
    ]\\n\";\n\n    if (!name.empty())\n      os << std::string(std::size(name) + 2,\
    \ ' ');\n\n    os << \"prod [ \";\n\n    if (locked)\n      os << \"cannot display\
    \ since range product query is locked \";\n    else\n      for (int i = 0; i <=\
    \ size(); ++i)\n        os << prod(0, i) << ' ';\n\n    os << \"]\\n\";\n#endif\n\
    \  }\n};\n\nnamespace internal::segment_tree_hpp {\n  template <typename Tp>\n\
    \  [[maybe_unused]] constexpr bool is_segment_tree_v = false;\n  template <typename\
    \ Elem, typename Func>\n  [[maybe_unused]] constexpr bool is_segment_tree_v<segment_tree<Elem,\
    \ Func>> = true;\n}  // namespace internal::segment_tree_hpp\n\n//! @brief Utility\
    \ class to automatically call lock() in constructor and propagate_all_and_unlock()\
    \ in destructor.\ntemplate <typename Tp, std::enable_if_t<internal::segment_tree_hpp::is_segment_tree_v<Tp>,\
    \ std::nullptr_t> = nullptr>\nclass no_range_query_in_this_scope {\nprivate:\n\
    \  Tp& target_segtree;\n\npublic:\n  //! @brief Lock segment tree by calling lock().\n\
    \  //! @param segtree target segment tree\n  //! @note Time complexity: O(1)\n\
    \  explicit no_range_query_in_this_scope(Tp& segtree) : target_segtree(segtree)\
    \ {\n    target_segtree.lock();\n  }\n  //! @brief Unlock segment tree and apply\
    \ all changes by calling propagate_all_and_unlock().\n  //! @note Time complexity:\
    \ O(size of target segment tree)\n  ~no_range_query_in_this_scope() {\n    target_segtree.propagate_all_and_unlock();\n\
    \  }\n};\n\n}  // namespace lib\n\n#ifdef CP_LIBRARY_WARN_NOT_DEFINED\n#  undef\
    \ CP_LIBRARY_WARN\n#  undef CP_LIBRARY_WARN_NOT_DEFINED\n#  ifdef CP_LIBRARY_WARN\n\
    #    undef CP_LIBRARY_WARN\n#  endif\n#endif\n\n#ifdef CP_LIBRARY_ASSERT_NOT_DEFINED\n\
    #  undef CP_LIBRARY_ASSERT\n#  undef CP_LIBRARY_ASSERT_NOT_DEFINED\n#endif\n\n\
    #endif  // CP_LIBRARY_SEGMENT_TREE_HPP\n"
  code: "\n//! @file segment_tree.hpp\n\n#ifndef CP_LIBRARY_SEGMENT_TREE_HPP\n#define\
    \ CP_LIBRARY_SEGMENT_TREE_HPP\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <functional>\n#include <iostream>\n#include <limits>\n#include <string>\n#include\
    \ <type_traits>\n#include <vector>\n\n#ifndef CP_LIBRARY_WARN\n#  if (CP_LIBRARY_DEBUG_LEVEL\
    \ >= 1)\n//! @brief Print warning message\n//! @note You can suppress the warning\
    \ by uncommenting line 21\n#    define CP_LIBRARY_WARN(msg) (std::cerr << (msg)\
    \ << '\\n')\n// #  define CP_LIBRARY_WARN(msg) (static_cast<void>(0))\n#  else\n\
    #    define CP_LIBRARY_WARN(msg) (static_cast<void>(0))\n#  endif\n#  define CP_LIBRARY_WARN_NOT_DEFINED\n\
    #endif\n\n#ifndef CP_LIBRARY_ASSERT\n//! @brief Assert macro\n#  define CP_LIBRARY_ASSERT(...)\
    \ assert(__VA_ARGS__)\n#  define CP_LIBRARY_ASSERT_NOT_DEFINED\n#endif\n\nnamespace\
    \ lib {\n\nnamespace internal::segment_tree_hpp {\n  template <typename Func,\
    \ typename Arg>\n  auto is_binary_op_of_impl(int) -> std::bool_constant<std::is_same_v<decltype(std::declval<Func>()(std::declval<Arg>(),\
    \ std::declval<Arg>())), Arg>>;\n  template <typename Func, typename Arg>\n  auto\
    \ is_binary_op_of_impl(...) -> std::false_type;\n\n  //! @brief Check if Func(Arg,\
    \ Arg) returns a value of type Arg.\n  template <typename Func, typename Arg>\n\
    \  [[maybe_unused]] constexpr bool is_binary_op_of_v = decltype(is_binary_op_of_impl<Func,\
    \ Arg>(int {}))::value;\n}  // namespace internal::segment_tree_hpp\n\n//! @brief\
    \ Segment tree\n//! @tparam Elem element type. Watch out for overflows.\n//! @tparam\
    \ Func binary op type.\ntemplate <typename Elem = long long, typename Func = std::plus<>,\n\
    \          std::enable_if_t<internal::segment_tree_hpp::is_binary_op_of_v<Func,\
    \ Elem>, std::nullptr_t> = nullptr>\nclass segment_tree {\nprivate:\n  const int\
    \ length;\n  const Elem id;\n  std::vector<Elem> data;\n  Func binary_op;\n  bool\
    \ locked;\n\n  //! @brief Propagate changes in the index-th element to its ancestors.\n\
    \  //! @note Time complexity: O(log size)\n  void propagate_impl(int index) {\n\
    \    index += length;\n    while (index > 0) {\n      index >>= 1;\n      data[index]\
    \ = binary_op(data[index << 1], data[index << 1 | 1]);\n    }\n  }\n\npublic:\n\
    \  //! @brief Construct a vector of n zeroes. Default operation (sum) will be\
    \ selected.\n  //! @param n vector size\n  explicit segment_tree(const int n)\n\
    \      : length(n),\n        id(0),\n        data(length << 1, id),\n        binary_op(),\n\
    \        locked(false) {}\n\n  //! @brief Construct a vector from an existing\
    \ container. Default operation (sum) will be selected.\n  //! @tparam Container\
    \ container type (deduced from parameter).\n  //! @param src Source (container)\n\
    \  template <typename Container>\n  explicit segment_tree(const Container& src)\n\
    \      : length(static_cast<int>(std::size(src))),\n        id(0),\n        data(length\
    \ << 1, id),\n        binary_op(),\n        locked(false) {\n    std::copy(std::cbegin(src),\
    \ std::cend(src), std::begin(data) + length);\n    for (int i = length - 1; i\
    \ > 0; --i)\n      data[i] = binary_op(data[i << 1], data[i << 1 | 1]);\n  }\n\
    \n  //! @brief Construct a vector of length n filled with init_vals. Default operation\
    \ (sum) will be selected.\n  //! @param n vector size\n  //! @param init_val initial\
    \ value for all elements\n  segment_tree(const int n, const Elem init_val)\n \
    \     : length(n),\n        id(0),\n        data(length << 1, id),\n        binary_op(),\n\
    \        locked(false) {\n    std::fill(std::begin(data) + length, std::end(data),\
    \ init_val);\n    for (int i = length - 1; i > 0; --i)\n      data[i] = binary_op(data[i\
    \ << 1], data[i << 1 | 1]);\n  }\n\n  //! @brief Construct a vector of n zeroes,\
    \ specifying a binary operation and its identity element.\n  //! @param n vector\
    \ size\n  //! @param identity_element identity element of the binary operation\n\
    \  //! @param binary_operation associative binary operation (sum, product, min,\
    \ max, ...)\n  segment_tree(const int n, const Elem identity_element, const Func&\
    \ binary_operation)\n      : length(n),\n        id(identity_element),\n     \
    \   data(length << 1, id),\n        binary_op(binary_operation),\n        locked(false)\
    \ {}\n\n  //! @brief Construct a vector from an existing container, specifying\
    \ a binary operation and its identity element.\n  //! @tparam Container container\
    \ type (deduced from parameter).\n  //! @param src Source (container)\n  //! @param\
    \ identity_element identity element of the binary operation\n  //! @param binary_operation\
    \ associative binary operation (sum, product, min, max, ...)\n  template <typename\
    \ Container>\n  segment_tree(const Container& src, const Elem identity_element,\
    \ const Func& binary_operation)\n      : length(static_cast<int>(std::size(src))),\n\
    \        id(identity_element),\n        data(length << 1, id),\n        binary_op(binary_operation),\n\
    \        locked(false) {\n    std::copy(std::cbegin(src), std::cend(src), std::begin(data)\
    \ + length);\n    for (int i = length - 1; i > 0; --i)\n      data[i] = binary_op(data[i\
    \ << 1], data[i << 1 | 1]);\n  }\n\n  //! @brief Construct a vector of length\
    \ n filled with init_vals, specifying a binary operation and its identity element.\n\
    \  //! @param n vector size\n  //! @param init_val initial value for all elements\n\
    \  //! @param identity_element identity element of the binary operation\n  //!\
    \ @param binary_operation associative binary operation (sum, product, min, max,\
    \ ...)\n  segment_tree(const int n, const Elem init_val, const Elem identity_element,\
    \ const Func& binary_operation)\n      : length(n),\n        id(identity_element),\n\
    \        data(length << 1, id),\n        binary_op(binary_operation),\n      \
    \  locked(false) {\n    std::fill(std::begin(data) + length, std::end(data), init_val);\n\
    \    for (int i = length - 1; i > 0; --i)\n      data[i] = binary_op(data[i <<\
    \ 1], data[i << 1 | 1]);\n  }\n\n  //! @brief Construct a vector of n zeroes,\
    \ specifying a binary operation and its identity element.\n  //! @param n vector\
    \ size\n  //! @param identity_element identity element of the binary operation\n\
    \  //! @param binary_operation associative binary operation (sum, product, min,\
    \ max, ...)\n  segment_tree(const int n, const Elem identity_element, Func&& binary_operation)\n\
    \      : length(n),\n        id(identity_element),\n        data(length << 1,\
    \ id),\n        binary_op(std::move(binary_operation)),\n        locked(false)\
    \ {}\n\n  //! @brief Construct a vector from an existing container, specifying\
    \ a binary operation and its identity element.\n  //! @tparam Container container\
    \ type (deduced from parameter).\n  //! @param src Source (container)\n  //! @param\
    \ identity_element identity element of the binary operation\n  //! @param binary_operation\
    \ associative binary operation (sum, product, min, max, ...)\n  template <typename\
    \ Container>\n  segment_tree(const Container& src, const Elem identity_element,\
    \ Func&& binary_operation)\n      : length(static_cast<int>(std::size(src))),\n\
    \        id(identity_element),\n        data(length << 1, id),\n        binary_op(std::move(binary_operation)),\n\
    \        locked(false) {\n    std::copy(std::cbegin(src), std::cend(src), std::begin(data)\
    \ + length);\n    for (int i = length - 1; i > 0; --i)\n      data[i] = binary_op(data[i\
    \ << 1], data[i << 1 | 1]);\n  }\n\n  //! @brief Construct a vector of n zeroes,\
    \ specifying a binary operation and its identity element.\n  //! @param n vector\
    \ size\n  //! @param identity_element identity element of the binary operation\n\
    \  //! @param binary_operation associative binary operation (sum, product, min,\
    \ max, ...)\n  segment_tree(const int n, const Elem init_val, const Elem identity_element,\
    \ Func&& binary_operation)\n      : length(n),\n        id(identity_element),\n\
    \        data(length << 1, id),\n        binary_op(std::move(binary_operation)),\n\
    \        locked(false) {\n    std::fill(std::begin(data) + length, std::end(data),\
    \ init_val);\n    for (int i = length - 1; i > 0; --i)\n      data[i] = binary_op(data[i\
    \ << 1], data[i << 1 | 1]);\n  }\n\n  ~segment_tree() {\n    if (locked)\n   \
    \   CP_LIBRARY_WARN(\"Segment tree is destructed in a locked state.\");\n  }\n\
    \n  //! @return Vector size (length)\n  [[nodiscard]] int size() const noexcept\
    \ {\n    return length;\n  }\n\n  //! @brief Add value to the index-th element.\n\
    \  //! @param index index of the element to be added (0-indexed)\n  //! @param\
    \ value value to be added\n  //! @note Time complexity: O(log size) if unlocked\n\
    \  //! @note Time complexity: O(1)        if locked\n  void add(const int index,\
    \ const Elem value) {\n    CP_LIBRARY_ASSERT(0 <= index && index < length);\n\
    \    data[index + length] = data[index + length] + value;\n    if (!locked)\n\
    \      propagate_impl(index);\n  }\n\n  //! @brief Set the value of the index-th\
    \ element to value.\n  //! @param index index (0-indexed)\n  //! @param value\
    \ value to be set\n  //! @note Time complexity: O(log size) if unlocked\n  //!\
    \ @note Time complexity: O(1)        if locked\n  void set(const int index, const\
    \ Elem value) {\n    CP_LIBRARY_ASSERT(0 <= index && index < length);\n    data[index\
    \ + length] = value;\n    if (!locked)\n      propagate_impl(index);\n  }\n\n\
    \  //! @brief Get the value of the index-th element.\n  //! @param index index\
    \ (0-indexed)\n  //! @note Time complexity: O(1)\n  [[nodiscard]] Elem get(const\
    \ int index) const {\n    CP_LIBRARY_ASSERT(0 <= index && index < length);\n \
    \   return data[index + length];\n  }\n\n  //! @brief Calculate interval product.\n\
    \  //! @param left lower limit of interval (0-indexed)\n  //! @param right upper\
    \ limit of interval (0-indexed)\n  //! @return product (result of the specified\
    \ binary operation) of the elements within [left, right) (half-open interval)\n\
    \  //! @note Time complexity: O(log size)\n  [[nodiscard]] Elem prod(int L, int\
    \ R) const {\n    CP_LIBRARY_ASSERT(!locked);\n    CP_LIBRARY_ASSERT(0 <= L &&\
    \ L <= R && R <= length);\n    L += length;\n    R += length;\n\n    Elem res_l\
    \ = id, res_r = id;\n\n    while (L < R) {\n      if (L & 1) {\n        res_l\
    \ = binary_op(res_l, data[L]);\n        ++L;\n      }\n      if (R & 1)\n    \
    \    res_r = binary_op(data[--R], res_r);\n      L >>= 1;\n      R >>= 1;\n  \
    \  }\n\n    return binary_op(res_l, res_r);\n  }\n\n  //! @brief Calculate product\
    \ of all elements.\n  //! @param left lower limit of interval (0-indexed)\n  //!\
    \ @param right upper limit of interval (0-indexed)\n  //! @return product (result\
    \ of the specified binary operation) of all elements\n  //! @note Time complexity:\
    \ O(1)\n  [[nodiscard]] Elem all_prod() const {\n    CP_LIBRARY_ASSERT(!locked);\n\
    \    return data[1];\n  }\n\n  //! @warning You need to call this function ONLY\
    \ IF you use lock()/unlock() function.\n  //! @brief Propagate changes in the\
    \ index-th element to its ancestors.\n  //! @note Time complexity: O(log size)\n\
    \  void propagate(int index) {\n    CP_LIBRARY_ASSERT(locked);\n    CP_LIBRARY_ASSERT(0\
    \ <= index && index < length);\n    propagate_impl(index);\n  }\n\n  //! @warning\
    \ You need to call this function ONLY IF you use lock()/unlock() function.\n \
    \ //! @brief Propagate changes of all elements to the ancestors.\n  //! @note\
    \ Time complexity: O(size)\n  void propagate_all() {\n    CP_LIBRARY_ASSERT(locked);\n\
    \    for (int i = length - 1; i > 0; --i)\n      data[i] = binary_op(data[i <<\
    \ 1], data[i << 1 | 1]);\n  }\n\n  //! @warning You need to call this function\
    \ ONLY IF you use lock()/unlock() function.\n  //! @brief Propagate changes of\
    \ all elements to the ancestors and resume automatic propagation.\n  //! @note\
    \ Time complexity: O(size)\n  void propagate_all_and_unlock() {\n    propagate_all();\n\
    \    unlock();\n  }\n\n  //! @warning You can call this function only if you can\
    \ promise not to call prod()/all_prod() until you call unlock().\n  //! @brief\
    \ Stop automatic propagation on element changes.\n  //! @note Time complexity:\
    \ O(1)\n  void lock() {\n    CP_LIBRARY_ASSERT(!locked);\n    locked = true;\n\
    \  }\n\n  //! @warning You can call this function only if this segment tree is\
    \ locked.\n  //! @warning This function will not perform propagation. You need\
    \ to call propagate()/propagate_all() manually.\n  //! @brief Resume automatic\
    \ propagation on element changes.\n  //! @note Time complexity: O(1)\n  void unlock()\
    \ {\n    CP_LIBRARY_ASSERT(locked);\n    locked = false;\n  }\n\n  //! @warning\
    \ You need to call this function ONLY IF you use lock()/unlock() function.\n \
    \ //! @return Whether the automatic propagation is stopped.\n  //! @note Time\
    \ complexity: O(1)\n  [[nodiscard]] bool is_locked() const {\n    return locked;\n\
    \  }\n\n  void debug_print([[maybe_unused]] const std::string& name = \"\", [[maybe_unused]]\
    \ std::ostream& os = std::cerr) const {\n#if (CP_LIBRARY_DEBUG_LEVEL >= 1)\n \
    \   if (!name.empty())\n      os << name << \": \";\n\n    os << \"val  [ \";\n\
    \    for (int i = 0; i < size(); ++i)\n      os << get(i) << ' ';\n    os << \"\
    ]\\n\";\n\n    if (!name.empty())\n      os << std::string(std::size(name) + 2,\
    \ ' ');\n\n    os << \"prod [ \";\n\n    if (locked)\n      os << \"cannot display\
    \ since range product query is locked \";\n    else\n      for (int i = 0; i <=\
    \ size(); ++i)\n        os << prod(0, i) << ' ';\n\n    os << \"]\\n\";\n#endif\n\
    \  }\n};\n\nnamespace internal::segment_tree_hpp {\n  template <typename Tp>\n\
    \  [[maybe_unused]] constexpr bool is_segment_tree_v = false;\n  template <typename\
    \ Elem, typename Func>\n  [[maybe_unused]] constexpr bool is_segment_tree_v<segment_tree<Elem,\
    \ Func>> = true;\n}  // namespace internal::segment_tree_hpp\n\n//! @brief Utility\
    \ class to automatically call lock() in constructor and propagate_all_and_unlock()\
    \ in destructor.\ntemplate <typename Tp, std::enable_if_t<internal::segment_tree_hpp::is_segment_tree_v<Tp>,\
    \ std::nullptr_t> = nullptr>\nclass no_range_query_in_this_scope {\nprivate:\n\
    \  Tp& target_segtree;\n\npublic:\n  //! @brief Lock segment tree by calling lock().\n\
    \  //! @param segtree target segment tree\n  //! @note Time complexity: O(1)\n\
    \  explicit no_range_query_in_this_scope(Tp& segtree) : target_segtree(segtree)\
    \ {\n    target_segtree.lock();\n  }\n  //! @brief Unlock segment tree and apply\
    \ all changes by calling propagate_all_and_unlock().\n  //! @note Time complexity:\
    \ O(size of target segment tree)\n  ~no_range_query_in_this_scope() {\n    target_segtree.propagate_all_and_unlock();\n\
    \  }\n};\n\n}  // namespace lib\n\n#ifdef CP_LIBRARY_WARN_NOT_DEFINED\n#  undef\
    \ CP_LIBRARY_WARN\n#  undef CP_LIBRARY_WARN_NOT_DEFINED\n#  ifdef CP_LIBRARY_WARN\n\
    #    undef CP_LIBRARY_WARN\n#  endif\n#endif\n\n#ifdef CP_LIBRARY_ASSERT_NOT_DEFINED\n\
    #  undef CP_LIBRARY_ASSERT\n#  undef CP_LIBRARY_ASSERT_NOT_DEFINED\n#endif\n\n\
    #endif  // CP_LIBRARY_SEGMENT_TREE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/data_structure/segment_tree.hpp
  requiredBy: []
  timestamp: '2021-08-11 13:38:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structure/segment_tree/3.test.cpp
  - test/data_structure/segment_tree/4.test.cpp
  - test/data_structure/segment_tree/6.test.cpp
  - test/data_structure/segment_tree/8.test.cpp
  - test/data_structure/segment_tree/1.test.cpp
  - test/data_structure/segment_tree/2.test.cpp
  - test/data_structure/segment_tree/7.test.cpp
  - test/data_structure/segment_tree/5.test.cpp
documentation_of: include/data_structure/segment_tree.hpp
layout: document
title: Segment tree
---

配列に対して以下のクエリが対数時間で行えるデータ構造である `segment_tree` クラスと、その制御に用いる `no_range_query_in_this_scope` クラスが定義されています。[`binary_indexed_tree`](https://naskya.github.io/cp-library/include/data_structure/binary_indexed_tree.hpp) や [`sparse_table`](https://naskya.github.io/cp-library/include/data_structure/sparse_table.hpp) が利用できる場合、そちらを利用した方が高速に動作することが期待できます。

- 配列の一つの要素の値を更新する
- 配列の一つの要素の値を取得する
- 配列の区間積を取得する

ここでいう「区間積」とは、配列のある区間内に二項演算を繰り返し適用した結果です。例えば二項演算を加算とすると、配列 $\{a_1,\, a_2,\, a_3,\, a_4,\, a_5,\, a_6\}$ の $a_2$ から $a_4$ までの区間の区間積は $a_2 + a_3 + a_4$ です。二項演算は単位元が存在して結合法則を満たすものであれば構いません。例えば掛け算・最小値を求める演算・最大値を求める演算等を使うこともできます。

---

### クラステンプレート

`segment_tree` クラスは 2 つの省略可能なテンプレート引数をとります。

```cpp
lib::segment_tree  // 1.
lib::segment_tree<int>  // 2.
lib::segment_tree<lib::static_modint<1000000007>>  // 3.
lib::segment_tree<int, std::bit_xor<>>  // 4.
```

1. テンプレート引数を省略した場合、要素の型は long long で二項演算は加算 (+) となります。
1. 第一引数で要素の型を指定できます。この場合要素の型は int で二項演算は加算 (+) となります。
1. 要素の型は組み込み型でなくてもよいです。この場合要素の型は [`lib::static_modint<1000000007>`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) で二項演算は加算 (+) となります。
1. 第二引数で二項演算を指定できます。この場合要素の型は int で二項演算は bitwise xor (^) となります。後述の通り他にも二項演算を変更する方法があります。

### コンストラクタ

```cpp
std::vector<int> v {1, 2, 3, 4, 5};

lib::segment_tree tree_1(N);      // 1.
lib::segment_tree tree_2(N, 10);  // 2.
lib::segment_tree tree_3(v);      // 3.

lib::segment_tree<long long, std::bit_xor<>> tree_4(N);      // 4.
lib::segment_tree<long long, std::bit_xor<>> tree_5(N, 10);  // 5.
lib::segment_tree<long long, std::bit_xor<>> tree_6(v);      // 6.

// 最小値を返す演算
const auto func_min = [](const long long x, const long long y) constexpr { return std::min(x, y); };
// 最小値を返す演算の単位元
constexpr long long id_min = 1000000000000000005LL;

lib::segment_tree tree_7(N, id_min, func_min);       // 7.
lib::segment_tree tree_8(N, 500, id_min, func_min);  // 8.
lib::segment_tree tree_9(v, id_min, func_min);       // 9.

// 引数の部分にラムダ式を直接書いても良い
// lib::segment_tree tree_9 (v, 1000000000000000005LL,
//                           [](long long x, long long y) { return std::min(x, y); });
```

1. 要素数 $N$ の、全ての要素が $0$ で初期化された、二項演算を加算とした Segment tree を構築します。
1. 要素数 $N$ の、全ての要素が $10$ で初期化された、二項演算を加算とした Segment tree を構築します。
1. $v$ の要素で初期化された、$v$ と同じ要素数の、二項演算を加算とした Segment tree を構築します。
1. 要素数 $N$ の、全ての要素が $0$ で初期化された、二項演算を bitwise xor とした Segment tree を構築します。
1. 要素数 $N$ の、全ての要素が $10$ で初期化された、二項演算を bitwise xor とした Segment tree を構築します。
1. $v$ の要素で初期化された、$v$ と同じ要素数の、二項演算を bitwise xor とした Segment tree を構築します。
1. 要素数 $N$ の、全ての要素が `id_min` で初期化された、二項演算を最小値をとる演算とした Segment tree を構築します。
1. 要素数 $N$ の、全ての要素が $500$ で初期化された、二項演算を最小値をとる演算とした Segment tree を構築します。
1. $v$ の要素で初期化された、$v$ と同じ要素数の、二項演算を最小値をとる演算とした Segment tree を構築します。

二項演算として関数へのポインタを渡すこともできます。

```cpp
unsigned max(unsigned x, unsigned y) {
  return (x >= y) ? x : y;
}

int main() {
  int N;
  std::cin >> N;

  lib::segment_tree tree(N, 0u, &max);  // OK
  //                            ^^^^
}
```

### メンバ関数

#### `size()`

要素数を返します。

#### `add(i, x)`

$i$ 番目 (0-indexed) の要素に $x$ を加算します。

#### `prod(l, r)`

半開区間 $[l, r)$ (0-indexed) に含まれる要素の区間積を返します。

#### `all_prod(l, r)`

全要素についての区間積を返します (`prod(0, size())` と同じ値を返します)。

#### `get(i)`

$i$ 番目 (0-indexed) の要素の値を返します。

#### `set(i, x)`

$i$ 番目 (0-indexed) の要素の値を $x$ にします。

#### `debug_print()`

[デバッグレベル](https://naskya.github.io/cp-library/about#cp_library_debug_level-%E3%83%9E%E3%82%AF%E3%83%AD)が $1$ 以上のとき、標準エラー出力にデバッグ情報(配列の内容)を出力します。

---

以下は処理をほんのり高速化させるためのメンバ関数です。使い方を間違えると `assert` マクロによって異常終了するか、正しくない計算結果が返ります。

これらの関数の使用を検討する場合、他に適したデータ構造が無いかを考えてください。

#### `lock()`

`set` 関数や `add` 関数で要素を変更した時に、その変更が自動的に親ノードに**伝播されない**ようにします。そのため `lock()` を行った後には (`unlock()` を行うまでは) 区間積は取得できなくなります。この関数を呼び、`unlock()` を行わずにもう一度この関数を呼ぶと `assert` マクロによって異常終了します。

#### `unlock()`

`set` 関数や `add` 関数で要素を変更した時に、その変更が自動的に親ノードに**伝播される**ようにします。`lock()` を呼んでいない状態でこの関数を呼ぶと `assert` マクロによって異常終了します。

この関数は内部に保持されている `locked` という変数の値を `false` にセットするだけなので、この関数を呼んだだけでは変更が親ノードへ伝播されないことに注意してください。

#### `propagate(i)`

$i$ 番目の要素の変更を親ノードに伝播します。変更が自動的に親ノードに伝播されない状態で行った変更を手動で反映させるために使います。

#### `propagate_all()`

全ての要素の変更を親ノードに伝播します。変更が自動的に親ノードに伝播されない状態で行った変更を手動で反映させるために使います。

#### `propagate_all_and_unlock()`

`propagate_all()` と `unlock()` を呼びます。

#### `is_locked()`

変更が自動的に親ノードに**伝播されない**状態になっているかどうかを返します。

---

`lock()` や `unlock()` を直接使用するとバグの原因となるので、`no_range_query_in_this_scope` クラスを通して使用するとよいです。

`no_range_query_in_this_scope` クラスのコンストラクタで自動的に `lock()` が呼ばれ、デストラクタで自動的に `propagate_all_and_unlock()` が呼ばれます。

```cpp
lib::segmant_tree tree(N);

{
  // コンストラクタが呼ばれ、tree は変更が自動的に親ノードに伝播されない状態になる
  lib::no_range_query_in_this_scope query_lock(tree);

  // 大量の変更クエリ (ここで区間積の取得はできないが、get() を使うことはできる)
  for (int i = 0; i < Q; ++i)
    tree.set(x[i], y[i]);

  // スコープを抜けるのでデストラクタが呼ばれ、tree への変更が適用される
}
```

---
