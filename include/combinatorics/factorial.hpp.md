---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/combinatorics/factorial/1.test.cpp
    title: test/combinatorics/factorial/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/combinatorics/factorial/2.test.cpp
    title: test/combinatorics/factorial/2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Factorial, Permutation, Combination, Multinomial coefficients
    links: []
  bundledCode: "#line 1 \"include/combinatorics/factorial.hpp\"\n\n//! @file factorial.hpp\n\
    //! @brief Factorial, Permutation, Combination, Multinomial coefficients\n\n#ifndef\
    \ FACTORIAL_HPP\n#define FACTORIAL_HPP\n\n#include <algorithm>\n#include <array>\n\
    #include <iostream>\n#include <numeric>\n#include <type_traits>\n\n#ifndef warn\n\
    #  ifndef ONLINE_JUDGE\n//! @brief Print warning message\n//! @note You can suppress\
    \ the warning by uncommenting line 19\n#    define warn(msg) (std::cerr << (msg)\
    \ << '\\n')\n// #  define warn(msg) (static_cast<void>(0))\n#  else\n#    define\
    \ warn(msg) (static_cast<void>(0))\n#  endif\n#  define warn_not_defined\n#endif\n\
    \nnamespace lib {\n\nnamespace internal {\n  template <typename... Ts>\n  struct\
    \ is_all_same : std::false_type {};\n  template <>\n  struct is_all_same<> : std::true_type\
    \ {};\n  template <typename Tp>\n  struct is_all_same<Tp> : std::true_type {};\n\
    \  template <typename Tp, typename... Ts>\n  struct is_all_same<Tp, Tp, Ts...>\
    \ : is_all_same<Tp, Ts...> {};\n  template <typename... Ts>\n  [[maybe_unused]]\
    \ constexpr bool is_all_same_v = is_all_same<Ts...>::value;\n  template <class\
    \ Tp, class... Ts>\n  struct first_type { using type = Tp; };\n  template <class...\
    \ Ts>\n  using first_type_t = typename first_type<Ts...>::type;\n}  // namespace\
    \ internal\n\n//! @tparam Tp deduced from parameter\n//! @tparam ReturnType set\
    \ appropriately if there is a possibility of overflow (e.g. long long, __int128,\
    \ modint)\n//! @param n non-negative integer (doesn't have to be primitive)\n\
    //! @return factorial of n (n!), or number of ways to arrange n distinguishable\
    \ objects in any order.\n//! @note Time complexity: O(n)\ntemplate <typename Tp,\
    \ typename ReturnType = Tp>\n[[nodiscard]] ReturnType factorial(const Tp n) {\n\
    \  if (n < 0)\n    warn(\"n is negative.\");\n\n  ReturnType res = 1;\n  for (Tp\
    \ i = 1; i <= n; ++i)\n    res *= i;\n  return res;\n}\n\n//! @tparam Tp deduced\
    \ from parameters\n//! @tparam ReturnType set appropriately if there is a possibility\
    \ of overflow (e.g. long long, __int128, modint)\n//! @param n non-negative integer\
    \ (doesn't have to be primitive)\n//! @param r non-negative integer (doesn't have\
    \ to be primitive)\n//! @return nPr, or number of ways to select r out of n distinguishable\
    \ objects and arrange them in any order.\n//! @note Time complexity: O(r)\ntemplate\
    \ <typename Tp, typename ReturnType = Tp>\n[[nodiscard]] ReturnType permutation(const\
    \ Tp n, const Tp r) {\n  if (n == 0)\n    warn(\"n is zero.\");\n  if (n < 0)\
    \ {\n    warn(\"n is negative.\");\n    return 0;\n  }\n  if (r < 0) {\n    warn(\"\
    r is negative.\");\n    return 0;\n  }\n  if (n < r) {\n    warn(\"n is less than\
    \ r.\");\n    return 0;\n  }\n  ReturnType res = 1;\n  for (Tp i = n - r + 1;\
    \ i <= n; ++i)\n    res *= i;\n  return res;\n}\n\n//! @tparam Tp deduced from\
    \ parameters\n//! @tparam ReturnType set appropriately if there is a possibility\
    \ of overflow (e.g. long long, __int128, modint)\n//! @param n non-negative integer\
    \ (doesn't have to be primitive)\n//! @param r non-negative integer (doesn't have\
    \ to be primitive)\n//! @return nCr, or number of ways to select r out of n distinguishable\
    \ objects.\n//! @note Time complexity: O(r)\ntemplate <typename Tp, typename ReturnType\
    \ = Tp>\n[[nodiscard]] ReturnType combination(const Tp n, const Tp r) {\n  if\
    \ (n == 0)\n    warn(\"n is zero.\");\n  if (n < 0) {\n    warn(\"n is negative.\"\
    );\n    return 0;\n  }\n  if (r < 0) {\n    warn(\"r is negative.\");\n    return\
    \ 0;\n  }\n  if (n < r) {\n    warn(\"n is less than r.\");\n    return 0;\n \
    \ }\n  ReturnType res = 1;\n  for (Tp i = 1; i <= r; ++i) {\n    res *= (n - r\
    \ + i);\n    res /= i;\n  }\n  return res;\n}\n\n//! @tparam Tp deduced from parameters\n\
    //! @tparam ReturnType set appropriately if there is a possibility of overflow\
    \ (e.g. long long, __int128, modint)\n//! @tparam Ts deduced from parameters\n\
    //! @param n non-negative integer\n//! @param r non-negative integers of same\
    \ type whose sum is equal to n\n//! @return Number of ways to arrange n objects\
    \ when r_1, r_2, ... objects are indistinguishable.\n//! @note Time complexity:\
    \ O(n - max(r))\ntemplate <typename Tp, typename ReturnType = Tp, typename...\
    \ Ts>\n[[nodiscard]] ReturnType multinomial(const Tp n, const Ts... r) {\n  static_assert(internal::is_all_same_v<Ts...>);\n\
    \n  if (n == 0)\n    warn(\"n is zero.\");\n  if (n < 0) {\n    warn(\"n is negative.\"\
    );\n    return 0;\n  }\n  if (((r < 0) || ...)) {\n    warn(\"r... contains negative\
    \ number.\");\n    return 0;\n  }\n  if ((r + ...) != n) {\n    warn(\"Sum of\
    \ r... is not equal to n.\");\n    return 0;\n  }\n  std::array<internal::first_type_t<Ts...>,\
    \ sizeof...(Ts)> r_array {r...};\n\n  const auto max_idx = std::distance(std::cbegin(r_array),\
    \ std::max_element(std::cbegin(r_array), std::cend(r_array)));\n  const auto max_r\
    \   = r_array[max_idx];\n\n  unsigned current_den_idx                      = static_cast<int>(max_idx\
    \ == 0);\n  internal::first_type_t<Ts...> current_den_cnt = 1;\n\n  ReturnType\
    \ res = 1;\n\n  for (Tp i = 1; i <= n - max_r; ++i) {\n    res *= (n - i + 1);\n\
    \    res /= current_den_cnt;\n    if (current_den_idx < sizeof...(Ts) - 1 && (current_den_cnt\
    \ == r_array[current_den_idx] || current_den_idx == max_idx)) {\n      current_den_idx\
    \ += static_cast<int>(current_den_cnt == r_array[current_den_idx]);\n      current_den_idx\
    \ += static_cast<int>(current_den_idx == max_idx);\n      current_den_cnt = 1;\n\
    \    } else if (current_den_idx == sizeof...(Ts) - 1 && current_den_cnt == r_array[current_den_idx])\
    \ {\n      current_den_cnt = 1;\n    } else {\n      ++current_den_cnt;\n    }\n\
    \  }\n\n  return res;\n}\n\n//! @tparam Tp deduced from parameters\n//! @tparam\
    \ ReturnType set appropriately if there is a possibility of overflow (e.g. long\
    \ long, __int128, modint)\n//! @tparam Container container type (deduced from\
    \ parameters)\n//! @param n non-negative integer\n//! @param r container of non-negative\
    \ integers whose sum is equal to n\n//! @return Number of ways to arrange n objects\
    \ when r[0], r[1], ... objects are indistinguishable.\n//! @note Time complexity:\
    \ O(n - max(r))\ntemplate <typename Tp, typename ReturnType = Tp, typename Container>\n\
    [[nodiscard]] ReturnType multinomial(const Tp n, const Container& r) {\n  using\
    \ Elem = std::decay_t<decltype(*std::cbegin(r))>;\n  if (n == 0)\n    warn(\"\
    n is zero.\");\n  if (n < 0) {\n    warn(\"n is negative.\");\n    return 0;\n\
    \  }\n  if (std::any_of(std::cbegin(r), std::cend(r), [](const auto v) { return\
    \ v < 0; })) {\n    warn(\"r contains negative number.\");\n    return 0;\n  }\n\
    \  if (std::reduce(std::cbegin(r), std::cend(r), Elem(0)) != n) {\n    warn(\"\
    Sum of r is not equal to n.\");\n    return 0;\n  }\n\n  const auto max_idx =\
    \ std::distance(std::cbegin(r), std::max_element(std::cbegin(r), std::cend(r)));\n\
    \  const auto max_r   = r[max_idx];\n\n  unsigned current_den_idx = static_cast<int>(max_idx\
    \ == 0);\n  Elem current_den_cnt     = 1;\n\n  ReturnType res = 1;\n\n  for (Tp\
    \ i = 1; i <= n - max_r; ++i) {\n    res *= (n - i + 1);\n    res /= current_den_cnt;\n\
    \    if (current_den_idx < std::size(r) - 1 && (current_den_cnt == r[current_den_idx]\
    \ || current_den_idx == max_idx)) {\n      current_den_idx += static_cast<int>(current_den_cnt\
    \ == r[current_den_idx]);\n      current_den_idx += static_cast<int>(current_den_idx\
    \ == max_idx);\n      current_den_cnt = 1;\n    } else if (current_den_idx ==\
    \ std::size(r) - 1 && current_den_cnt == r[current_den_idx]) {\n      current_den_cnt\
    \ = 1;\n    } else {\n      ++current_den_cnt;\n    }\n  }\n\n  return res;\n\
    }\n\n//! @tparam Tp deduced from parameters\n//! @tparam ReturnType set appropriately\
    \ if there is a possibility of overflow (e.g. long long, __int128, modint)\n//!\
    \ @param n non-negative integer (doesn't have to be primitive)\n//! @param r non-negative\
    \ integer (doesn't have to be primitive)\n//! @return nHr, or number of ways to\
    \ put n indistinguishable balls into r distinguishable bins.\n//! @note Time complexity:\
    \ O(r)\ntemplate <typename Tp, typename ReturnType = Tp>\n[[nodiscard]] ReturnType\
    \ stars_and_bars(const Tp n, const Tp r) {\n  return combination<Tp, ReturnType>(n\
    \ + r - 1, r);\n}\n\n//! @tparam Max upper limit\n//! @tparam ReturnType value\
    \ type\n//! @return std::array which contains 0!, 1!, ..., Max! (Max + 1 numbers)\n\
    //! @note Time complexity: O(Max)\ntemplate <std::size_t Max, typename ReturnType>\n\
    [[nodiscard]] constexpr std::array<ReturnType, Max + 1> factorial_array() {\n\
    \  std::array<ReturnType, Max + 1> res;\n  res[0] = 1;\n\n  for (std::size_t i\
    \ = 1; i <= Max; ++i)\n    res[i] = res[i - 1] * i;\n\n  return res;\n}\n\n//!\
    \ @tparam Max upper limit\n//! @tparam Modint value type (deduced from parameter,\
    \ must be Modint)\n//! @param fact factorial of Max (which is the result of factorial\
    \ or factorial_array)\n//! @return std::array which contains multiplicative inverse\
    \ of 0!, 1!, ..., Max! (Max + 1 numbers)\n//! @note Time complexity: O(Max)\n\
    template <std::size_t Max, typename Modint>\n[[nodiscard]] constexpr std::array<Modint,\
    \ Max + 1> factorial_modinv_array(const Modint fact) {\n  std::array<Modint, Max\
    \ + 1> res;\n  res[Max] = fact.inv();\n\n  for (std::size_t i = Max; i > 0; --i)\n\
    \    res[i - 1] = res[i] * i;\n\n  return res;\n}\n\n//! @tparam Size Size of\
    \ factorial_array and factorial_modinv_array (deduced from parameters)\n//! @tparam\
    \ Tp deduced from parameters\n//! @tparam Modint deduced from parameters\n//!\
    \ @param n non-negative integer\n//! @param r non-negative integer\n//! @param\
    \ factorial_array Array that factorial_array() returns\n//! @param factorial_modinv_array\
    \ Array that factorial_modinv_array() returns\n//! @return nPr, or number of ways\
    \ to select r out of n distinguishable objects and arrange them in any order.\n\
    //! @note Time complexity: O(1)\ntemplate <std::size_t Size, typename Modint,\
    \ typename Tp>\n[[nodiscard]] Modint permutation(const Tp n, const Tp r, const\
    \ std::array<Modint, Size>& factorial_array, const std::array<Modint, Size>& factorial_modinv_array)\
    \ {\n  if (n == 0)\n    warn(\"n is zero.\");\n  if (n < 0) {\n    warn(\"n is\
    \ negative.\");\n    return 0;\n  }\n  if (r < 0) {\n    warn(\"r is negative.\"\
    );\n    return 0;\n  }\n  if (n < r) {\n    warn(\"n is less than r.\");\n   \
    \ return 0;\n  }\n  return factorial_array[n] * factorial_modinv_array[n - r];\n\
    }\n\n//! @tparam Size Size of factorial_array and factorial_modinv_array (deduced\
    \ from parameters)\n//! @tparam Tp deduced from parameters\n//! @tparam Modint\
    \ deduced from parameters\n//! @param n non-negative integer\n//! @param r non-negative\
    \ integer\n//! @param factorial_array Array that factorial_array() returns\n//!\
    \ @param factorial_modinv_array Array that factorial_modinv_array() returns\n\
    //! @return nCr, or number of ways to select r out of n distinguishable objects.\n\
    //! @note Time complexity: O(1)\ntemplate <std::size_t Size, typename Modint,\
    \ typename Tp>\n[[nodiscard]] constexpr Modint combination(const Tp n, const Tp\
    \ r, const std::array<Modint, Size>& factorial_array, const std::array<Modint,\
    \ Size>& factorial_modinv_array) {\n  if (n == 0)\n    warn(\"n is zero.\");\n\
    \  if (n < 0) {\n    warn(\"n is negative.\");\n    return 0;\n  }\n  if (r <\
    \ 0) {\n    warn(\"r is negative.\");\n    return 0;\n  }\n  if (n < r) {\n  \
    \  warn(\"n is less than r.\");\n    return 0;\n  }\n  return factorial_array[n]\
    \ * factorial_modinv_array[n - r] * factorial_modinv_array[r];\n}\n\n//! @tparam\
    \ Size Size of factorial_array and factorial_modinv_array (deduced from parameters)\n\
    //! @tparam Modint deduced from parameters\n//! @tparam Tp deduced from parameters\n\
    //! @tparam Ts deduced from parameters\n//! @param n non-negative integer\n//!\
    \ @param r non-negative integers whose sum is equal to n\n//! @param factorial_array\
    \ Array that factorial_array() returns\n//! @param factorial_modinv_array Array\
    \ that factorial_modinv_array() returns\n//! @return Number of ways to arrange\
    \ n objects when r_1, r_2, ... objects are indistinguishable.\n//! @note Time\
    \ complexity: O(sizeof...(r))\ntemplate <std::size_t Size, typename Modint, typename\
    \ Tp, typename... Ts>\n[[nodiscard]] constexpr Modint multinomial(const Tp n,\
    \ const Ts... r, const std::array<Modint, Size>& factorial_array, const std::array<Modint,\
    \ Size>& factorial_modinv_array) {\n  if (n == 0)\n    warn(\"n is zero.\");\n\
    \  if (n < 0) {\n    warn(\"n is negative.\");\n    return 0;\n  }\n  if (((r\
    \ < 0) || ...)) {\n    warn(\"r contains negative number.\");\n    return 0;\n\
    \  }\n  if ((r + ...) != n) {\n    warn(\"Sum of r... is not equal to n.\");\n\
    \    return 0;\n  }\n  return factorial_array[n] * ((factorial_modinv_array[r])\
    \ * ...);\n}\n\n//! @tparam Size Size of factorial_array and factorial_modinv_array\
    \ (deduced from parameters)\n//! @tparam Modint deduced from parameters\n//! @tparam\
    \ Tp deduced from parameters\n//! @tparam container type (deduced from parameters)\n\
    //! @param n non-negative integer\n//! @param r container of non-negative integers\
    \ whose sum is equal to n\n//! @param factorial_array Array that factorial_array()\
    \ returns\n//! @param factorial_modinv_array Array that factorial_modinv_array()\
    \ returns\n//! @return Number of ways to arrange n objects when r[0], r[1], ...\
    \ objects are indistinguishable.\n//! @note Time complexity: O(size(r))\ntemplate\
    \ <std::size_t Size, typename Modint, typename Tp, typename Container>\n[[nodiscard]]\
    \ constexpr Modint multinomial(const Tp n, const Container& r, const std::array<Modint,\
    \ Size>& factorial_array, const std::array<Modint, Size>& factorial_modinv_array)\
    \ {\n  using Elem = std::decay_t<decltype(*std::cbegin(r))>;\n  if (n == 0)\n\
    \    warn(\"n is zero.\");\n  if (n < 0) {\n    warn(\"n is negative.\");\n  \
    \  return 0;\n  }\n  if (std::any_of(std::cbegin(r), std::cend(r), [](const auto\
    \ v) { return v < 0; })) {\n    warn(\"r contains negative number.\");\n    return\
    \ 0;\n  }\n  if (std::reduce(std::cbegin(r), std::cend(r), Elem(0)) != n) {\n\
    \    warn(\"Sum of r is not equal to n.\");\n    return 0;\n  }\n  return factorial_array[n]\
    \ * std::reduce(std::cbegin(r), std::cend(r), Modint(1),\n                   \
    \                       [&](const Modint res, const Elem e) { return res * factorial_modinv_array[e];\
    \ });\n}\n\n//! @tparam Size Size of factorial_array and factorial_modinv_array\
    \ (deduced from parameters)\n//! @tparam Tp deduced from parameters\n//! @tparam\
    \ Modint deduced from parameters\n//! @param n non-negative integer\n//! @param\
    \ r non-negative integers whose sum is equal to n\n//! @param factorial_array\
    \ Array that factorial_array() returns\n//! @param factorial_modinv_array Array\
    \ that factorial_modinv_array() returns\n//! @return nHr, or number of ways to\
    \ put n indistinguishable balls into r distinguishable bins.\n//! @note Time complexity:\
    \ O(1)\ntemplate <std::size_t Size, typename Modint, typename Tp>\n[[nodiscard]]\
    \ constexpr Modint stars_and_bars(const Tp n, const Tp r, const std::array<Modint,\
    \ Size>& factorial_array, const std::array<Modint, Size>& factorial_modinv_array)\
    \ {\n  return combination(n + r - 1, r, factorial_array, factorial_modinv_array);\n\
    }\n\n}  // namespace lib\n\n#ifdef warn_not_defined\n#  undef warn\n#  undef warn_not_defined\n\
    // warn may be defined 2 times (by uncommenting line 19)\n#  ifdef warn\n#   \
    \ undef warn\n#  endif\n#endif\n\n#endif\n"
  code: "\n//! @file factorial.hpp\n//! @brief Factorial, Permutation, Combination,\
    \ Multinomial coefficients\n\n#ifndef FACTORIAL_HPP\n#define FACTORIAL_HPP\n\n\
    #include <algorithm>\n#include <array>\n#include <iostream>\n#include <numeric>\n\
    #include <type_traits>\n\n#ifndef warn\n#  ifndef ONLINE_JUDGE\n//! @brief Print\
    \ warning message\n//! @note You can suppress the warning by uncommenting line\
    \ 19\n#    define warn(msg) (std::cerr << (msg) << '\\n')\n// #  define warn(msg)\
    \ (static_cast<void>(0))\n#  else\n#    define warn(msg) (static_cast<void>(0))\n\
    #  endif\n#  define warn_not_defined\n#endif\n\nnamespace lib {\n\nnamespace internal\
    \ {\n  template <typename... Ts>\n  struct is_all_same : std::false_type {};\n\
    \  template <>\n  struct is_all_same<> : std::true_type {};\n  template <typename\
    \ Tp>\n  struct is_all_same<Tp> : std::true_type {};\n  template <typename Tp,\
    \ typename... Ts>\n  struct is_all_same<Tp, Tp, Ts...> : is_all_same<Tp, Ts...>\
    \ {};\n  template <typename... Ts>\n  [[maybe_unused]] constexpr bool is_all_same_v\
    \ = is_all_same<Ts...>::value;\n  template <class Tp, class... Ts>\n  struct first_type\
    \ { using type = Tp; };\n  template <class... Ts>\n  using first_type_t = typename\
    \ first_type<Ts...>::type;\n}  // namespace internal\n\n//! @tparam Tp deduced\
    \ from parameter\n//! @tparam ReturnType set appropriately if there is a possibility\
    \ of overflow (e.g. long long, __int128, modint)\n//! @param n non-negative integer\
    \ (doesn't have to be primitive)\n//! @return factorial of n (n!), or number of\
    \ ways to arrange n distinguishable objects in any order.\n//! @note Time complexity:\
    \ O(n)\ntemplate <typename Tp, typename ReturnType = Tp>\n[[nodiscard]] ReturnType\
    \ factorial(const Tp n) {\n  if (n < 0)\n    warn(\"n is negative.\");\n\n  ReturnType\
    \ res = 1;\n  for (Tp i = 1; i <= n; ++i)\n    res *= i;\n  return res;\n}\n\n\
    //! @tparam Tp deduced from parameters\n//! @tparam ReturnType set appropriately\
    \ if there is a possibility of overflow (e.g. long long, __int128, modint)\n//!\
    \ @param n non-negative integer (doesn't have to be primitive)\n//! @param r non-negative\
    \ integer (doesn't have to be primitive)\n//! @return nPr, or number of ways to\
    \ select r out of n distinguishable objects and arrange them in any order.\n//!\
    \ @note Time complexity: O(r)\ntemplate <typename Tp, typename ReturnType = Tp>\n\
    [[nodiscard]] ReturnType permutation(const Tp n, const Tp r) {\n  if (n == 0)\n\
    \    warn(\"n is zero.\");\n  if (n < 0) {\n    warn(\"n is negative.\");\n  \
    \  return 0;\n  }\n  if (r < 0) {\n    warn(\"r is negative.\");\n    return 0;\n\
    \  }\n  if (n < r) {\n    warn(\"n is less than r.\");\n    return 0;\n  }\n \
    \ ReturnType res = 1;\n  for (Tp i = n - r + 1; i <= n; ++i)\n    res *= i;\n\
    \  return res;\n}\n\n//! @tparam Tp deduced from parameters\n//! @tparam ReturnType\
    \ set appropriately if there is a possibility of overflow (e.g. long long, __int128,\
    \ modint)\n//! @param n non-negative integer (doesn't have to be primitive)\n\
    //! @param r non-negative integer (doesn't have to be primitive)\n//! @return\
    \ nCr, or number of ways to select r out of n distinguishable objects.\n//! @note\
    \ Time complexity: O(r)\ntemplate <typename Tp, typename ReturnType = Tp>\n[[nodiscard]]\
    \ ReturnType combination(const Tp n, const Tp r) {\n  if (n == 0)\n    warn(\"\
    n is zero.\");\n  if (n < 0) {\n    warn(\"n is negative.\");\n    return 0;\n\
    \  }\n  if (r < 0) {\n    warn(\"r is negative.\");\n    return 0;\n  }\n  if\
    \ (n < r) {\n    warn(\"n is less than r.\");\n    return 0;\n  }\n  ReturnType\
    \ res = 1;\n  for (Tp i = 1; i <= r; ++i) {\n    res *= (n - r + i);\n    res\
    \ /= i;\n  }\n  return res;\n}\n\n//! @tparam Tp deduced from parameters\n//!\
    \ @tparam ReturnType set appropriately if there is a possibility of overflow (e.g.\
    \ long long, __int128, modint)\n//! @tparam Ts deduced from parameters\n//! @param\
    \ n non-negative integer\n//! @param r non-negative integers of same type whose\
    \ sum is equal to n\n//! @return Number of ways to arrange n objects when r_1,\
    \ r_2, ... objects are indistinguishable.\n//! @note Time complexity: O(n - max(r))\n\
    template <typename Tp, typename ReturnType = Tp, typename... Ts>\n[[nodiscard]]\
    \ ReturnType multinomial(const Tp n, const Ts... r) {\n  static_assert(internal::is_all_same_v<Ts...>);\n\
    \n  if (n == 0)\n    warn(\"n is zero.\");\n  if (n < 0) {\n    warn(\"n is negative.\"\
    );\n    return 0;\n  }\n  if (((r < 0) || ...)) {\n    warn(\"r... contains negative\
    \ number.\");\n    return 0;\n  }\n  if ((r + ...) != n) {\n    warn(\"Sum of\
    \ r... is not equal to n.\");\n    return 0;\n  }\n  std::array<internal::first_type_t<Ts...>,\
    \ sizeof...(Ts)> r_array {r...};\n\n  const auto max_idx = std::distance(std::cbegin(r_array),\
    \ std::max_element(std::cbegin(r_array), std::cend(r_array)));\n  const auto max_r\
    \   = r_array[max_idx];\n\n  unsigned current_den_idx                      = static_cast<int>(max_idx\
    \ == 0);\n  internal::first_type_t<Ts...> current_den_cnt = 1;\n\n  ReturnType\
    \ res = 1;\n\n  for (Tp i = 1; i <= n - max_r; ++i) {\n    res *= (n - i + 1);\n\
    \    res /= current_den_cnt;\n    if (current_den_idx < sizeof...(Ts) - 1 && (current_den_cnt\
    \ == r_array[current_den_idx] || current_den_idx == max_idx)) {\n      current_den_idx\
    \ += static_cast<int>(current_den_cnt == r_array[current_den_idx]);\n      current_den_idx\
    \ += static_cast<int>(current_den_idx == max_idx);\n      current_den_cnt = 1;\n\
    \    } else if (current_den_idx == sizeof...(Ts) - 1 && current_den_cnt == r_array[current_den_idx])\
    \ {\n      current_den_cnt = 1;\n    } else {\n      ++current_den_cnt;\n    }\n\
    \  }\n\n  return res;\n}\n\n//! @tparam Tp deduced from parameters\n//! @tparam\
    \ ReturnType set appropriately if there is a possibility of overflow (e.g. long\
    \ long, __int128, modint)\n//! @tparam Container container type (deduced from\
    \ parameters)\n//! @param n non-negative integer\n//! @param r container of non-negative\
    \ integers whose sum is equal to n\n//! @return Number of ways to arrange n objects\
    \ when r[0], r[1], ... objects are indistinguishable.\n//! @note Time complexity:\
    \ O(n - max(r))\ntemplate <typename Tp, typename ReturnType = Tp, typename Container>\n\
    [[nodiscard]] ReturnType multinomial(const Tp n, const Container& r) {\n  using\
    \ Elem = std::decay_t<decltype(*std::cbegin(r))>;\n  if (n == 0)\n    warn(\"\
    n is zero.\");\n  if (n < 0) {\n    warn(\"n is negative.\");\n    return 0;\n\
    \  }\n  if (std::any_of(std::cbegin(r), std::cend(r), [](const auto v) { return\
    \ v < 0; })) {\n    warn(\"r contains negative number.\");\n    return 0;\n  }\n\
    \  if (std::reduce(std::cbegin(r), std::cend(r), Elem(0)) != n) {\n    warn(\"\
    Sum of r is not equal to n.\");\n    return 0;\n  }\n\n  const auto max_idx =\
    \ std::distance(std::cbegin(r), std::max_element(std::cbegin(r), std::cend(r)));\n\
    \  const auto max_r   = r[max_idx];\n\n  unsigned current_den_idx = static_cast<int>(max_idx\
    \ == 0);\n  Elem current_den_cnt     = 1;\n\n  ReturnType res = 1;\n\n  for (Tp\
    \ i = 1; i <= n - max_r; ++i) {\n    res *= (n - i + 1);\n    res /= current_den_cnt;\n\
    \    if (current_den_idx < std::size(r) - 1 && (current_den_cnt == r[current_den_idx]\
    \ || current_den_idx == max_idx)) {\n      current_den_idx += static_cast<int>(current_den_cnt\
    \ == r[current_den_idx]);\n      current_den_idx += static_cast<int>(current_den_idx\
    \ == max_idx);\n      current_den_cnt = 1;\n    } else if (current_den_idx ==\
    \ std::size(r) - 1 && current_den_cnt == r[current_den_idx]) {\n      current_den_cnt\
    \ = 1;\n    } else {\n      ++current_den_cnt;\n    }\n  }\n\n  return res;\n\
    }\n\n//! @tparam Tp deduced from parameters\n//! @tparam ReturnType set appropriately\
    \ if there is a possibility of overflow (e.g. long long, __int128, modint)\n//!\
    \ @param n non-negative integer (doesn't have to be primitive)\n//! @param r non-negative\
    \ integer (doesn't have to be primitive)\n//! @return nHr, or number of ways to\
    \ put n indistinguishable balls into r distinguishable bins.\n//! @note Time complexity:\
    \ O(r)\ntemplate <typename Tp, typename ReturnType = Tp>\n[[nodiscard]] ReturnType\
    \ stars_and_bars(const Tp n, const Tp r) {\n  return combination<Tp, ReturnType>(n\
    \ + r - 1, r);\n}\n\n//! @tparam Max upper limit\n//! @tparam ReturnType value\
    \ type\n//! @return std::array which contains 0!, 1!, ..., Max! (Max + 1 numbers)\n\
    //! @note Time complexity: O(Max)\ntemplate <std::size_t Max, typename ReturnType>\n\
    [[nodiscard]] constexpr std::array<ReturnType, Max + 1> factorial_array() {\n\
    \  std::array<ReturnType, Max + 1> res;\n  res[0] = 1;\n\n  for (std::size_t i\
    \ = 1; i <= Max; ++i)\n    res[i] = res[i - 1] * i;\n\n  return res;\n}\n\n//!\
    \ @tparam Max upper limit\n//! @tparam Modint value type (deduced from parameter,\
    \ must be Modint)\n//! @param fact factorial of Max (which is the result of factorial\
    \ or factorial_array)\n//! @return std::array which contains multiplicative inverse\
    \ of 0!, 1!, ..., Max! (Max + 1 numbers)\n//! @note Time complexity: O(Max)\n\
    template <std::size_t Max, typename Modint>\n[[nodiscard]] constexpr std::array<Modint,\
    \ Max + 1> factorial_modinv_array(const Modint fact) {\n  std::array<Modint, Max\
    \ + 1> res;\n  res[Max] = fact.inv();\n\n  for (std::size_t i = Max; i > 0; --i)\n\
    \    res[i - 1] = res[i] * i;\n\n  return res;\n}\n\n//! @tparam Size Size of\
    \ factorial_array and factorial_modinv_array (deduced from parameters)\n//! @tparam\
    \ Tp deduced from parameters\n//! @tparam Modint deduced from parameters\n//!\
    \ @param n non-negative integer\n//! @param r non-negative integer\n//! @param\
    \ factorial_array Array that factorial_array() returns\n//! @param factorial_modinv_array\
    \ Array that factorial_modinv_array() returns\n//! @return nPr, or number of ways\
    \ to select r out of n distinguishable objects and arrange them in any order.\n\
    //! @note Time complexity: O(1)\ntemplate <std::size_t Size, typename Modint,\
    \ typename Tp>\n[[nodiscard]] Modint permutation(const Tp n, const Tp r, const\
    \ std::array<Modint, Size>& factorial_array, const std::array<Modint, Size>& factorial_modinv_array)\
    \ {\n  if (n == 0)\n    warn(\"n is zero.\");\n  if (n < 0) {\n    warn(\"n is\
    \ negative.\");\n    return 0;\n  }\n  if (r < 0) {\n    warn(\"r is negative.\"\
    );\n    return 0;\n  }\n  if (n < r) {\n    warn(\"n is less than r.\");\n   \
    \ return 0;\n  }\n  return factorial_array[n] * factorial_modinv_array[n - r];\n\
    }\n\n//! @tparam Size Size of factorial_array and factorial_modinv_array (deduced\
    \ from parameters)\n//! @tparam Tp deduced from parameters\n//! @tparam Modint\
    \ deduced from parameters\n//! @param n non-negative integer\n//! @param r non-negative\
    \ integer\n//! @param factorial_array Array that factorial_array() returns\n//!\
    \ @param factorial_modinv_array Array that factorial_modinv_array() returns\n\
    //! @return nCr, or number of ways to select r out of n distinguishable objects.\n\
    //! @note Time complexity: O(1)\ntemplate <std::size_t Size, typename Modint,\
    \ typename Tp>\n[[nodiscard]] constexpr Modint combination(const Tp n, const Tp\
    \ r, const std::array<Modint, Size>& factorial_array, const std::array<Modint,\
    \ Size>& factorial_modinv_array) {\n  if (n == 0)\n    warn(\"n is zero.\");\n\
    \  if (n < 0) {\n    warn(\"n is negative.\");\n    return 0;\n  }\n  if (r <\
    \ 0) {\n    warn(\"r is negative.\");\n    return 0;\n  }\n  if (n < r) {\n  \
    \  warn(\"n is less than r.\");\n    return 0;\n  }\n  return factorial_array[n]\
    \ * factorial_modinv_array[n - r] * factorial_modinv_array[r];\n}\n\n//! @tparam\
    \ Size Size of factorial_array and factorial_modinv_array (deduced from parameters)\n\
    //! @tparam Modint deduced from parameters\n//! @tparam Tp deduced from parameters\n\
    //! @tparam Ts deduced from parameters\n//! @param n non-negative integer\n//!\
    \ @param r non-negative integers whose sum is equal to n\n//! @param factorial_array\
    \ Array that factorial_array() returns\n//! @param factorial_modinv_array Array\
    \ that factorial_modinv_array() returns\n//! @return Number of ways to arrange\
    \ n objects when r_1, r_2, ... objects are indistinguishable.\n//! @note Time\
    \ complexity: O(sizeof...(r))\ntemplate <std::size_t Size, typename Modint, typename\
    \ Tp, typename... Ts>\n[[nodiscard]] constexpr Modint multinomial(const Tp n,\
    \ const Ts... r, const std::array<Modint, Size>& factorial_array, const std::array<Modint,\
    \ Size>& factorial_modinv_array) {\n  if (n == 0)\n    warn(\"n is zero.\");\n\
    \  if (n < 0) {\n    warn(\"n is negative.\");\n    return 0;\n  }\n  if (((r\
    \ < 0) || ...)) {\n    warn(\"r contains negative number.\");\n    return 0;\n\
    \  }\n  if ((r + ...) != n) {\n    warn(\"Sum of r... is not equal to n.\");\n\
    \    return 0;\n  }\n  return factorial_array[n] * ((factorial_modinv_array[r])\
    \ * ...);\n}\n\n//! @tparam Size Size of factorial_array and factorial_modinv_array\
    \ (deduced from parameters)\n//! @tparam Modint deduced from parameters\n//! @tparam\
    \ Tp deduced from parameters\n//! @tparam container type (deduced from parameters)\n\
    //! @param n non-negative integer\n//! @param r container of non-negative integers\
    \ whose sum is equal to n\n//! @param factorial_array Array that factorial_array()\
    \ returns\n//! @param factorial_modinv_array Array that factorial_modinv_array()\
    \ returns\n//! @return Number of ways to arrange n objects when r[0], r[1], ...\
    \ objects are indistinguishable.\n//! @note Time complexity: O(size(r))\ntemplate\
    \ <std::size_t Size, typename Modint, typename Tp, typename Container>\n[[nodiscard]]\
    \ constexpr Modint multinomial(const Tp n, const Container& r, const std::array<Modint,\
    \ Size>& factorial_array, const std::array<Modint, Size>& factorial_modinv_array)\
    \ {\n  using Elem = std::decay_t<decltype(*std::cbegin(r))>;\n  if (n == 0)\n\
    \    warn(\"n is zero.\");\n  if (n < 0) {\n    warn(\"n is negative.\");\n  \
    \  return 0;\n  }\n  if (std::any_of(std::cbegin(r), std::cend(r), [](const auto\
    \ v) { return v < 0; })) {\n    warn(\"r contains negative number.\");\n    return\
    \ 0;\n  }\n  if (std::reduce(std::cbegin(r), std::cend(r), Elem(0)) != n) {\n\
    \    warn(\"Sum of r is not equal to n.\");\n    return 0;\n  }\n  return factorial_array[n]\
    \ * std::reduce(std::cbegin(r), std::cend(r), Modint(1),\n                   \
    \                       [&](const Modint res, const Elem e) { return res * factorial_modinv_array[e];\
    \ });\n}\n\n//! @tparam Size Size of factorial_array and factorial_modinv_array\
    \ (deduced from parameters)\n//! @tparam Tp deduced from parameters\n//! @tparam\
    \ Modint deduced from parameters\n//! @param n non-negative integer\n//! @param\
    \ r non-negative integers whose sum is equal to n\n//! @param factorial_array\
    \ Array that factorial_array() returns\n//! @param factorial_modinv_array Array\
    \ that factorial_modinv_array() returns\n//! @return nHr, or number of ways to\
    \ put n indistinguishable balls into r distinguishable bins.\n//! @note Time complexity:\
    \ O(1)\ntemplate <std::size_t Size, typename Modint, typename Tp>\n[[nodiscard]]\
    \ constexpr Modint stars_and_bars(const Tp n, const Tp r, const std::array<Modint,\
    \ Size>& factorial_array, const std::array<Modint, Size>& factorial_modinv_array)\
    \ {\n  return combination(n + r - 1, r, factorial_array, factorial_modinv_array);\n\
    }\n\n}  // namespace lib\n\n#ifdef warn_not_defined\n#  undef warn\n#  undef warn_not_defined\n\
    // warn may be defined 2 times (by uncommenting line 19)\n#  ifdef warn\n#   \
    \ undef warn\n#  endif\n#endif\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: include/combinatorics/factorial.hpp
  requiredBy: []
  timestamp: '2021-08-08 15:13:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/combinatorics/factorial/1.test.cpp
  - test/combinatorics/factorial/2.test.cpp
