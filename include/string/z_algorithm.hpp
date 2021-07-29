
//! @file z_algorithm.hpp
//! @details Provide a function to calculate the length of the longest common prefix.

#ifndef Z_ALGORITHM_HPP
#define Z_ALGORITHM_HPP

#include <iterator>
#include <vector>

namespace lib {

//! @tparam Container container type (deduced from parameter). operator[] and size(Container) must be defined.
//! @param src Source (container)
//! @return Vector contains the length of the longest common prefix
//! @note Time complexity: O(size(s))
template <typename Container>
[[nodiscard]] std::vector<int> z_algorithm(const Container& src) {
  const int size = static_cast<int>(std::size(src));

  std::vector<int> res(size);
  res[0] = size;

  for (int i = 1, l = 0, r = 0; i < size; ++i) {
    if (i <= r) {
      res[i] = std::min(r - i + 1, res[i - l]);
    }
    while (i + res[i] < size && src[i + res[i]] == src[res[i]]) {
      ++res[i];
    }
    if (i + res[i] - 1 > r) {
      l = i;
      r = i + res[i] - 1;
    }
  }

  return res;
}

}  // namespace lib

#endif  // Z_ALGORITHM_HPP
