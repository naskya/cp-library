
//! @file segment_tree.hpp

#ifndef SEGMENT_TREE_HPP
#define SEGMENT_TREE_HPP

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <vector>

#ifndef warn
#  if (CP_LIBRARY_DEBUG_LEVEL >= 1)
//! @brief Print warning message
//! @note You can suppress the warning by uncommenting line 21
#    define warn(msg) (std::cerr << (msg) << '\n')
// #  define warn(msg) (static_cast<void>(0))
#  else
#    define warn(msg) (static_cast<void>(0))
#  endif
#  define warn_not_defined
#endif

#ifndef O_assert
//! @brief Assert macro
#  define O_assert(...) assert(__VA_ARGS__)
#  define O_assert_not_defined
#endif

namespace lib {

namespace internal {
  template <typename Func, typename Arg>
  auto is_binary_op_of_impl(int) -> std::bool_constant<std::is_same_v<decltype(std::declval<Func>()(std::declval<Arg>(), std::declval<Arg>())), Arg>>;
  template <typename Func, typename Arg>
  auto is_binary_op_of_impl(...) -> std::false_type;

  //! @brief Check if Func(Arg, Arg) returns a value of type Arg.
  template <typename Func, typename Arg>
  [[maybe_unused]] constexpr bool is_binary_op_of_v = decltype(is_binary_op_of_impl<Func, Arg>(int {}))::value;
}  // namespace internal

//! @brief Segment tree
//! @tparam Elem element type. Watch out for overflows.
//! @tparam Func binary op type.
template <typename Elem = long long, typename Func = std::plus<>,
          std::enable_if_t<internal::is_binary_op_of_v<Func, Elem>, std::nullptr_t> = nullptr>
class segment_tree {
private:
  const int length;
  const Elem id;
  std::vector<Elem> data;
  Func binary_op;
  bool locked;

  //! @brief Propagate changes in the index-th element to its ancestors.
  //! @note Time complexity: O(log size)
  void propagate_impl(int index) {
    index += length;
    while (index > 0) {
      index >>= 1;
      data[index] = binary_op(data[index << 1], data[index << 1 | 1]);
    }
  }

public:
  //! @brief Construct a vector of n zeroes. Default operation (sum) will be selected.
  //! @param n vector size
  explicit segment_tree(const int n)
      : length(n),
        id(0),
        data(length << 1, id),
        binary_op(),
        locked(false) {}

  //! @brief Construct a vector from an existing container. Default operation (sum) will be selected.
  //! @tparam Container container type (deduced from parameter).
  //! @param src Source (container)
  template <typename Container>
  explicit segment_tree(const Container& src)
      : length(static_cast<int>(std::size(src))),
        id(0),
        data(length << 1, id),
        binary_op(),
        locked(false) {
    std::copy(std::cbegin(src), std::cend(src), std::begin(data) + length);
    for (int i = length - 1; i > 0; --i)
      data[i] = binary_op(data[i << 1], data[i << 1 | 1]);
  }

  //! @brief Construct a vector of length n filled with init_vals. Default operation (sum) will be selected.
  //! @param n vector size
  //! @param init_val initial value for all elements
  segment_tree(const int n, const Elem init_val)
      : length(n),
        id(0),
        data(length << 1, id),
        binary_op(),
        locked(false) {
    std::fill(std::begin(data) + length, std::end(data), init_val);
    for (int i = length - 1; i > 0; --i)
      data[i] = binary_op(data[i << 1], data[i << 1 | 1]);
  }

  //! @brief Construct a vector of n zeroes, specifying a binary operation and its identity element.
  //! @param n vector size
  //! @param identity_element identity element of the binary operation
  //! @param binary_operation associative binary operation (sum, product, min, max, ...)
  segment_tree(const int n, const Elem identity_element, const Func& binary_operation)
      : length(n),
        id(identity_element),
        data(length << 1, id),
        binary_op(binary_operation),
        locked(false) {}

  //! @brief Construct a vector from an existing container, specifying a binary operation and its identity element.
  //! @tparam Container container type (deduced from parameter).
  //! @param src Source (container)
  //! @param identity_element identity element of the binary operation
  //! @param binary_operation associative binary operation (sum, product, min, max, ...)
  template <typename Container>
  segment_tree(const Container& src, const Elem identity_element, const Func& binary_operation)
      : length(static_cast<int>(std::size(src))),
        id(identity_element),
        data(length << 1, id),
        binary_op(binary_operation),
        locked(false) {
    std::copy(std::cbegin(src), std::cend(src), std::begin(data) + length);
    for (int i = length - 1; i > 0; --i)
      data[i] = binary_op(data[i << 1], data[i << 1 | 1]);
  }