documentation_of: include/combinatorics/factorial.hpp
layout: document
title: Factorial, Permutation, Combination, Multinomial coefficients
---

階乗・順列の数・二項係数・多項係数を計算する関数が定義されています。

---

### `factorial(n)`

$n$ の階乗 ($n!$) を返します。

### `permutation(n, r)`

$n$ 個の区別できるものの中から $r$ 個を選んで任意の順番で横一列に並べるとき、考えられる並べ方の数 $\left(= {}_nP_r \right)$ を返します。

### `combination(n, r)`

$n$ 個の区別できるものの中から $r$ 個を選ぶとき、考えられる選び方の数 $\left(= {}_nC_r \right)$ を返します。

### `multinomial(n, r...)`

$n$ 個のもののうち $r_1, \, r_2, \, \cdots, r_k$ 個のものがお互いに区別できないとき、それらを任意の順番で横一列に並べる方法の数 $\left(= \binom{n}{r_1, \, r_2, \, \cdots, r_k \ } \right)$ を返します。$\sum_{i = 1}^k r_i = n$ が成り立つ必要があります。

### `stars_and_bars(n, r)`

$n$ 個の区別できるものの中から重複を許して(同じものを複数回選んでもよいとして) $r$ 個を選ぶとき、考えられる選び方の数 $\left(= {}_{n + r - 1}C_r \right)$ を返します。

