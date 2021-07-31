
//! @file run_length_encoding.hpp

#ifndef RUN_LENGTH_ENCODING_HPP
#define RUN_LENGTH_ENCODING_HPP

#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

#ifndef warn
//! @brief Print warning message
//! @note You can suppress the warning by uncommenting line 16
#  define warn(msg) (std::cerr << (msg) << '\n')
// #  define warn(msg) (static_cast<void>(0))
#  define warn_not_defined
#endif

namespace lib {

//! @tparam Container container type (deduced from parameters)
//! @param src source container (std::string, std::vector, std::deque, ...)
//! @return A std::vector<std::pair<element type of src, int>> which contains the RLE result.
//! @note Time complexity: O(size(src))
template <typename Container>
auto run_length_encoding(const Container& src) {
  using Elem = std::decay_t<decltype(*std::cbegin(std::declval<Container>()))>;
  if (src.empty()) {
    warn("An empty container is provided.");
    return std::vector<std::pair<Elem, int>> {};
  }
  std::vector<std::pair<Elem, int>> res {{*std::cbegin(src), 1}};
  for (auto iter1 = std::cbegin(src), iter2 = iter1 + 1; iter2 != std::cend(src); ++iter2) {
    if (*iter1 == *iter2)
      ++res.back().second;
    else
      res.emplace_back(*iter2, 1);
    iter1 = iter2;
  }
  return res;
}

}  // namespace lib

#ifdef warn_not_defined
#  undef warn
#  undef warn_not_defined
// warn may be defined 2 times (by uncommenting line 16)
#  ifdef warn
#    undef warn
#  endif
#endif

#endif  // RUN_LENGTH_ENCODING_HPP
