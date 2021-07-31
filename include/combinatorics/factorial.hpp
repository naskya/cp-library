
//! @file factorial.hpp
//! @brief Factorial, Permutation, Combination

#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

#include <array>
#include <iostream>

#ifndef warn
//! @brief Print warning message
//! @note You can suppress the warning by uncommenting line 15
#  define warn(msg) (std::cerr << (msg) << '\n')
// #  define warn(msg) (static_cast<void>(0))
#  define warn_not_defined
#endif

namespace lib {

//! @tparam Tp deduced from parameter
//! @tparam ReturnType set appropriately if there is a possibility of overflow (e.g. long long, __int128, modint)
//! @param n non-negative integer (doesn't have to be primitive)
//! @return factorial of n (n!), or number of ways to arrange n distinguishable objects in any order
//! @note Time complexity: O(n)
template <typename Tp, typename ReturnType = Tp> ReturnType factorial(const Tp n) {
  if (n < 0)
    warn("n is negative.");

  ReturnType res = 1;
  for (Tp i = 1; i <= n; ++i)
    res *= i;
  return res;
}

//! @tparam Tp deduced from parameters
//! @tparam ReturnType set appropriately if there is a possibility of overflow (e.g. long long, __int128, modint)
//! @param n non-negative integer (doesn't have to be primitive)
//! @param r non-negative integer (doesn't have to be primitive)
//! @return nPr, or number of ways to select r out of n distinguishable objects and arrange them in any order
//! @note Time complexity: O(r)
template <typename Tp, typename ReturnType = Tp>
[[nodiscard]] ReturnType permutation(const Tp n, const Tp r) {
  if (n == 0)
    warn("n is zero.");
  if (n < 0) {
    warn("n is negative.");
    return 0;
  }
  if (r < 0) {
    warn("r is negative.");
    return 0;
  }
  if (n < r) {
    warn("n is less than r.");
    return 0;
  }
  ReturnType res = 1;
  for (Tp i = n - r + 1; i <= n; ++i)
    res *= i;
  return res;
}

//! @tparam Tp deduced from parameters
//! @tparam ReturnType set appropriately if there is a possibility of overflow (e.g. long long, __int128, modint)
//! @param n non-negative integer (doesn't have to be primitive)
//! @param r non-negative integer (doesn't have to be primitive)
//! @return nCr, or number of ways to select r out of n distinguishable objects
//! @note Time complexity: O(r)
template <typename Tp, typename ReturnType = Tp>
[[nodiscard]] ReturnType combination(const Tp n, const Tp r) {
  if (n == 0)
    warn("n is zero.");
  if (n < 0) {
    warn("n is negative.");
    return 0;
  }
  if (r < 0) {
    warn("r is negative.");
    return 0;
  }
  if (n < r) {
    warn("n is less than r.");
    return 0;
  }
  ReturnType res = 1;
  for (Tp i = 1; i <= r; ++i) {
    res *= (n - r + i);
    res /= i;
  }
  return res;
}

//! @tparam Max upper limit
//! @tparam ReturnType value type
//! @return std::array which contains 0!, 1!, ..., Max! (Max + 1 numbers)
//! @note Time complexity: O(Max)
template <unsigned Max, typename ReturnType>
[[nodiscard]] constexpr std::array<ReturnType, Max + 1> factorial_array() {
  std::array<ReturnType, Max + 1> res;
  res[0] = 1;

  for (unsigned i = 1; i <= Max; ++i)
    res[i] = res[i - 1] * i;

  return res;
}

//! @tparam Max upper limit
//! @tparam Modint value type (deduced from parameter, must be Modint)
//! @param fact factorial of Max (which is the result of factorial or factorial_array)
//! @return std::array which contains multiplicative inverse of 0!, 1!, ..., Max! (Max + 1 numbers)
//! @note nPr = factorial[n] * factorial_modinv[n - r]
//! @note nCr = factorial[n] * factorial_modinv[n - r] * factorial_modinv[r]
//! @note Time complexity: O(Max)
template <unsigned Max, typename Modint>
[[nodiscard]] constexpr std::array<Modint, Max + 1> factorial_modinv_array(const Modint fact) {
  std::array<Modint, Max + 1> res;
  res[Max] = fact.inv();

  for (unsigned i = Max; i > 0; --i)
    res[i - 1] = res[i] * i;

  return res;
}

}  // namespace lib

#ifdef warn_not_defined
#  undef warn
#  undef warn_not_defined
// warn may be defined 2 times (by uncommenting line 15)
#  ifdef warn
#    undef warn
#  endif
#endif

#endif
