
//! @file binary_search.hpp

#ifndef CP_LIBRARY_BINARY_SEARCH_HPP
#define CP_LIBRARY_BINARY_SEARCH_HPP

#include <cassert>
#include <type_traits>
#include <utility>

#ifndef CP_LIBRARY_ASSERT
//! @brief Assert macro
#  define CP_LIBRARY_ASSERT(...) assert(__VA_ARGS__)
#  define CP_LIBRARY_ASSERT_NOT_DEFINED
#endif

namespace lib {

//! @brief Find the minimum or maximum value that satisfies the condition.
//! @tparam Tp Return type (deduced from parameters)
//! @tparam Func callable type (function reference, class with operator(), ...)
//! @param ok Initial value for which the condition is satisfied
//! @param ng Initial value for which the condition is not satisfied
//! @param f Callable object that takes 1 parameter of Tp and returns bool indicating if the condition is satisfied
//! @param diff Difference (end condition of binary search). 1 for integers, small value (e.g. 1e-9) for real numbers
//! @return minimum value (if ok < ng) or maximum value (if ok > ng)
//! @note One and only one boundary value between ok and ng must exist.
//! @note Time complexity: O(log(|ok - ng|))
template <typename Tp, typename Func>
[[nodiscard]] Tp binary_search(Tp ok, Tp ng, const Func& f, const Tp diff = 1) {
  static_assert(std::is_same_v<decltype(std::declval<Func>()(std::declval<Tp>())), bool>);
  CP_LIBRARY_ASSERT(f(ok));
  CP_LIBRARY_ASSERT(!f(ng));

  if (ok < ng)
    while (ng - ok > diff) {
      const Tp mid       = ok + (ng - ok) / 2;
      (f(mid) ? ok : ng) = mid;
    }
  else
    while (ok - ng > diff) {
      const Tp mid       = ng + (ok - ng) / 2;
      (f(mid) ? ok : ng) = mid;
    }

  return ok;
}

}  // namespace lib

#ifdef CP_LIBRARY_ASSERT_NOT_DEFINED
#  undef CP_LIBRARY_ASSERT
#  undef CP_LIBRARY_ASSERT_NOT_DEFINED
#endif

#endif  // CP_LIBRARY_BINARY_SEARCH_HPP
