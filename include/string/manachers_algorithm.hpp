
//! @file manachers_algorithm.hpp

#ifndef CP_LIBRARY_MANACHERS_ALGORITHM_HPP
#define CP_LIBRARY_MANACHERS_ALGORITHM_HPP

#include <deque>

namespace lib {

//! @brief Compute the length of the palindrome centered at each position using Manacher's Algorithm.
//! @tparam Container container type (deduced from parameter)
//! @param src source container (std::string, std::vector, std::deque, ...)
//! @return std::deque<int> containing palindrome lengths ("abbba" -> {1 0 1 2 5 2 1 0 1})
//! @note Time complexity: O(size(src))
template <typename Container>
[[nodiscard]] std::deque<int> palindrome_length_array(const Container& src) {
  const int N = 2 * static_cast<int>(std::size(src)) + 1;
  std::deque<int> res(N);
  int i = 0, j = 0;
  while (i < N) {
    while (i - j >= 0 && i + j < N && ((((i + j) % 2) == 0) || src[(i - j) / 2] == src[(i + j) / 2])) {
      ++j;
    }
    res[i] = j - 1;
    int k  = 1;
    while (i - k >= 0 && k + res[i - k] + 1 < j) {
      res[i + k] = res[i - k];
      ++k;
    }
    i += k;
    j -= k;
  }
  res.pop_front();
  res.pop_back();
  return res;
}

}  // namespace lib

#endif  // CP_LIBRARY_MANACHERS_ALGORITHM_HPP
