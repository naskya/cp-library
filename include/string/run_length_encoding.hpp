
//! @file run_length_encoding.hpp

#ifndef CP_LIBRARY_RUN_LENGTH_ENCODING_HPP
#define CP_LIBRARY_RUN_LENGTH_ENCODING_HPP

#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

#ifndef CP_LIBRARY_WARN
#  if (CP_LIBRARY_DEBUG_LEVEL >= 1)
//! @brief Print warning message
//! @note You can suppress the warning by uncommenting line 17
#    define CP_LIBRARY_WARN(msg) (std::cerr << (msg) << '\n')
// #  define CP_LIBRARY_WARN(msg) (static_cast<void>(0))
#  else
#    define CP_LIBRARY_WARN(msg) (static_cast<void>(0))
#  endif
#  define CP_LIBRARY_WARN_NOT_DEFINED
#endif

namespace lib {

//! @tparam Container container type (deduced from parameter)
//! @param src source container (std::string, std::vector, std::deque, ...)
//! @return A std::vector<std::pair<element type of src, int>> which contains the RLE result.
//! @note Time complexity: O(size(src))
template <typename Container>
[[nodiscard]] auto run_length_encoding(const Container& src) {
  using Elem = std::decay_t<decltype(*std::cbegin(std::declval<Container>()))>;
  if (src.empty()) {
    CP_LIBRARY_WARN("An empty container is provided.");
    return std::vector<std::pair<Elem, int>> {};
  }
  std::vector<std::pair<Elem, int>> res {{*std::cbegin(src), 1}};

  auto iter2 = std::cbegin(src);
  auto iter1 = iter2++;

  for (; iter2 != std::cend(src); std::advance(iter2, 2)) {
    if (*iter1 == *iter2)
      ++res.back().second;
    else
      res.emplace_back(*iter2, 1);
    std::swap(iter1, iter2);
  }
  return res;
}

}  // namespace lib

#ifdef CP_LIBRARY_WARN_NOT_DEFINED
#  undef CP_LIBRARY_WARN
#  undef CP_LIBRARY_WARN_NOT_DEFINED
#  ifdef CP_LIBRARY_WARN
#    undef CP_LIBRARY_WARN
#  endif
#endif

#endif  // CP_LIBRARY_RUN_LENGTH_ENCODING_HPP
