
//! @file factorial.hpp
//! @brief Factorial, Permutation, Combination, Multinomial coefficients

#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <type_traits>

#ifndef warn
#  if (CP_LIBRARY_DEBUG_LEVEL >= 1)
//! @brief Print warning message
//! @note You can suppress the warning by uncommenting line 19
#    define warn(msg) (std::cerr << (msg) << '\n')
// #  define warn(msg) (static_cast<void>(0))
#  else
#    define warn(msg) (static_cast<void>(0))
#  endif
#  define warn_not_defined
#endif

namespace lib {

namespace internal {
  template <typename... Ts>
  struct is_all_same : std::false_type {};
  template <>
  struct is_all_same<> : std::true_type {};
  template <typename Tp>
  struct is_all_same<Tp> : std::true_type {};
  template <typename Tp, typename... Ts>
  struct is_all_same<Tp, Tp, Ts...> : is_all_same<Tp, Ts...> {};
  template <typename... Ts>
  [[maybe_unused]] constexpr bool is_all_same_v = is_all_same<Ts...>::value;
  template <class Tp, class... Ts>
  struct first_type { using type = Tp; };
  template <class... Ts>
  using first_type_t = typename first_type<Ts...>::type;
}  // namespace internal

//! @tparam Tp deduced from parameter
//! @tparam ReturnType set appropriately if there is a possibility of overflow (e.g. long long, __int128, modint)
//! @param n non-negative integer (doesn't have to be primitive)
//! @return factorial of n (n!), or number of ways to arrange n distinguishable objects in any order.
//! @note Time complexity: O(n)
template <typename Tp, typename ReturnType = Tp>
[[nodiscard]] ReturnType factorial(const Tp n) {
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
//! @return nPr, or number of ways to select r out of n distinguishable objects and arrange them in any order.
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
//! @return nCr, or number of ways to select r out of n distinguishable objects.
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

//! @tparam Tp deduced from parameters
//! @tparam ReturnType set appropriately if there is a possibility of overflow (e.g. long long, __int128, modint)
//! @tparam Ts deduced from parameters
//! @param n non-negative integer
//! @param r non-negative integers of same type whose sum is less than or equal to n
//! @return Number of ways to arrange n objects when r_1, r_2, ... objects are indistinguishable.
//! @note Time complexity: O(n - max(r))
template <typename Tp, typename ReturnType = Tp, typename... Ts>
[[nodiscard]] ReturnType multinomial(const Tp n, const Ts... r) {
  static_assert(internal::is_all_same_v<Ts...>);

  if (n == 0)
    warn("n is zero.");
  if (n < 0) {
    warn("n is negative.");
    return 0;
  }
  if (((r < 0) || ...)) {
    warn("r... contains negative number.");
    return 0;
  }
  if ((r + ...) > n) {
    warn("Sum of r... is greater than n.");
    return 0;
  }
  std::array<internal::first_type_t<Ts...>, sizeof...(Ts)> r_array {r...};

  const auto max_idx = std::distance(std::cbegin(r_array), std::max_element(std::cbegin(r_array), std::cend(r_array)));
  const auto max_r   = r_array[max_idx];

  unsigned current_den_idx                      = static_cast<int>(max_idx == 0);
  internal::first_type_t<Ts...> current_den_cnt = 1;

  ReturnType res = 1;

  for (Tp i = 1; i <= n - max_r; ++i) {
    res *= (n - i + 1);
    res /= current_den_cnt;
    if (current_den_idx < sizeof...(Ts) - 1 && (current_den_cnt == r_array[current_den_idx] || current_den_idx == max_idx)) {
      current_den_idx += static_cast<int>(current_den_cnt == r_array[current_den_idx]);
      current_den_idx += static_cast<int>(current_den_idx == max_idx);
      current_den_cnt = 1;
    } else if (current_den_idx == sizeof...(Ts) - 1 && current_den_cnt == r_array[current_den_idx]) {
      current_den_cnt = 1;
    } else {
      ++current_den_cnt;
    }
  }

  return res;
}

//! @tparam Tp deduced from parameters
//! @tparam ReturnType set appropriately if there is a possibility of overflow (e.g. long long, __int128, modint)
//! @tparam Container container type (deduced from parameters)
//! @param n non-negative integer
//! @param r container of non-negative integers whose sum is less than or equal to n
//! @return Number of ways to arrange n objects when r[0], r[1], ... objects are indistinguishable.
//! @note Time complexity: O(n - max(r))
template <typename Tp, typename ReturnType = Tp, typename Container>
[[nodiscard]] ReturnType multinomial(const Tp n, const Container& r) {
  using Elem = std::decay_t<decltype(*std::cbegin(r))>;
  if (n == 0)
    warn("n is zero.");
  if (n < 0) {
    warn("n is negative.");
    return 0;
  }
  if (std::any_of(std::cbegin(r), std::cend(r), [](const auto v) { return v < 0; })) {
    warn("r contains negative number.");
    return 0;
  }
  if (std::reduce(std::cbegin(r), std::cend(r), Elem(0)) > n) {
    warn("Sum of r is greater than n.");
    return 0;
  }

  const auto max_idx = std::distance(std::cbegin(r), std::max_element(std::cbegin(r), std::cend(r)));
  const auto max_r   = r[max_idx];

  unsigned current_den_idx = static_cast<int>(max_idx == 0);
  Elem current_den_cnt     = 1;

  ReturnType res = 1;

  for (Tp i = 1; i <= n - max_r; ++i) {
    res *= (n - i + 1);
    res /= current_den_cnt;
    if (current_den_idx < std::size(r) - 1 && (current_den_cnt == r[current_den_idx] || current_den_idx == max_idx)) {
      current_den_idx += static_cast<int>(current_den_cnt == r[current_den_idx]);
      current_den_idx += static_cast<int>(current_den_idx == max_idx);
      current_den_cnt = 1;
    } else if (current_den_idx == std::size(r) - 1 && current_den_cnt == r[current_den_idx]) {
      current_den_cnt = 1;
    } else {
      ++current_den_cnt;
    }
  }

  return res;
}

//! @tparam Tp deduced from parameters
//! @tparam ReturnType set appropriately if there is a possibility of overflow (e.g. long long, __int128, modint)
//! @param n non-negative integer (doesn't have to be primitive)
//! @param r non-negative integer (doesn't have to be primitive)
//! @return nHr, or number of ways to put n indistinguishable balls into r distinguishable bins.
//! @note Time complexity: O(r)
template <typename Tp, typename ReturnType = Tp>
[[nodiscard]] ReturnType stars_and_bars(const Tp n, const Tp r) {
  return combination<Tp, ReturnType>(n + r - 1, r);
}

//! @tparam Max upper limit
//! @tparam ReturnType value type
//! @return std::array which contains 0!, 1!, ..., Max! (Max + 1 numbers)
//! @note Time complexity: O(Max)
template <std::size_t Max, typename ReturnType>
[[nodiscard]] constexpr std::array<ReturnType, Max + 1> factorial_array() {
  std::array<ReturnType, Max + 1> res;
  res[0] = 1;

  for (std::size_t i = 1; i <= Max; ++i)
    res[i] = res[i - 1] * i;

  return res;
}

//! @tparam Max upper limit
//! @tparam Modint value type (deduced from parameter, must be Modint)
//! @param fact factorial of Max (which is the result of factorial or factorial_array)
//! @return std::array which contains multiplicative inverse of 0!, 1!, ..., Max! (Max + 1 numbers)
//! @note Time complexity: O(Max)
template <std::size_t Max, typename Modint>
[[nodiscard]] constexpr std::array<Modint, Max + 1> factorial_modinv_array(const Modint fact) {
  std::array<Modint, Max + 1> res;
  res[Max] = fact.inv();

  for (std::size_t i = Max; i > 0; --i)
    res[i - 1] = res[i] * i;

  return res;
}

//! @tparam Size Size of factorial_array and factorial_modinv_array (deduced from parameters)
//! @tparam Tp deduced from parameters
//! @tparam Modint deduced from parameters
//! @param n non-negative integer
//! @param r non-negative integer
//! @param factorial_array Array that factorial_array() returns
//! @param factorial_modinv_array Array that factorial_modinv_array() returns
//! @return nPr, or number of ways to select r out of n distinguishable objects and arrange them in any order.
//! @note Time complexity: O(1)
template <std::size_t Size, typename Modint, typename Tp>
[[nodiscard]] Modint permutation(const Tp n, const Tp r, const std::array<Modint, Size>& factorial_array, const std::array<Modint, Size>& factorial_modinv_array) {
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
  return factorial_array[n] * factorial_modinv_array[n - r];
}

//! @tparam Size Size of factorial_array and factorial_modinv_array (deduced from parameters)
//! @tparam Tp deduced from parameters
//! @tparam Modint deduced from parameters
//! @param n non-negative integer
//! @param r non-negative integer
//! @param factorial_array Array that factorial_array() returns
//! @param factorial_modinv_array Array that factorial_modinv_array() returns
//! @return nCr, or number of ways to select r out of n distinguishable objects.
//! @note Time complexity: O(1)
template <std::size_t Size, typename Modint, typename Tp>
[[nodiscard]] constexpr Modint combination(const Tp n, const Tp r, const std::array<Modint, Size>& factorial_array, const std::array<Modint, Size>& factorial_modinv_array) {
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
  return factorial_array[n] * factorial_modinv_array[n - r] * factorial_modinv_array[r];
}

//! @tparam Size Size of factorial_array and factorial_modinv_array (deduced from parameters)
//! @tparam Modint deduced from parameters
//! @tparam Tp deduced from parameters
//! @tparam Ts deduced from parameters
//! @param n non-negative integer
//! @param r non-negative integers whose sum is less than or equal to n
//! @param factorial_array Array that factorial_array() returns
//! @param factorial_modinv_array Array that factorial_modinv_array() returns
//! @return Number of ways to arrange n objects when r_1, r_2, ... objects are indistinguishable.
//! @note Time complexity: O(sizeof...(r))
template <std::size_t Size, typename Modint, typename Tp, typename... Ts>
[[nodiscard]] constexpr Modint multinomial(const Tp n, const Ts... r, const std::array<Modint, Size>& factorial_array, const std::array<Modint, Size>& factorial_modinv_array) {
  if (n == 0)
    warn("n is zero.");
  if (n < 0) {
    warn("n is negative.");
    return 0;
  }
  if (((r < 0) || ...)) {
    warn("r contains negative number.");
    return 0;
  }
  if ((r + ...) > n) {
    warn("Sum of r... is greater than n.");
    return 0;
  }
  return factorial_array[n] * ((factorial_modinv_array[r]) * ...);
}

//! @tparam Size Size of factorial_array and factorial_modinv_array (deduced from parameters)
//! @tparam Modint deduced from parameters
//! @tparam Tp deduced from parameters
//! @tparam container type (deduced from parameters)
//! @param n non-negative integer
//! @param r container of non-negative integers whose sum is less than or equal to n
//! @param factorial_array Array that factorial_array() returns
//! @param factorial_modinv_array Array that factorial_modinv_array() returns
//! @return Number of ways to arrange n objects when r[0], r[1], ... objects are indistinguishable.
//! @note Time complexity: O(size(r))
template <std::size_t Size, typename Modint, typename Tp, typename Container>
[[nodiscard]] constexpr Modint multinomial(const Tp n, const Container& r, const std::array<Modint, Size>& factorial_array, const std::array<Modint, Size>& factorial_modinv_array) {
  using Elem = std::decay_t<decltype(*std::cbegin(r))>;
  if (n == 0)
    warn("n is zero.");
  if (n < 0) {
    warn("n is negative.");
    return 0;
  }
  if (std::any_of(std::cbegin(r), std::cend(r), [](const auto v) { return v < 0; })) {
    warn("r contains negative number.");
    return 0;
  }
  if (std::reduce(std::cbegin(r), std::cend(r), Elem(0)) > n) {
    warn("Sum of r is greater than n.");
    return 0;
  }
  return factorial_array[n] * std::reduce(std::cbegin(r), std::cend(r), Modint(1),
                                          [&](const Modint res, const Elem e) { return res * factorial_modinv_array[e]; });
}

//! @tparam Size Size of factorial_array and factorial_modinv_array (deduced from parameters)
//! @tparam Tp deduced from parameters
//! @tparam Modint deduced from parameters
//! @param n non-negative integer
//! @param r non-negative integers whose sum is equal to n
//! @param factorial_array Array that factorial_array() returns
//! @param factorial_modinv_array Array that factorial_modinv_array() returns
//! @return nHr, or number of ways to put n indistinguishable balls into r distinguishable bins.
//! @note Time complexity: O(1)
template <std::size_t Size, typename Modint, typename Tp>
[[nodiscard]] constexpr Modint stars_and_bars(const Tp n, const Tp r, const std::array<Modint, Size>& factorial_array, const std::array<Modint, Size>& factorial_modinv_array) {
  return combination(n + r - 1, r, factorial_array, factorial_modinv_array);
}

}  // namespace lib

#ifdef warn_not_defined
#  undef warn
#  undef warn_not_defined
// warn may be defined 2 times (by uncommenting line 19)
#  ifdef warn
#    undef warn
#  endif
#endif

#endif