  //! @brief Construct a vector of length n filled with init_vals, specifying a binary operation and its identity element.
  //! @param n vector size
  //! @param init_val initial value for all elements
  //! @param identity_element identity element of the binary operation
  //! @param binary_operation associative binary operation (sum, product, min, max, ...)
  segment_tree(const int n, const Elem init_val, const Elem identity_element, const Func& binary_operation)
      : length(n),
        id(identity_element),
        data(length << 1, id),
        binary_op(binary_operation),
        locked(false) {
    std::fill(std::begin(data) + length, std::end(data), init_val);
    for (int i = length - 1; i > 0; --i)
      data[i] = binary_op(data[i << 1], data[i << 1 | 1]);
  }

  //! @brief Construct a vector of n zeroes, specifying a binary operation and its identity element.
  //! @param n vector size
  //! @param identity_element identity element of the binary operation
  //! @param binary_operation associative binary operation (sum, product, min, max, ...)
  segment_tree(const int n, const Elem identity_element, Func&& binary_operation)
      : length(n),
        id(identity_element),
        data(length << 1, id),
        binary_op(std::move(binary_operation)),
        locked(false) {}

  //! @brief Construct a vector from an existing container, specifying a binary operation and its identity element.
  //! @tparam Container container type (deduced from parameter).
  //! @param src Source (container)
  //! @param identity_element identity element of the binary operation
  //! @param binary_operation associative binary operation (sum, product, min, max, ...)
  template <typename Container>
  segment_tree(const Container& src, const Elem identity_element, Func&& binary_operation)
      : length(static_cast<int>(std::size(src))),
        id(identity_element),
        data(length << 1, id),
        binary_op(std::move(binary_operation)),
        locked(false) {
    std::copy(std::cbegin(src), std::cend(src), std::begin(data) + length);
    for (int i = length - 1; i > 0; --i)
      data[i] = binary_op(data[i << 1], data[i << 1 | 1]);
  }

  //! @brief Construct a vector of n zeroes, specifying a binary operation and its identity element.
  //! @param n vector size
  //! @param identity_element identity element of the binary operation
  //! @param binary_operation associative binary operation (sum, product, min, max, ...)
  segment_tree(const int n, const Elem init_val, const Elem identity_element, Func&& binary_operation)
      : length(n),
        id(identity_element),
        data(length << 1, id),
        binary_op(std::move(binary_operation)),
        locked(false) {
    std::fill(std::begin(data) + length, std::end(data), init_val);
    for (int i = length - 1; i > 0; --i)
      data[i] = binary_op(data[i << 1], data[i << 1 | 1]);
  }

  ~segment_tree() {
    if (locked)
      warn("Segment tree is destructed in a locked state.");
  }

  //! @return Vector size (length)
  [[nodiscard]] int size() const noexcept {
    return length;
  }

  //! @brief Add value to the index-th element.
  //! @param index index of the element to be added (0-indexed)
  //! @param value value to be added
  //! @note Time complexity: O(log size) if unlocked
  //! @note Time complexity: O(1)        if locked
  void add(const int index, const Elem value) {
    O_assert(0 <= index && index < length);
    data[index + length] = data[index + length] + value;
    if (!locked)
      propagate_impl(index);
  }

  //! @brief Set the value of the index-th element to value.
  //! @param index index (0-indexed)
  //! @param value value to be set
  //! @note Time complexity: O(log size) if unlocked
  //! @note Time complexity: O(1)        if locked
  void set(const int index, const Elem value) {
    O_assert(0 <= index && index < length);
    data[index + length] = value;
    if (!locked)
      propagate_impl(index);
  }

  //! @brief Get the value of the index-th element.
  //! @param index index (0-indexed)
  //! @note Time complexity: O(1)
  [[nodiscard]] Elem get(const int index) const {
    O_assert(0 <= index && index < length);
    return data[index + length];
  }

  //! @brief Calculate interval product.
  //! @param left lower limit of interval (0-indexed)
  //! @param right upper limit of interval (0-indexed)
  //! @return product (result of the specified binary operation) of the elements within [left, right) (half-open interval)
  //! @note Time complexity: O(log size)
  [[nodiscard]] Elem prod(int L, int R) const {
    O_assert(!locked);
    O_assert(0 <= L && L <= R && R <= length);
    L += length;
    R += length;

    Elem res_l = id, res_r = id;

    while (L < R) {
      if (L & 1) {
        res_l = binary_op(res_l, data[L]);
        ++L;
      }
      if (R & 1)
        res_r = binary_op(data[--R], res_r);
      L >>= 1;
      R >>= 1;
    }

    return binary_op(res_l, res_r);
  }

