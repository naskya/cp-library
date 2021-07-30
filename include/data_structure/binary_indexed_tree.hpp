
//! @file binary_indexed_tree.hpp

#ifndef BINARY_INDEXED_TREE_HPP
#define BINARY_INDEXED_TREE_HPP

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#ifndef O_assert
//! @brief Assert macro
#  define O_assert(...) assert(__VA_ARGS__)
#  define O_assert_not_defined
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
    //! @param n vector length
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

    //! @brief Construct a vector of length n filled with init_vals.
    //! @param n vector length
    //! @param init_val initial value for all elements
    binary_indexed_tree_impl(const int n, const Elem& init_val) : length(n), data(n + 1, (Elem) 0) {
      for (int i = 0; i < length; ++i)
        add(i, init_val);
    }

    //! @return Vector length
    [[nodiscard]] int size() const noexcept {
      return length;
    }

    //! @brief Add val to the index-th element.
    //! @param index index of the element to be added (0-indexed)
    //! @param val value to be added
    //! @note Time complexity: O(log n) where n is the vector length
    void add(int index, const Elem& val) {
      O_assert(0 <= index && index < length);
      for (++index; index <= length; index += (index & -index))
        data[index] += val;
    }

    //! @brief Calculate interval sum.
    //! @param left lower limit of interval (0-indexed)
    //! @param right upper limit of interval (0-indexed)
    //! @return Sum of the elements within [left, right) (half-open interval)
    //! @note Time complexity: O(log n) where n is the vector length
    [[nodiscard]] Elem sum(int left, int right) const {
      O_assert(0 <= left && left <= right && right <= length);
      if (left == 0)
        return partial_sum(right);
      else
        return partial_sum(right) - partial_sum(left - 1);
    }

    //! @brief Get the value of the index-th element.
    //! @param index index (0-indexed)
    //! @note Time complexity: O(log n) where n is the vector length
    [[nodiscard]] Elem get(int index) const {
      return partial_sum(index + 1) - partial_sum(index);
    }

    //! @brief Set the value of the index-th element to val.
    //! @param index index (0-indexed)
    //! @param val value to be set
    //! @note Time complexity: O(log n) where n is the vector length
    void set(const int index, const Elem& val) {
      add(index, val - get(index));
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
  //! @param n vector length
  explicit binary_indexed_tree(const int n) : bit_0(n), bit_1(n) {}

  //! @brief Construct a vector from an existing container.
  //! @tparam Container container type (deduced from parameter).
  //! @param src Source (container)
  template <typename Container>
  explicit binary_indexed_tree(const Container& src) : bit_0(src), bit_1(static_cast<int>(std::size(src))) {}

  //! @brief Construct a vector of length n filled with init_vals.
  //! @param n vector length
  //! @param init_val initial value for all elements
  binary_indexed_tree(const int n, const Elem& init_val) : bit_0(n, init_val), bit_1(n) {}

  //! @return Vector length
  [[nodiscard]] int size() const noexcept {
    return bit_0.size();
  }

  //! @brief Add val to the index-th element.
  //! @param index index of the element to be added (0-indexed)
  //! @param val value to be added
  //! @note Time complexity: O(log n) where n is the vector length
  void add(int index, const Elem& val) {
    bit_0.add(index, val);
  }

  //! @brief Add val to the elements within [left, right) (half-open interval)
  //! @param left lower limit of interval (0-indexed)
  //! @param right upper limit of interval (0-indexed)
  //! @param val value to be added
  //! @note Time complexity: O(log n) where n is the vector length
  void uniform_add(int left, int right, const Elem& val) {
    O_assert(0 <= left && left <= right && right <= size());
    if (left != size()) {
      bit_0.add(left, val * (-1) * (left - 1));
      bit_1.add(left, val);
    }
    if (right != size()) {
      bit_0.add(right, val * (right - 1));
      bit_1.add(right, val * (-1));
    }
  }

  //! @brief Calculate interval sum.
  //! @param left lower limit of interval (0-indexed)
  //! @param right upper limit of interval (0-indexed)
  //! @return Sum of the elements within [left, right) (half-open interval)
  //! @note Time complexity: O(log n) where n is the vector length
  [[nodiscard]] Elem sum(int left, int right) const {
    if (left == 0)
      return partial_sum(right);
    else
      return partial_sum(right) - partial_sum(left - 1);
  }

  //! @brief Get the value of the index-th element.
  //! @param index index (0-indexed)
  //! @note Time complexity: O(log n) where n is the vector length
  [[nodiscard]] Elem get(int index) const {
    return partial_sum(index + 1) - partial_sum(index);
  }

  //! @brief Set the value of the index-th element to val.
  //! @param index index (0-indexed)
  //! @param val value to be set
  //! @note Time complexity: O(log n) where n is the vector length
  void set(const int index, const Elem& val) {
    bit_0.add(index, val - get(index));
  }

  //! @brief Print debug information.
  //! @param name variable name
  //! @param os output stream
  void debug_print(const std::string& name = "", std::ostream& os = std::cerr) const {
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
  }
};

}  // namespace lib

#ifdef O_assert_not_defined
#  undef O_assert
#  undef O_assert_not_defined
#endif

#endif  // BINARY_INDEXED_TREE_HPP