### `factorial_array<N, type>()`

$0$ から $N$ までの階乗が入った長さ $N + 1$ の `type` 型の配列 (`std::array`) を返します。

### `factorial_modinv_array<N, modint_type>(x)`

`modint_type` には [`static_modint`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) または [`dynamic_modint`](https://naskya.github.io/cp-library/include/algebra/dynamic_modint.hpp) が指定できます。$x$ として $N$ の階乗 ($N!$) を与えると、$0$ から $N$ までの階乗の `modint_type` 型における乗法の逆元が入った長さ $N + 1$ の `modint_type` 型の配列 (`std::array`) を返します。

---

[`static_modint`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) または [`dynamic_modint`](https://naskya.github.io/cp-library/include/algebra/dynamic_modint.hpp) を用いた組み合わせの計算では、`factorial_array` 関数と `factorial_modinv_array` 関数で行った前計算の結果を関数の引数の末尾に与えると定数時間で値を計算できるようになります。

```cpp
using mint = lib::static_modint<1000000007>;
constexpr int N = 500000;

// 階乗と階乗の逆元を前計算
const auto fact_array     = lib::factorial_array<N, mint>();
const auto fact_inv_array = lib::factorial_array<N, mint>(fact_array.back());

// 以下の計算は全て定数時間で行われる
const mint a = fact_array[n];  // factorial(n) は fact_array[n]
const mint b = permutation   (n, r,                       fact_array, fact_inv_array);
const mint c = combination   (n, r,                       fact_array, fact_inv_array);
const mint d = multinomial   (n, r_1, r_2, n - r_1 - r_2, fact_array, fact_inv_array);
const mint e = stars_and_bars(n, r,                       fact_array, fact_inv_array);
//                                                        ^^^^^^^^^^^^^^^^^^^^^^^^^^
```

---