  //! @brief Calculate product of all elements.
  //! @param left lower limit of interval (0-indexed)
  //! @param right upper limit of interval (0-indexed)
  //! @return product (result of the specified binary operation) of all elements
  //! @note Time complexity: O(1)
  [[nodiscard]] Elem all_prod() const {
    O_assert(!locked);
    return data[1];
  }

  //! @warning You need to call this function ONLY IF you use lock()/unlock() function.
  //! @brief Propagate changes in the index-th element to its ancestors.
  //! @note Time complexity: O(log size)
  void propagate(int index) {
    O_assert(locked);
    O_assert(0 <= index && index < length);
    propagate_impl(index);
  }

  //! @warning You need to call this function ONLY IF you use lock()/unlock() function.
  //! @brief Propagate changes of all elements to the ancestors.
  //! @note Time complexity: O(size)
  void propagate_all() {
    O_assert(locked);
    for (int i = length - 1; i > 0; --i)
      data[i] = binary_op(data[i << 1], data[i << 1 | 1]);
  }

  //! @warning You need to call this function ONLY IF you use lock()/unlock() function.
  //! @brief Propagate changes of all elements to the ancestors and resume automatic propagation.
  //! @note Time complexity: O(size)
  void propagate_all_and_unlock() {
    propagate_all();
    unlock();
  }

  //! @warning You can call this function only if you can promise not to call prod()/all_prod() until you call unlock().
  //! @brief Stop automatic propagation on element changes.
  //! @note Time complexity: O(1)
  void lock() {
    O_assert(!locked);
    locked = true;
  }

  //! @warning You can call this function only if this segment tree is locked.
  //! @warning This function will not perform propagation. You need to call propagate()/propagate_all() manually.
  //! @brief Resume automatic propagation on element changes.
  //! @note Time complexity: O(1)
  void unlock() {
    O_assert(locked);
    locked = false;
  }

  //! @warning You need to call this function ONLY IF you use lock()/unlock() function.
  //! @return Whether the automatic propagation is stopped.
  //! @note Time complexity: O(1)
  [[nodiscard]] bool is_locked() const {
    return locked;
  }

  void debug_print([[maybe_unused]] const std::string& name = "", [[maybe_unused]] std::ostream& os = std::cerr) const {
#if (CP_LIBRARY_DEBUG_LEVEL >= 1)
    if (!name.empty())
      os << name << ": ";

    os << "val  [ ";
    for (int i = 0; i < size(); ++i)
      os << get(i) << ' ';
    os << "]\n";

    if (!name.empty())
      os << std::string(std::size(name) + 2, ' ');

    os << "prod [ ";

    if (locked)
      os << "cannot display since range product query is locked ";
    else
      for (int i = 0; i <= size(); ++i)
        os << prod(0, i) << ' ';

    os << "]\n";
#endif
  }
};

namespace internal {
  template <typename Tp>
  [[maybe_unused]] constexpr bool is_segment_tree_v = false;
  template <typename Elem, typename Func>
  [[maybe_unused]] constexpr bool is_segment_tree_v<segment_tree<Elem, Func>> = true;
}  // namespace internal

//! @brief Utility class to automatically call lock() in constructor and propagate_all_and_unlock() in destructor.
template <typename Tp, std::enable_if_t<internal::is_segment_tree_v<Tp>, std::nullptr_t> = nullptr>
class no_range_query_in_this_scope {
private:
  Tp& target_segtree;

public:
  //! @brief Lock segment tree by calling lock().
  //! @param segtree target segment tree
  //! @note Time complexity: O(1)
  explicit no_range_query_in_this_scope(Tp& segtree) : target_segtree(segtree) {
    target_segtree.lock();
  }
  //! @brief Unlock segment tree and apply all changes by calling propagate_all_and_unlock().
  //! @note Time complexity: O(size of target segment tree)
  ~no_range_query_in_this_scope() {
    target_segtree.propagate_all_and_unlock();
  }
};

}  // namespace lib

#ifdef warn_not_defined
#  undef warn
#  undef warn_not_defined
// warn may be defined 2 times (by uncommenting line 21)
#  ifdef warn
#    undef warn
#  endif
#endif

#ifdef O_assert_not_defined
#  undef O_assert
#  undef O_assert_not_defined
#endif

#endif  // SEGMENT_TREE_HPP
