
//! @file sparse_table.hpp
//! @details Provide a data structure to calculate interval products of associative and idempotent operations.

#ifndef SPARSE_TABLE_HPP
#define SPARSE_TABLE_HPP

#include <cassert>
#include <limits>
#include <type_traits>
#include <vector>

#ifndef O_assert
//! @brief Assert macro
#  define O_assert(...) assert(__VA_ARGS__)
#  define O_assert_not_defined
#endif

namespace lib {

namespace internal {
  [[nodiscard]] int int_log2(const int n) {
    return std::numeric_limits<int>::digits - __builtin_clz(n);
  }
}  // namespace internal

//! @brief data structure to calculate interval products of associative and idempotent operations (for static array)
//! @tparam Elem element type (deduced from constructor's parameters but can be set manually if needed)
//! @tparam Func functor type (deduced from constructor's parameters but has to be specified if you set Elem manually)
template <typename Elem, typename Func>
class sparse_table {
private:
  const int length;
  const Func& binary_op;
  std::vector<std::vector<Elem>> table;

public:
  //! @brief Construct a sparse table from source container
  //! @tparam Container container type (deduced from parameter)
  //! @param src source container
  //! @param binary_op_functor functor (must be associative & idempotent)
  //! @note Time complexity: O(N log N) where N = size(src)
  template <typename Container>
  sparse_table(const Container& src, const Func& binary_op_functor)
      : length(static_cast<int>(std::size(src))), binary_op(binary_op_functor) {
    const int M = internal::int_log2(length) + 1;

    table = std::vector(length, std::vector<Elem>(M));

    for (int i = 0; i < length; ++i)
      table[i][0] = src[i];
    for (int j = 1; j < M; ++j)
      for (int i = 0; i + (1 << j) <= length; ++i)
        table[i][j] = binary_op(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
  }

  //! @return Vector length
  [[nodiscard]] int size() const noexcept {
    return length;
  }

  //! @brief Get the value of the index-th element.
  //! @param index index (0-indexed)
  [[nodiscard]] Elem get(const int index) const {
    return table[index][0];
  }

  //! @param left lower limit of interval (0-indexed)
  //! @param right upper limit of interval (0-indexed)
  //! @return product of the elements of an interval [left, right) (half-open interval)
  //! @note Time complexity: O(1)
  [[nodiscard]] Elem query(const int left, const int right) const {
    O_assert(0 <= left && left < right && right <= length);
    const int j = internal::int_log2(right - left);
    return binary_op(table[left][j], table[right - (1 << j)][j]);
  }
};

//! @brief Deduction guide
template <typename Container, typename Func>
sparse_table(const Container&, const Func&)
  -> sparse_table<std::decay_t<decltype(*std::begin(std::declval<Container>()))>, Func>;

}  // namespace lib

#ifdef O_assert_not_defined
#  undef O_assert
#  undef O_assert_not_defined
#endif

#endif  // SPARSE_TABLE_HPP
