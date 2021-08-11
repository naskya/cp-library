
//! @file binary_indexed_tree.hpp

#ifndef CP_LIBRARY_BINARY_INDEXED_TREE_HPP
#define CP_LIBRARY_BINARY_INDEXED_TREE_HPP

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#ifndef CP_LIBRARY_ASSERT
//! @brief Assert macro
#  define CP_LIBRARY_ASSERT(...) assert(__VA_ARGS__)
#  define CP_LIBRARY_ASSERT_NOT_DEFINED
#endif

namespace lib {

namespace internal {
  //! @brief Normal binary indexed tree.
  //! @tparam Elem Element type. Watch out for overflows.
  template <typename Elem>
  class binary_indexed_tree_impl {
  private:
    int length;
    std::vector<Elem> data;

    //! @return Sum of the elements within [0, index) (0-indexed, half-open interval)
    [[nodiscard]] Elem partial_sum(int index) const {
      Elem res = 0;
      for (; index > 0; index -= (index & -index))
        res += data[index];
      return res;
    }

  public:
    //! @brief Construct a vector of n zeroes.
    //! @param n vector size
    explicit binary_indexed_tree_impl(const int n) : length(n), data(n + 1, (Elem) 0) {}

    //! @brief Construct a vector from an existing container.
    //! @tparam Container container type (deduced from parameter).
    //! @param src Source (container)
    template <typename Container>
    explicit binary_indexed_tree_impl(const Container& src)
        : length(static_cast<int>(std::size(src))), data(length + 1, (Elem) 0) {
      for (int i = 0; i < length; ++i)
        add(i, src[i]);
    }

    //! @brief Construct a vector of length n filled with initial_values.
    //! @param n vector size
    //! @param initial_value initial value for all elements
    binary_indexed_tree_impl(const int n, const Elem& initial_value) : length(n), data(n + 1, (Elem) 0) {
      for (int i = 0; i < length; ++i)
        add(i, initial_value);
    }

    //! @return Vector length
    [[nodiscard]] int size() const noexcept {
      return length;
    }

    //! @brief Add value to the index-th element.
    //! @param index index of the element to be added (0-indexed)
    //! @param value value to be added
    //! @note Time complexity: O(log size)
    void add(int index, const Elem& value) {
      CP_LIBRARY_ASSERT(0 <= index && index < length);
      for (++index; index <= length; index += (index & -index))
        data[index] += value;
    }

    //! @brief Calculate interval sum.
    //! @param left lower limit of interval (0-indexed)
    //! @param right upper limit of interval (0-indexed)
    //! @return Sum of the elements within [left, right) (half-open interval)
    //! @note Time complexity: O(log size)
    [[nodiscard]] Elem sum(int left, int right) const {
      CP_LIBRARY_ASSERT(0 <= left && left <= right && right <= length);
      if (left == 0)
        return partial_sum(right);
      else
        return partial_sum(right) - partial_sum(left - 1);
    }

    //! @brief Get the value of the index-th element.
    //! @param index index (0-indexed)
    //! @note Time complexity: O(log size)
    [[nodiscard]] Elem get(int index) const {
      return partial_sum(index + 1) - partial_sum(index);
    }

    //! @brief Set the value of the index-th element to value.
    //! @param index index (0-indexed)
    //! @param value value to be set
    //! @note Time complexity: O(log size)
    void set(const int index, const Elem& value) {
      add(index, value - get(index));
    }
  };
}  // namespace internal

//! @brief Binary indexed tree with uniform add function.
//! @tparam Elem Element type. Watch out for overflows.
template <typename Elem>
class binary_indexed_tree {
private:
  internal::binary_indexed_tree_impl<Elem> bit_0, bit_1;

  //! @return Sum of the elements within [0, index) (0-indexed, half-open interval)
  [[nodiscard]] Elem partial_sum(int index) const {
    return bit_0.sum(0, index) + bit_1.sum(0, index) * (index - 1);
  }

public:
  //! @brief Construct a vector of n zeroes.
  //! @param n vector size
  explicit binary_indexed_tree(const int n) : bit_0(n), bit_1(n) {}

  //! @brief Construct a vector from an existing container.
  //! @tparam Container container type (deduced from parameter).
  //! @param src Source (container)
  template <typename Container>
  explicit binary_indexed_tree(const Container& src) : bit_0(src), bit_1(static_cast<int>(std::size(src))) {}

  //! @brief Construct a vector of length n filled with initial_values.
  //! @param n vector size
  //! @param initial_value initial value for all elements
  binary_indexed_tree(const int n, const Elem& initial_value) : bit_0(n, initial_value), bit_1(n) {}

  //! @return Vector size (length)
  [[nodiscard]] int size() const noexcept {
    return bit_0.size();
  }

  //! @brief Add value to the index-th element.
  //! @param index index of the element to be added (0-indexed)
  //! @param value value to be added
  //! @note Time complexity: O(log size)
  void add(int index, const Elem& value) {
    bit_0.add(index, value);
  }

  //! @brief Add value to the elements within [left, right) (half-open interval)
  //! @param left lower limit of interval (0-indexed)
  //! @param right upper limit of interval (0-indexed)
  //! @param value value to be added
  //! @note Time complexity: O(log size)
  void uniform_add(int left, int right, const Elem& value) {
    CP_LIBRARY_ASSERT(0 <= left && left <= right && right <= size());
    if (left != size()) {
      bit_0.add(left, value * (-1) * (left - 1));
      bit_1.add(left, value);
    }
    if (right != size()) {
      bit_0.add(right, value * (right - 1));
      bit_1.add(right, value * (-1));
    }
  }

  //! @brief Calculate interval sum.
  //! @param left lower limit of interval (0-indexed)
  //! @param right upper limit of interval (0-indexed)
  //! @return Sum of the elements within [left, right) (half-open interval)
  //! @note Time complexity: O(log size)
  [[nodiscard]] Elem sum(int left, int right) const {
    if (left == 0)
      return partial_sum(right);
    else
      return partial_sum(right) - partial_sum(left - 1);
  }

  //! @brief Get the value of the index-th element.
  //! @param index index (0-indexed)
  //! @note Time complexity: O(log size)
  [[nodiscard]] Elem get(int index) const {
    return partial_sum(index + 1) - partial_sum(index);
  }

  //! @brief Set the value of the index-th element to value.
  //! @param index index (0-indexed)
  //! @param value value to be set
  //! @note Time complexity: O(log size)
  void set(const int index, const Elem& value) {
    bit_0.add(index, value - get(index));
  }

  //! @brief Print debug information.
  //! @param name variable name
  //! @param os output stream
  void debug_print([[maybe_unused]] const std::string& name = "", [[maybe_unused]] std::ostream& os = std::cerr) const {
#if (CP_LIBRARY_DEBUG_LEVEL >= 1)
    if (!name.empty())
      os << name << ": ";

    os << "val [ ";
    for (int i = 0; i < size(); ++i)
      os << get(i) << ' ';
    os << "]\n";

    if (!name.empty())
      os << std::string(std::size(name) + 2, ' ');

    os << "sum [ ";
    for (int i = 0; i <= size(); ++i)
      os << partial_sum(i) << ' ';
    os << "]\n";
#endif
  }
};

}  // namespace lib

#ifdef CP_LIBRARY_ASSERT_NOT_DEFINED
#  undef CP_LIBRARY_ASSERT
#  undef CP_LIBRARY_ASSERT_NOT_DEFINED
#endif

#endif  // CP_LIBRARY_BINARY_INDEXED_TREE_HPP
