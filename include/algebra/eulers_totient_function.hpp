
//! @file eulers_totient_function.hpp

#ifndef EULERS_TOTIENT_FUNCTION_HPP
#define EULERS_TOTIENT_FUNCTION_HPP

#include <numeric>
#include <type_traits>
#include <vector>

namespace lib {

//! @brief Euler's totient function
//! @tparam Tp return type (deduced from parameter)
//! @param n positive integer
//! @return number of positive integers in [1, n] that are coprime to n
//! @note Time complexity: O(sqrt(n))
template <typename Tp>
[[nodiscard]] Tp totient_function(Tp n) {
  Tp res = n;

  using primitive_t = std::conditional_t<std::is_integral_v<Tp>, Tp, long long>;

  for (primitive_t i = 2; i <= n / i; ++i) {
    if (n % i == 0)
      res -= res / i;
    while (n % i == 0)
      n /= i;
  }

  if (n > 1)
    res -= res / n;

  return res;
}

//! @brief Euler's totient function (from 1 to n)
//! @tparam Tp return type (deduced from parameter)
//! @param n positive integer
//! @return a vector of length n+1 that contains 0, phi(1), phi(2), ..., phi(n) where phi is Euler's totient function
//! @note Time complexity: O(n log(log n))
template <typename Tp>
[[nodiscard]] std::vector<Tp> totient_function_sequence(Tp n) {
  std::vector<Tp> res(n + 1);
  std::iota(std::begin(res), std::end(res), (Tp) 0);

  using primitive_t = std::conditional_t<std::is_integral_v<Tp>, Tp, long long>;

  for (primitive_t i = 2; i <= n; ++i) {
    if (res[i] == i) {
      for (primitive_t j = i; j <= n; j += i) {
        res[j] /= i;
        res[j] *= i - 1;
      }
    }
  }

  return res;
}

}  // namespace lib

#endif  // EULERS_TOTIENT_FUNCTION_HPP
