---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/algebra/pow/1.test.cpp
    title: test/algebra/pow/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/algebra/static_modint/1.test.cpp
    title: test/algebra/static_modint/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/algebra/static_modint/2.test.cpp
    title: test/algebra/static_modint/2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/algebra/static_modint/3.test.cpp
    title: test/algebra/static_modint/3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/combinatorics/factorial/1.test.cpp
    title: test/combinatorics/factorial/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/combinatorics/factorial/2.test.cpp
    title: test/combinatorics/factorial/2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/binary_indexed_tree/1.test.cpp
    title: test/data_structure/binary_indexed_tree/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/binary_indexed_tree/2.test.cpp
    title: test/data_structure/binary_indexed_tree/2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Print warning message
    links: []
  bundledCode: "#line 1 \"include/algebra/static_modint.hpp\"\n\n//! @file static_modint.hpp\n\
    \n#ifndef STATIC_MODINT_HPP\n#define STATIC_MODINT_HPP\n\n#include <cstdint>\n\
    #include <iostream>\n#include <limits>\n#include <type_traits>\n\n#ifndef warn\n\
    //! @brief Print warning message\n//! @note You can suppress the warning by uncommenting\
    \ line 17\n#  ifndef ONLINE_JUDGE\n#    define warn(msg) (std::cerr << (msg) <<\
    \ '\\n')\n// #  define warn(msg) (static_cast<void>(0))\n#  else\n#    define\
    \ warn(msg) (static_cast<void>(0))\n#  endif\n#  define warn_not_defined\n#endif\n\
    \nnamespace lib {\n\n//! @brief modint (for compile-time constant modulo)\n//!\
    \ @tparam modulo modulo (e.g. 1000000007).\ntemplate <std::int_least32_t modulo,\n\
    \          std::enable_if_t<(1 < modulo) && (modulo < std::numeric_limits<std::int_least32_t>::max()\
    \ / 2),\n                           std::nullptr_t> = nullptr>\nstruct static_modint\
    \ {\nprivate:\n  std::int_least32_t value;\n\n  //! @param n non-zero integer\n\
    \  //! @return multiplicative inverse of n\n  template <typename Tp>\n  [[nodiscard]]\
    \ static constexpr std::int_least32_t calc_inverse(Tp n) noexcept {\n    Tp b\
    \ = modulo, u = 1, v = 0, t;\n    while (b > 0) {\n      t = n / b;\n      //\
    \ std::swap is not necessarily constexpr in C++17\n      // std::swap(n -= t *\
    \ b, b);\n      Tp tmp = std::move(n -= t * b);\n      n      = std::move(b);\n\
    \      b      = std::move(tmp);\n      // std::swap(u -= t * v, v);\n      tmp\
    \ = std::move(u -= t * v);\n      u   = std::move(v);\n      v   = std::move(tmp);\n\
    \    }\n    if (u < 0)\n      u += modulo;\n    return static_cast<std::int_least32_t>(u);\n\
    \  }\n\n  //! @brief Calculate modulo and keep the value within [0, modulo)\n\
    \  //! @param v integer\n  //! @return integer within [0, modulo)\n  //! @note\
    \ Time complexity: O(1)\n  template <typename Tp>\n  [[nodiscard]] static constexpr\
    \ std::int_least32_t clamp_ll(Tp v) noexcept {\n#pragma GCC diagnostic push\n\
    #pragma GCC diagnostic ignored \"-Wsign-compare\"\n    if (modulo <= v || v <\
    \ -modulo)\n      v %= modulo;\n#pragma GCC diagnostic pop\n\n    if (v < 0)\n\
    \      v += modulo;\n    return static_cast<std::int_least32_t>(v);\n  }\n\n \
    \ //! @brief Calculate modulo and keep the value within [0, modulo)\n  //! @note\
    \ Time complexity: O(1)\n  constexpr void clamp_self() noexcept {\n    if (0 <=\
    \ value) {\n      if (value < modulo)\n        return;\n      if (value < modulo\
    \ * 2)\n        value -= modulo;\n      else\n        value -= modulo * 2;\n \
    \   } else {\n      if (-modulo < value)\n        value += modulo;\n      else\
    \ if (-modulo * 2 < value)\n        value += modulo * 2;\n      else {\n     \
    \   value += modulo;\n        value += modulo * 2;\n      }\n    }\n  }\n\npublic:\n\
    \  //! @brief underlying integer type\n  using type = std::int_least32_t;\n\n\
    \  //! @return modulo (e.g. 1000000007)\n  [[nodiscard]] static constexpr type\
    \ mod() noexcept {\n    return modulo;\n  }\n\n  //! @brief Create a modint of\
    \ value 0\n  constexpr static_modint() noexcept : value(0) {}\n\n  //! @brief\
    \ Create a modint without taking modulo\n  constexpr static_modint(const type\
    \ v, bool) noexcept : value(v) {}\n\n  //! @brief Create a modint\n  template\
    \ <typename ValueType>\n  constexpr static_modint(const ValueType v) noexcept\
    \ : value() {\n    if constexpr (std::is_integral_v<ValueType> && (std::numeric_limits<ValueType>::digits\
    \ <= 32)) {\n      value = v;\n      clamp_self();\n    } else {\n      value\
    \ = clamp_ll(v);\n    }\n  }\n\n  [[nodiscard]] constexpr static_modint operator+(const\
    \ static_modint rhs) const noexcept {\n    return static_modint(value + rhs.value);\n\
    \  }\n  [[nodiscard]] constexpr static_modint operator-(const static_modint rhs)\
    \ const noexcept {\n    return static_modint(value - rhs.value);\n  }\n  [[nodiscard]]\
    \ constexpr static_modint operator*(const static_modint rhs) const noexcept {\n\
    \    return static_modint(static_cast<std::int_least64_t>(value) * rhs.value);\n\
    \  }\n  [[nodiscard]] constexpr static_modint operator/(const static_modint rhs)\
    \ const {\n    return static_modint(static_cast<std::int_least64_t>(value) * calc_inverse(rhs.value));\n\
    \  }\n\n  [[nodiscard]] constexpr static_modint operator%(const static_modint\
    \ rhs) const {\n    warn(\"operator% : Are you sure you want to do this?\");\n\
    \    return static_modint(value % rhs.value);\n  }\n\n  [[nodiscard]] constexpr\
    \ static_modint operator&(const static_modint rhs) const {\n    warn(\"operator&\
    \ : Are you sure you want to do this?\");\n    return static_modint(value & rhs.value,\
    \ true);\n  }\n  [[nodiscard]] constexpr static_modint operator|(const static_modint\
    \ rhs) const {\n    warn(\"operator| : Are you sure you want to do this?\");\n\
    \    return static_modint(value | rhs.value);\n  }\n  [[nodiscard]] constexpr\
    \ static_modint operator^(const static_modint rhs) const {\n    warn(\"operator^\
    \ : Are you sure you want to do this?\");\n    return static_modint(value ^ rhs.value);\n\
    \  }\n  [[nodiscard]] constexpr static_modint operator<<(const static_modint rhs)\
    \ const {\n    warn(\"operator<< : Are you sure you want to do this?\");\n   \
    \ return static_modint(static_cast<std::int_least64_t>(value) << rhs.value);\n\
    \  }\n  [[nodiscard]] constexpr static_modint operator>>(const static_modint rhs)\
    \ const {\n    warn(\"operator>> : Are you sure you want to do this?\");\n   \
    \ return static_modint(value >> rhs.value, true);\n  }\n\n  constexpr static_modint&\
    \ operator+=(const static_modint rhs) noexcept {\n    value += rhs.value;\n  \
    \  if (value >= modulo)\n      value -= modulo;\n    return *this;\n  }\n  constexpr\
    \ static_modint& operator-=(const static_modint rhs) noexcept {\n    value -=\
    \ rhs.value;\n    if (value < 0)\n      value += modulo;\n    return *this;\n\
    \  }\n  constexpr static_modint& operator*=(const static_modint rhs) noexcept\
    \ {\n    value = clamp_ll(static_cast<std::int_least64_t>(value) * rhs.value);\n\
    \    return *this;\n  }\n  constexpr static_modint& operator/=(const static_modint\
    \ rhs) {\n    value = clamp_ll(static_cast<std::int_least64_t>(value) * calc_inverse(rhs.value));\n\
    \    return *this;\n  }\n\n  constexpr static_modint& operator%=(const static_modint\
    \ rhs) {\n    warn(\"operator%= : Are you sure you want to do this?\");\n    value\
    \ %= rhs.value;\n    if (value < 0)\n      value += modulo;\n    return *this;\n\
    \  }\n\n  constexpr static_modint& operator&=(const static_modint rhs) noexcept\
    \ {\n    warn(\"operator&= : Are you sure you want to do this?\");\n    value\
    \ &= rhs.value;\n    return *this;\n  }\n  constexpr static_modint& operator|=(const\
    \ static_modint rhs) noexcept {\n    warn(\"operator|= : Are you sure you want\
    \ to do this?\");\n    value |= rhs.value;\n    clamp_self();\n    return *this;\n\
    \  }\n  constexpr static_modint& operator^=(const static_modint rhs) noexcept\
    \ {\n    warn(\"operator^= : Are you sure you want to do this?\");\n    value\
    \ ^= rhs.value;\n    clamp_self();\n    return *this;\n  }\n  constexpr static_modint&\
    \ operator<<=(const static_modint rhs) noexcept {\n    warn(\"operator<<= : Are\
    \ you sure you want to do this?\");\n    value = clamp_ll(static_cast<std::int_least64_t>(value)\
    \ << rhs.value);\n    return *this;\n  }\n  constexpr static_modint& operator>>=(const\
    \ static_modint rhs) noexcept {\n    warn(\"operator>>= : Are you sure you want\
    \ to do this?\");\n    value >>= rhs.value;\n    return *this;\n  }\n\n  template\
    \ <typename RhsType>\n  [[nodiscard]] constexpr static_modint operator+(const\
    \ RhsType rhs) const noexcept {\n    return static_modint(value + clamp_ll(rhs));\n\
    \  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr static_modint operator-(const\
    \ RhsType rhs) const noexcept {\n    return static_modint(value - clamp_ll(rhs));\n\
    \  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr static_modint operator*(const\
    \ RhsType rhs) const noexcept {\n    return static_modint(static_cast<std::int_least64_t>(value)\
    \ * clamp_ll(rhs));\n  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr\
    \ static_modint operator/(const RhsType rhs) const {\n    std::int_least64_t mul\
    \ = (rhs > 0) ? calc_inverse(rhs) : -calc_inverse(-rhs);\n    return static_modint(value\
    \ * mul);\n  }\n\n  template <typename RhsType>\n  [[nodiscard]] constexpr static_modint\
    \ operator%(const RhsType rhs) const {\n    warn(\"operator% : Are you sure you\
    \ want to do this?\");\n    return static_modint(value % rhs, true);\n  }\n\n\
    \  template <typename RhsType>\n  [[nodiscard]] constexpr static_modint operator&(const\
    \ RhsType rhs) const {\n    warn(\"operator& : Are you sure you want to do this?\"\
    );\n    return static_modint(value & rhs, true);\n  }\n  template <typename RhsType>\n\
    \  [[nodiscard]] constexpr static_modint operator|(const RhsType rhs) const {\n\
    \    warn(\"operator| : Are you sure you want to do this?\");\n    return static_modint(value\
    \ | rhs);\n  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr static_modint\
    \ operator^(const RhsType rhs) const {\n    warn(\"operator^ : Are you sure you\
    \ want to do this?\");\n    return static_modint(value ^ rhs);\n  }\n  template\
    \ <typename RhsType>\n  [[nodiscard]] constexpr static_modint operator<<(const\
    \ RhsType rhs) const {\n    warn(\"operator<< : Are you sure you want to do this?\"\
    );\n    return static_modint(static_cast<std::int_least64_t>(value) << rhs);\n\
    \  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr static_modint operator>>(const\
    \ RhsType rhs) const {\n    warn(\"operator>> : Are you sure you want to do this?\"\
    );\n    return static_modint(value >> rhs, true);\n  }\n\n  template <typename\
    \ RhsType>\n  constexpr static_modint& operator+=(const RhsType rhs) noexcept\
    \ {\n    value = clamp_ll(static_cast<std::int_least64_t>(value) + rhs);\n   \
    \ return *this;\n  }\n  template <typename RhsType>\n  constexpr static_modint&\
    \ operator-=(const RhsType rhs) noexcept {\n    value = clamp_ll(static_cast<std::int_least64_t>(value)\
    \ - rhs);\n    return *this;\n  }\n  template <typename RhsType>\n  constexpr\
    \ static_modint& operator*=(const RhsType rhs) noexcept {\n    value = clamp_ll(static_cast<std::int_least64_t>(value)\
    \ * clamp_ll(rhs));\n    return *this;\n  }\n  template <typename RhsType>\n \
    \ constexpr static_modint& operator/=(const RhsType rhs) {\n    std::int_least64_t\
    \ mul = (rhs > 0) ? calc_inverse(rhs) : -calc_inverse(-rhs);\n    value      \
    \            = clamp_ll(value * mul);\n    return *this;\n  }\n\n  template <typename\
    \ RhsType>\n  constexpr static_modint& operator%=(const RhsType rhs) {\n    warn(\"\
    operator%= : Are you sure you want to do this?\");\n    value %= rhs;\n    return\
    \ *this;\n  }\n\n  template <typename RhsType>\n  constexpr static_modint& operator&=(const\
    \ RhsType rhs) noexcept {\n    warn(\"operator&= : Are you sure you want to do\
    \ this?\");\n    value &= rhs;\n    return *this;\n  }\n  template <typename RhsType>\n\
    \  constexpr static_modint& operator|=(const RhsType rhs) noexcept {\n    warn(\"\
    operator|= : Are you sure you want to do this?\");\n    value |= rhs;\n    clamp_self();\n\
    \    return *this;\n  }\n  template <typename RhsType>\n  constexpr static_modint&\
    \ operator^=(const RhsType rhs) noexcept {\n    warn(\"operator^= : Are you sure\
    \ you want to do this?\");\n    value ^= rhs;\n    clamp_self();\n    return *this;\n\
    \  }\n  template <typename RhsType>\n  constexpr static_modint& operator<<=(const\
    \ RhsType rhs) noexcept {\n    warn(\"operator<<= : Are you sure you want to do\
    \ this?\");\n    value = clamp_ll(static_cast<std::int_least64_t>(value) << rhs);\n\
    \    return *this;\n  }\n  template <typename RhsType>\n  constexpr static_modint&\
    \ operator>>=(const RhsType rhs) noexcept {\n    warn(\"operator>>= : Are you\
    \ sure you want to do this?\");\n    value >>= rhs;\n    return *this;\n  }\n\n\
    \  [[nodiscard]] constexpr bool operator!() const {\n    warn(\"operator! : Are\
    \ you sure you want to do this?\");\n    return value == 0;\n  }\n  [[nodiscard]]\
    \ constexpr static_modint operator~() const {\n    warn(\"operator~ : Are you\
    \ sure you want to do this?\");\n    return static_modint(~value);\n  }\n  [[nodiscard]]\
    \ constexpr static_modint operator-() const noexcept {\n    return static_modint(value\
    \ == 0 ? 0 : modulo - value, true);\n  }\n  [[nodiscard]] constexpr static_modint&\
    \ operator+() const noexcept {\n    return *this;\n  }\n\n  constexpr static_modint&\
    \ operator++() noexcept {\n    value = ((value + 1 == modulo) ? 0 : value + 1);\n\
    \    return *this;\n  }\n  constexpr static_modint& operator--() noexcept {\n\
    \    value = ((value == 0) ? modulo - 1 : value - 1);\n    return *this;\n  }\n\
    \  constexpr static_modint operator++(int) noexcept {\n    std::int_least32_t\
    \ res = value;\n    ++(*this);\n    return static_modint(res, true);\n  }\n  constexpr\
    \ static_modint operator--(int) noexcept {\n    std::int_least32_t res = value;\n\
    \    --(*this);\n    return static_modint(res, true);\n  }\n\n  [[nodiscard]]\
    \ constexpr bool operator==(const static_modint rhs) const noexcept {\n    return\
    \ value == rhs.value;\n  }\n  [[nodiscard]] constexpr bool operator!=(const static_modint\
    \ rhs) const noexcept {\n    return value != rhs.value;\n  }\n  [[nodiscard]]\
    \ constexpr bool operator<(const static_modint rhs) const {\n    warn(\"operator<\
    \ : Are you sure you want to do this?\");\n    return value < rhs.value;\n  }\n\
    \  [[nodiscard]] constexpr bool operator<=(const static_modint rhs) const {\n\
    \    warn(\"operator<= : Are you sure you want to do this?\");\n    return value\
    \ <= rhs.value;\n  }\n  [[nodiscard]] constexpr bool operator>(const static_modint\
    \ rhs) const {\n    warn(\"operator> : Are you sure you want to do this?\");\n\
    \    return value > rhs.value;\n  }\n  [[nodiscard]] constexpr bool operator>=(const\
    \ static_modint rhs) const {\n    warn(\"operator>= : Are you sure you want to\
    \ do this?\");\n    return value >= rhs.value;\n  }\n\n  template <typename RhsType>\n\
    \  [[nodiscard]] constexpr bool operator==(const RhsType rhs) const noexcept {\n\
    \    return value == rhs;\n  }\n  template <typename RhsType>\n  [[nodiscard]]\
    \ constexpr bool operator!=(const RhsType rhs) const noexcept {\n    return value\
    \ != rhs;\n  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr bool\
    \ operator<(const RhsType rhs) const {\n    warn(\"operator< : Are you sure you\
    \ want to do this?\");\n    return value < rhs;\n  }\n  template <typename RhsType>\n\
    \  [[nodiscard]] constexpr bool operator<=(const RhsType rhs) const {\n    warn(\"\
    operator<= : Are you sure you want to do this?\");\n    return value <= rhs;\n\
    \  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr bool operator>(const\
    \ RhsType rhs) const {\n    warn(\"operator> : Are you sure you want to do this?\"\
    );\n    return value > rhs;\n  }\n  template <typename RhsType>\n  [[nodiscard]]\
    \ constexpr bool operator>=(const RhsType rhs) const {\n    warn(\"operator>=\
    \ : Are you sure you want to do this?\");\n    return value >= rhs;\n  }\n\n \
    \ [[nodiscard]] constexpr operator std::int_least32_t() const noexcept {\n   \
    \ return value;\n  }\n\n  //! @brief Read value (64-bit signed integer) from std::istream&\
    \ is, take modulo, and store it in rhs.\n  //! @return std::istream& is\n  friend\
    \ std::istream& operator>>(std::istream& is, static_modint& rhs) {\n    std::int_least64_t\
    \ tmp;\n    is >> tmp;\n    if (tmp < -modulo || modulo <= tmp)\n      tmp %=\
    \ modulo;\n    if (tmp < 0)\n      tmp += modulo;\n    rhs.value = static_cast<std::int_least32_t>(tmp);\n\
    \    return is;\n  }\n  //! @brief Print value to std::ostream& os\n  //! @return\
    \ std::ostream& os\n  friend std::ostream& operator<<(std::ostream& os, static_modint&\
    \ rhs) {\n    return os << rhs.value;\n  }\n\n  //! @return multiplicative inverse\n\
    \  [[nodiscard]] constexpr static_modint inv() const {\n    return static_modint(calc_inverse(value),\
    \ true);\n  }\n  //! @tparam index_positive_guaranteed set true if and only if\
    \ you can promise that index is positive\n  //! @tparam Tp integer type (deduced\
    \ from parameter)\n  //! @param index index. This must be an integer, but doesn't\
    \ have to be primitive.\n  //! @return index-th power of the value\n  //! @note\
    \ Time complexity: O(log(index))\n  template <bool index_positive_guaranteed =\
    \ true, typename Tp = std::int_least32_t>\n  [[nodiscard]] constexpr static_modint\
    \ pow(Tp index) const noexcept {\n    if constexpr (!index_positive_guaranteed)\
    \ {\n      if (value == 0)\n        return static_modint(0, true);\n      if (index\
    \ == 0)\n        return static_modint(1, true);\n      if (index < 0)\n      \
    \  return static_modint(value, true).inv().pow<true>(-index);\n    }\n    static_modint\
    \ res(1, true), base(value, true);\n    while (index > 0) {\n      if ((index\
    \ & 1) == 1)\n        res *= base;\n      base *= base;\n      index >>= 1;\n\
    \    }\n    return res;\n  }\n  //! @return a pair (a, b) such that b > 0, value\
    \ is equal to a * (mult inverse of b), and (a + b) is minimal\n  [[nodiscard]]\
    \ constexpr std::pair<std::int_least32_t, std::int_least32_t> to_frac() const\
    \ noexcept {\n    std::int_least32_t x = modulo - value, y = value, u = 1, v =\
    \ 1;\n    std::pair<std::int_least32_t, std::int_least32_t> res {value, 1};\n\n\
    \    std::int_least32_t num = value, den = 1;\n    std::int_least32_t cost = num\
    \ + den;\n\n    while (x > 0) {\n      if (x <= num) {\n        std::int_least32_t\
    \ q = num / x;\n        num                  = num % x;\n        den += q * u;\n\
    \        if (num == 0)\n          break;\n        if (num + den < cost) {\n  \
    \        cost       = num + den;\n          res.first  = num;\n          res.second\
    \ = den;\n        }\n      }\n      std::int_least32_t q = y / x;\n      y   \
    \                 = y % x;\n      v += q * u;\n      q = x / y;\n      x = x %\
    \ y;\n      u += q * v;\n    }\n\n    return res;\n  }\n};\n\ntemplate <typename\
    \ LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr static_modint<modulo>\
    \ operator+(const LhsType lhs, const static_modint<modulo> rhs) noexcept {\n \
    \ return rhs + lhs;\n}\ntemplate <typename LhsType, std::int_least32_t modulo>\n\
    [[nodiscard]] constexpr static_modint<modulo> operator-(const LhsType lhs, const\
    \ static_modint<modulo> rhs) noexcept {\n  return -rhs + lhs;\n}\ntemplate <typename\
    \ LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr static_modint<modulo>\
    \ operator*(const LhsType lhs, const static_modint<modulo> rhs) noexcept {\n \
    \ return rhs * lhs;\n}\ntemplate <typename LhsType, std::int_least32_t modulo>\n\
    [[nodiscard]] constexpr static_modint<modulo> operator/(const LhsType lhs, const\
    \ static_modint<modulo> rhs) {\n  return rhs.inv() * lhs;\n}\n\ntemplate <typename\
    \ LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr static_modint<modulo>\
    \ operator%(const LhsType lhs, const static_modint<modulo> rhs) {\n  warn(\"operator%\
    \ : Are you sure you want to do this?\");\n  return static_modint<modulo>(lhs\
    \ % static_cast<std::int_least32_t>(rhs), true);\n}\n\ntemplate <typename LhsType,\
    \ std::int_least32_t modulo, std::enable_if_t<std::is_integral_v<LhsType>, std::nullptr_t>\
    \ = nullptr>\n[[nodiscard]] constexpr static_modint<modulo> operator<<(const LhsType\
    \ lhs, const static_modint<modulo> rhs) {\n  warn(\"operator<< : Are you sure\
    \ you want to do this?\");\n  return static_modint<modulo>(static_cast<std::int_least64_t>(lhs)\
    \ << static_cast<std::int_least32_t>(rhs));\n}\ntemplate <typename LhsType, std::int_least32_t\
    \ modulo, std::enable_if_t<std::is_integral_v<LhsType>, std::nullptr_t> = nullptr>\n\
    [[nodiscard]] constexpr static_modint<modulo> operator>>(const LhsType lhs, const\
    \ static_modint<modulo> rhs) {\n  warn(\"operator>> : Are you sure you want to\
    \ do this?\");\n  return static_modint<modulo>(lhs >> static_cast<std::int_least32_t>(rhs));\n\
    }\n\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator+=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  return\
    \ lhs += static_cast<std::int_least32_t>(rhs);\n}\ntemplate <typename LhsType,\
    \ std::int_least32_t modulo>\nconstexpr LhsType& operator-=(LhsType& lhs, const\
    \ static_modint<modulo> rhs) noexcept {\n  return lhs -= static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator*=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  return\
    \ lhs *= static_cast<std::int_least32_t>(rhs);\n}\ntemplate <typename LhsType,\
    \ std::int_least32_t modulo>\nconstexpr LhsType& operator/=(LhsType& lhs, const\
    \ static_modint<modulo> rhs) noexcept {\n  return lhs /= static_cast<std::int_least32_t>(rhs);\n\
    }\n\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator%=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  warn(\"\
    operator%= : Are you sure you want to do this?\");\n  return lhs %= static_cast<std::int_least32_t>(rhs);\n\
    }\n\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator&=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  warn(\"\
    operator&= : Are you sure you want to do this?\");\n  return lhs &= static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator|=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  warn(\"\
    operator|= : Are you sure you want to do this?\");\n  return lhs |= static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator^=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  warn(\"\
    operator^= : Are you sure you want to do this?\");\n  return lhs ^= static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator<<=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  warn(\"\
    operator<<= : Are you sure you want to do this?\");\n  return lhs <<= static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator>>=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  warn(\"\
    operator>>= : Are you sure you want to do this?\");\n  return lhs >>= static_cast<std::int_least32_t>(rhs);\n\
    }\n\ntemplate <typename LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr\
    \ bool operator<(const LhsType lhs, const static_modint<modulo> rhs) {\n  warn(\"\
    operator< : Are you sure you want to do this?\");\n  return lhs < static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr\
    \ bool operator<=(const LhsType lhs, const static_modint<modulo> rhs) {\n  warn(\"\
    operator<= : Are you sure you want to do this?\");\n  return lhs < static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr\
    \ bool operator>(const LhsType lhs, const static_modint<modulo> rhs) {\n  warn(\"\
    operator> : Are you sure you want to do this?\");\n  return lhs < static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr\
    \ bool operator>=(const LhsType lhs, const static_modint<modulo> rhs) {\n  warn(\"\
    operator>= : Are you sure you want to do this?\");\n  return lhs < static_cast<std::int_least32_t>(rhs);\n\
    }\n\n}  // namespace lib\n\n#ifdef warn_not_defined\n#  undef warn\n#  undef warn_not_defined\n\
    // warn may be defined 2 times (by uncommenting line 17)\n#  ifdef warn\n#   \
    \ undef warn\n#  endif\n#endif\n\n#endif  // STATIC_MODINT_HPP\n"
  code: "\n//! @file static_modint.hpp\n\n#ifndef STATIC_MODINT_HPP\n#define STATIC_MODINT_HPP\n\
    \n#include <cstdint>\n#include <iostream>\n#include <limits>\n#include <type_traits>\n\
    \n#ifndef warn\n//! @brief Print warning message\n//! @note You can suppress the\
    \ warning by uncommenting line 17\n#  ifndef ONLINE_JUDGE\n#    define warn(msg)\
    \ (std::cerr << (msg) << '\\n')\n// #  define warn(msg) (static_cast<void>(0))\n\
    #  else\n#    define warn(msg) (static_cast<void>(0))\n#  endif\n#  define warn_not_defined\n\
    #endif\n\nnamespace lib {\n\n//! @brief modint (for compile-time constant modulo)\n\
    //! @tparam modulo modulo (e.g. 1000000007).\ntemplate <std::int_least32_t modulo,\n\
    \          std::enable_if_t<(1 < modulo) && (modulo < std::numeric_limits<std::int_least32_t>::max()\
    \ / 2),\n                           std::nullptr_t> = nullptr>\nstruct static_modint\
    \ {\nprivate:\n  std::int_least32_t value;\n\n  //! @param n non-zero integer\n\
    \  //! @return multiplicative inverse of n\n  template <typename Tp>\n  [[nodiscard]]\
    \ static constexpr std::int_least32_t calc_inverse(Tp n) noexcept {\n    Tp b\
    \ = modulo, u = 1, v = 0, t;\n    while (b > 0) {\n      t = n / b;\n      //\
    \ std::swap is not necessarily constexpr in C++17\n      // std::swap(n -= t *\
    \ b, b);\n      Tp tmp = std::move(n -= t * b);\n      n      = std::move(b);\n\
    \      b      = std::move(tmp);\n      // std::swap(u -= t * v, v);\n      tmp\
    \ = std::move(u -= t * v);\n      u   = std::move(v);\n      v   = std::move(tmp);\n\
    \    }\n    if (u < 0)\n      u += modulo;\n    return static_cast<std::int_least32_t>(u);\n\
    \  }\n\n  //! @brief Calculate modulo and keep the value within [0, modulo)\n\
    \  //! @param v integer\n  //! @return integer within [0, modulo)\n  //! @note\
    \ Time complexity: O(1)\n  template <typename Tp>\n  [[nodiscard]] static constexpr\
    \ std::int_least32_t clamp_ll(Tp v) noexcept {\n#pragma GCC diagnostic push\n\
    #pragma GCC diagnostic ignored \"-Wsign-compare\"\n    if (modulo <= v || v <\
    \ -modulo)\n      v %= modulo;\n#pragma GCC diagnostic pop\n\n    if (v < 0)\n\
    \      v += modulo;\n    return static_cast<std::int_least32_t>(v);\n  }\n\n \
    \ //! @brief Calculate modulo and keep the value within [0, modulo)\n  //! @note\
    \ Time complexity: O(1)\n  constexpr void clamp_self() noexcept {\n    if (0 <=\
    \ value) {\n      if (value < modulo)\n        return;\n      if (value < modulo\
    \ * 2)\n        value -= modulo;\n      else\n        value -= modulo * 2;\n \
    \   } else {\n      if (-modulo < value)\n        value += modulo;\n      else\
    \ if (-modulo * 2 < value)\n        value += modulo * 2;\n      else {\n     \
    \   value += modulo;\n        value += modulo * 2;\n      }\n    }\n  }\n\npublic:\n\
    \  //! @brief underlying integer type\n  using type = std::int_least32_t;\n\n\
    \  //! @return modulo (e.g. 1000000007)\n  [[nodiscard]] static constexpr type\
    \ mod() noexcept {\n    return modulo;\n  }\n\n  //! @brief Create a modint of\
    \ value 0\n  constexpr static_modint() noexcept : value(0) {}\n\n  //! @brief\
    \ Create a modint without taking modulo\n  constexpr static_modint(const type\
    \ v, bool) noexcept : value(v) {}\n\n  //! @brief Create a modint\n  template\
    \ <typename ValueType>\n  constexpr static_modint(const ValueType v) noexcept\
    \ : value() {\n    if constexpr (std::is_integral_v<ValueType> && (std::numeric_limits<ValueType>::digits\
    \ <= 32)) {\n      value = v;\n      clamp_self();\n    } else {\n      value\
    \ = clamp_ll(v);\n    }\n  }\n\n  [[nodiscard]] constexpr static_modint operator+(const\
    \ static_modint rhs) const noexcept {\n    return static_modint(value + rhs.value);\n\
    \  }\n  [[nodiscard]] constexpr static_modint operator-(const static_modint rhs)\
    \ const noexcept {\n    return static_modint(value - rhs.value);\n  }\n  [[nodiscard]]\
    \ constexpr static_modint operator*(const static_modint rhs) const noexcept {\n\
    \    return static_modint(static_cast<std::int_least64_t>(value) * rhs.value);\n\
    \  }\n  [[nodiscard]] constexpr static_modint operator/(const static_modint rhs)\
    \ const {\n    return static_modint(static_cast<std::int_least64_t>(value) * calc_inverse(rhs.value));\n\
    \  }\n\n  [[nodiscard]] constexpr static_modint operator%(const static_modint\
    \ rhs) const {\n    warn(\"operator% : Are you sure you want to do this?\");\n\
    \    return static_modint(value % rhs.value);\n  }\n\n  [[nodiscard]] constexpr\
    \ static_modint operator&(const static_modint rhs) const {\n    warn(\"operator&\
    \ : Are you sure you want to do this?\");\n    return static_modint(value & rhs.value,\
    \ true);\n  }\n  [[nodiscard]] constexpr static_modint operator|(const static_modint\
    \ rhs) const {\n    warn(\"operator| : Are you sure you want to do this?\");\n\
    \    return static_modint(value | rhs.value);\n  }\n  [[nodiscard]] constexpr\
    \ static_modint operator^(const static_modint rhs) const {\n    warn(\"operator^\
    \ : Are you sure you want to do this?\");\n    return static_modint(value ^ rhs.value);\n\
    \  }\n  [[nodiscard]] constexpr static_modint operator<<(const static_modint rhs)\
    \ const {\n    warn(\"operator<< : Are you sure you want to do this?\");\n   \
    \ return static_modint(static_cast<std::int_least64_t>(value) << rhs.value);\n\
    \  }\n  [[nodiscard]] constexpr static_modint operator>>(const static_modint rhs)\
    \ const {\n    warn(\"operator>> : Are you sure you want to do this?\");\n   \
    \ return static_modint(value >> rhs.value, true);\n  }\n\n  constexpr static_modint&\
    \ operator+=(const static_modint rhs) noexcept {\n    value += rhs.value;\n  \
    \  if (value >= modulo)\n      value -= modulo;\n    return *this;\n  }\n  constexpr\
    \ static_modint& operator-=(const static_modint rhs) noexcept {\n    value -=\
    \ rhs.value;\n    if (value < 0)\n      value += modulo;\n    return *this;\n\
    \  }\n  constexpr static_modint& operator*=(const static_modint rhs) noexcept\
    \ {\n    value = clamp_ll(static_cast<std::int_least64_t>(value) * rhs.value);\n\
    \    return *this;\n  }\n  constexpr static_modint& operator/=(const static_modint\
    \ rhs) {\n    value = clamp_ll(static_cast<std::int_least64_t>(value) * calc_inverse(rhs.value));\n\
    \    return *this;\n  }\n\n  constexpr static_modint& operator%=(const static_modint\
    \ rhs) {\n    warn(\"operator%= : Are you sure you want to do this?\");\n    value\
    \ %= rhs.value;\n    if (value < 0)\n      value += modulo;\n    return *this;\n\
    \  }\n\n  constexpr static_modint& operator&=(const static_modint rhs) noexcept\
    \ {\n    warn(\"operator&= : Are you sure you want to do this?\");\n    value\
    \ &= rhs.value;\n    return *this;\n  }\n  constexpr static_modint& operator|=(const\
    \ static_modint rhs) noexcept {\n    warn(\"operator|= : Are you sure you want\
    \ to do this?\");\n    value |= rhs.value;\n    clamp_self();\n    return *this;\n\
    \  }\n  constexpr static_modint& operator^=(const static_modint rhs) noexcept\
    \ {\n    warn(\"operator^= : Are you sure you want to do this?\");\n    value\
    \ ^= rhs.value;\n    clamp_self();\n    return *this;\n  }\n  constexpr static_modint&\
    \ operator<<=(const static_modint rhs) noexcept {\n    warn(\"operator<<= : Are\
    \ you sure you want to do this?\");\n    value = clamp_ll(static_cast<std::int_least64_t>(value)\
    \ << rhs.value);\n    return *this;\n  }\n  constexpr static_modint& operator>>=(const\
    \ static_modint rhs) noexcept {\n    warn(\"operator>>= : Are you sure you want\
    \ to do this?\");\n    value >>= rhs.value;\n    return *this;\n  }\n\n  template\
    \ <typename RhsType>\n  [[nodiscard]] constexpr static_modint operator+(const\
    \ RhsType rhs) const noexcept {\n    return static_modint(value + clamp_ll(rhs));\n\
    \  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr static_modint operator-(const\
    \ RhsType rhs) const noexcept {\n    return static_modint(value - clamp_ll(rhs));\n\
    \  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr static_modint operator*(const\
    \ RhsType rhs) const noexcept {\n    return static_modint(static_cast<std::int_least64_t>(value)\
    \ * clamp_ll(rhs));\n  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr\
    \ static_modint operator/(const RhsType rhs) const {\n    std::int_least64_t mul\
    \ = (rhs > 0) ? calc_inverse(rhs) : -calc_inverse(-rhs);\n    return static_modint(value\
    \ * mul);\n  }\n\n  template <typename RhsType>\n  [[nodiscard]] constexpr static_modint\
    \ operator%(const RhsType rhs) const {\n    warn(\"operator% : Are you sure you\
    \ want to do this?\");\n    return static_modint(value % rhs, true);\n  }\n\n\
    \  template <typename RhsType>\n  [[nodiscard]] constexpr static_modint operator&(const\
    \ RhsType rhs) const {\n    warn(\"operator& : Are you sure you want to do this?\"\
    );\n    return static_modint(value & rhs, true);\n  }\n  template <typename RhsType>\n\
    \  [[nodiscard]] constexpr static_modint operator|(const RhsType rhs) const {\n\
    \    warn(\"operator| : Are you sure you want to do this?\");\n    return static_modint(value\
    \ | rhs);\n  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr static_modint\
    \ operator^(const RhsType rhs) const {\n    warn(\"operator^ : Are you sure you\
    \ want to do this?\");\n    return static_modint(value ^ rhs);\n  }\n  template\
    \ <typename RhsType>\n  [[nodiscard]] constexpr static_modint operator<<(const\
    \ RhsType rhs) const {\n    warn(\"operator<< : Are you sure you want to do this?\"\
    );\n    return static_modint(static_cast<std::int_least64_t>(value) << rhs);\n\
    \  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr static_modint operator>>(const\
    \ RhsType rhs) const {\n    warn(\"operator>> : Are you sure you want to do this?\"\
    );\n    return static_modint(value >> rhs, true);\n  }\n\n  template <typename\
    \ RhsType>\n  constexpr static_modint& operator+=(const RhsType rhs) noexcept\
    \ {\n    value = clamp_ll(static_cast<std::int_least64_t>(value) + rhs);\n   \
    \ return *this;\n  }\n  template <typename RhsType>\n  constexpr static_modint&\
    \ operator-=(const RhsType rhs) noexcept {\n    value = clamp_ll(static_cast<std::int_least64_t>(value)\
    \ - rhs);\n    return *this;\n  }\n  template <typename RhsType>\n  constexpr\
    \ static_modint& operator*=(const RhsType rhs) noexcept {\n    value = clamp_ll(static_cast<std::int_least64_t>(value)\
    \ * clamp_ll(rhs));\n    return *this;\n  }\n  template <typename RhsType>\n \
    \ constexpr static_modint& operator/=(const RhsType rhs) {\n    std::int_least64_t\
    \ mul = (rhs > 0) ? calc_inverse(rhs) : -calc_inverse(-rhs);\n    value      \
    \            = clamp_ll(value * mul);\n    return *this;\n  }\n\n  template <typename\
    \ RhsType>\n  constexpr static_modint& operator%=(const RhsType rhs) {\n    warn(\"\
    operator%= : Are you sure you want to do this?\");\n    value %= rhs;\n    return\
    \ *this;\n  }\n\n  template <typename RhsType>\n  constexpr static_modint& operator&=(const\
    \ RhsType rhs) noexcept {\n    warn(\"operator&= : Are you sure you want to do\
    \ this?\");\n    value &= rhs;\n    return *this;\n  }\n  template <typename RhsType>\n\
    \  constexpr static_modint& operator|=(const RhsType rhs) noexcept {\n    warn(\"\
    operator|= : Are you sure you want to do this?\");\n    value |= rhs;\n    clamp_self();\n\
    \    return *this;\n  }\n  template <typename RhsType>\n  constexpr static_modint&\
    \ operator^=(const RhsType rhs) noexcept {\n    warn(\"operator^= : Are you sure\
    \ you want to do this?\");\n    value ^= rhs;\n    clamp_self();\n    return *this;\n\
    \  }\n  template <typename RhsType>\n  constexpr static_modint& operator<<=(const\
    \ RhsType rhs) noexcept {\n    warn(\"operator<<= : Are you sure you want to do\
    \ this?\");\n    value = clamp_ll(static_cast<std::int_least64_t>(value) << rhs);\n\
    \    return *this;\n  }\n  template <typename RhsType>\n  constexpr static_modint&\
    \ operator>>=(const RhsType rhs) noexcept {\n    warn(\"operator>>= : Are you\
    \ sure you want to do this?\");\n    value >>= rhs;\n    return *this;\n  }\n\n\
    \  [[nodiscard]] constexpr bool operator!() const {\n    warn(\"operator! : Are\
    \ you sure you want to do this?\");\n    return value == 0;\n  }\n  [[nodiscard]]\
    \ constexpr static_modint operator~() const {\n    warn(\"operator~ : Are you\
    \ sure you want to do this?\");\n    return static_modint(~value);\n  }\n  [[nodiscard]]\
    \ constexpr static_modint operator-() const noexcept {\n    return static_modint(value\
    \ == 0 ? 0 : modulo - value, true);\n  }\n  [[nodiscard]] constexpr static_modint&\
    \ operator+() const noexcept {\n    return *this;\n  }\n\n  constexpr static_modint&\
    \ operator++() noexcept {\n    value = ((value + 1 == modulo) ? 0 : value + 1);\n\
    \    return *this;\n  }\n  constexpr static_modint& operator--() noexcept {\n\
    \    value = ((value == 0) ? modulo - 1 : value - 1);\n    return *this;\n  }\n\
    \  constexpr static_modint operator++(int) noexcept {\n    std::int_least32_t\
    \ res = value;\n    ++(*this);\n    return static_modint(res, true);\n  }\n  constexpr\
    \ static_modint operator--(int) noexcept {\n    std::int_least32_t res = value;\n\
    \    --(*this);\n    return static_modint(res, true);\n  }\n\n  [[nodiscard]]\
    \ constexpr bool operator==(const static_modint rhs) const noexcept {\n    return\
    \ value == rhs.value;\n  }\n  [[nodiscard]] constexpr bool operator!=(const static_modint\
    \ rhs) const noexcept {\n    return value != rhs.value;\n  }\n  [[nodiscard]]\
    \ constexpr bool operator<(const static_modint rhs) const {\n    warn(\"operator<\
    \ : Are you sure you want to do this?\");\n    return value < rhs.value;\n  }\n\
    \  [[nodiscard]] constexpr bool operator<=(const static_modint rhs) const {\n\
    \    warn(\"operator<= : Are you sure you want to do this?\");\n    return value\
    \ <= rhs.value;\n  }\n  [[nodiscard]] constexpr bool operator>(const static_modint\
    \ rhs) const {\n    warn(\"operator> : Are you sure you want to do this?\");\n\
    \    return value > rhs.value;\n  }\n  [[nodiscard]] constexpr bool operator>=(const\
    \ static_modint rhs) const {\n    warn(\"operator>= : Are you sure you want to\
    \ do this?\");\n    return value >= rhs.value;\n  }\n\n  template <typename RhsType>\n\
    \  [[nodiscard]] constexpr bool operator==(const RhsType rhs) const noexcept {\n\
    \    return value == rhs;\n  }\n  template <typename RhsType>\n  [[nodiscard]]\
    \ constexpr bool operator!=(const RhsType rhs) const noexcept {\n    return value\
    \ != rhs;\n  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr bool\
    \ operator<(const RhsType rhs) const {\n    warn(\"operator< : Are you sure you\
    \ want to do this?\");\n    return value < rhs;\n  }\n  template <typename RhsType>\n\
    \  [[nodiscard]] constexpr bool operator<=(const RhsType rhs) const {\n    warn(\"\
    operator<= : Are you sure you want to do this?\");\n    return value <= rhs;\n\
    \  }\n  template <typename RhsType>\n  [[nodiscard]] constexpr bool operator>(const\
    \ RhsType rhs) const {\n    warn(\"operator> : Are you sure you want to do this?\"\
    );\n    return value > rhs;\n  }\n  template <typename RhsType>\n  [[nodiscard]]\
    \ constexpr bool operator>=(const RhsType rhs) const {\n    warn(\"operator>=\
    \ : Are you sure you want to do this?\");\n    return value >= rhs;\n  }\n\n \
    \ [[nodiscard]] constexpr operator std::int_least32_t() const noexcept {\n   \
    \ return value;\n  }\n\n  //! @brief Read value (64-bit signed integer) from std::istream&\
    \ is, take modulo, and store it in rhs.\n  //! @return std::istream& is\n  friend\
    \ std::istream& operator>>(std::istream& is, static_modint& rhs) {\n    std::int_least64_t\
    \ tmp;\n    is >> tmp;\n    if (tmp < -modulo || modulo <= tmp)\n      tmp %=\
    \ modulo;\n    if (tmp < 0)\n      tmp += modulo;\n    rhs.value = static_cast<std::int_least32_t>(tmp);\n\
    \    return is;\n  }\n  //! @brief Print value to std::ostream& os\n  //! @return\
    \ std::ostream& os\n  friend std::ostream& operator<<(std::ostream& os, static_modint&\
    \ rhs) {\n    return os << rhs.value;\n  }\n\n  //! @return multiplicative inverse\n\
    \  [[nodiscard]] constexpr static_modint inv() const {\n    return static_modint(calc_inverse(value),\
    \ true);\n  }\n  //! @tparam index_positive_guaranteed set true if and only if\
    \ you can promise that index is positive\n  //! @tparam Tp integer type (deduced\
    \ from parameter)\n  //! @param index index. This must be an integer, but doesn't\
    \ have to be primitive.\n  //! @return index-th power of the value\n  //! @note\
    \ Time complexity: O(log(index))\n  template <bool index_positive_guaranteed =\
    \ true, typename Tp = std::int_least32_t>\n  [[nodiscard]] constexpr static_modint\
    \ pow(Tp index) const noexcept {\n    if constexpr (!index_positive_guaranteed)\
    \ {\n      if (value == 0)\n        return static_modint(0, true);\n      if (index\
    \ == 0)\n        return static_modint(1, true);\n      if (index < 0)\n      \
    \  return static_modint(value, true).inv().pow<true>(-index);\n    }\n    static_modint\
    \ res(1, true), base(value, true);\n    while (index > 0) {\n      if ((index\
    \ & 1) == 1)\n        res *= base;\n      base *= base;\n      index >>= 1;\n\
    \    }\n    return res;\n  }\n  //! @return a pair (a, b) such that b > 0, value\
    \ is equal to a * (mult inverse of b), and (a + b) is minimal\n  [[nodiscard]]\
    \ constexpr std::pair<std::int_least32_t, std::int_least32_t> to_frac() const\
    \ noexcept {\n    std::int_least32_t x = modulo - value, y = value, u = 1, v =\
    \ 1;\n    std::pair<std::int_least32_t, std::int_least32_t> res {value, 1};\n\n\
    \    std::int_least32_t num = value, den = 1;\n    std::int_least32_t cost = num\
    \ + den;\n\n    while (x > 0) {\n      if (x <= num) {\n        std::int_least32_t\
    \ q = num / x;\n        num                  = num % x;\n        den += q * u;\n\
    \        if (num == 0)\n          break;\n        if (num + den < cost) {\n  \
    \        cost       = num + den;\n          res.first  = num;\n          res.second\
    \ = den;\n        }\n      }\n      std::int_least32_t q = y / x;\n      y   \
    \                 = y % x;\n      v += q * u;\n      q = x / y;\n      x = x %\
    \ y;\n      u += q * v;\n    }\n\n    return res;\n  }\n};\n\ntemplate <typename\
    \ LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr static_modint<modulo>\
    \ operator+(const LhsType lhs, const static_modint<modulo> rhs) noexcept {\n \
    \ return rhs + lhs;\n}\ntemplate <typename LhsType, std::int_least32_t modulo>\n\
    [[nodiscard]] constexpr static_modint<modulo> operator-(const LhsType lhs, const\
    \ static_modint<modulo> rhs) noexcept {\n  return -rhs + lhs;\n}\ntemplate <typename\
    \ LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr static_modint<modulo>\
    \ operator*(const LhsType lhs, const static_modint<modulo> rhs) noexcept {\n \
    \ return rhs * lhs;\n}\ntemplate <typename LhsType, std::int_least32_t modulo>\n\
    [[nodiscard]] constexpr static_modint<modulo> operator/(const LhsType lhs, const\
    \ static_modint<modulo> rhs) {\n  return rhs.inv() * lhs;\n}\n\ntemplate <typename\
    \ LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr static_modint<modulo>\
    \ operator%(const LhsType lhs, const static_modint<modulo> rhs) {\n  warn(\"operator%\
    \ : Are you sure you want to do this?\");\n  return static_modint<modulo>(lhs\
    \ % static_cast<std::int_least32_t>(rhs), true);\n}\n\ntemplate <typename LhsType,\
    \ std::int_least32_t modulo, std::enable_if_t<std::is_integral_v<LhsType>, std::nullptr_t>\
    \ = nullptr>\n[[nodiscard]] constexpr static_modint<modulo> operator<<(const LhsType\
    \ lhs, const static_modint<modulo> rhs) {\n  warn(\"operator<< : Are you sure\
    \ you want to do this?\");\n  return static_modint<modulo>(static_cast<std::int_least64_t>(lhs)\
    \ << static_cast<std::int_least32_t>(rhs));\n}\ntemplate <typename LhsType, std::int_least32_t\
    \ modulo, std::enable_if_t<std::is_integral_v<LhsType>, std::nullptr_t> = nullptr>\n\
    [[nodiscard]] constexpr static_modint<modulo> operator>>(const LhsType lhs, const\
    \ static_modint<modulo> rhs) {\n  warn(\"operator>> : Are you sure you want to\
    \ do this?\");\n  return static_modint<modulo>(lhs >> static_cast<std::int_least32_t>(rhs));\n\
    }\n\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator+=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  return\
    \ lhs += static_cast<std::int_least32_t>(rhs);\n}\ntemplate <typename LhsType,\
    \ std::int_least32_t modulo>\nconstexpr LhsType& operator-=(LhsType& lhs, const\
    \ static_modint<modulo> rhs) noexcept {\n  return lhs -= static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator*=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  return\
    \ lhs *= static_cast<std::int_least32_t>(rhs);\n}\ntemplate <typename LhsType,\
    \ std::int_least32_t modulo>\nconstexpr LhsType& operator/=(LhsType& lhs, const\
    \ static_modint<modulo> rhs) noexcept {\n  return lhs /= static_cast<std::int_least32_t>(rhs);\n\
    }\n\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator%=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  warn(\"\
    operator%= : Are you sure you want to do this?\");\n  return lhs %= static_cast<std::int_least32_t>(rhs);\n\
    }\n\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator&=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  warn(\"\
    operator&= : Are you sure you want to do this?\");\n  return lhs &= static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator|=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  warn(\"\
    operator|= : Are you sure you want to do this?\");\n  return lhs |= static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator^=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  warn(\"\
    operator^= : Are you sure you want to do this?\");\n  return lhs ^= static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator<<=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  warn(\"\
    operator<<= : Are you sure you want to do this?\");\n  return lhs <<= static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\nconstexpr LhsType&\
    \ operator>>=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {\n  warn(\"\
    operator>>= : Are you sure you want to do this?\");\n  return lhs >>= static_cast<std::int_least32_t>(rhs);\n\
    }\n\ntemplate <typename LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr\
    \ bool operator<(const LhsType lhs, const static_modint<modulo> rhs) {\n  warn(\"\
    operator< : Are you sure you want to do this?\");\n  return lhs < static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr\
    \ bool operator<=(const LhsType lhs, const static_modint<modulo> rhs) {\n  warn(\"\
    operator<= : Are you sure you want to do this?\");\n  return lhs < static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr\
    \ bool operator>(const LhsType lhs, const static_modint<modulo> rhs) {\n  warn(\"\
    operator> : Are you sure you want to do this?\");\n  return lhs < static_cast<std::int_least32_t>(rhs);\n\
    }\ntemplate <typename LhsType, std::int_least32_t modulo>\n[[nodiscard]] constexpr\
    \ bool operator>=(const LhsType lhs, const static_modint<modulo> rhs) {\n  warn(\"\
    operator>= : Are you sure you want to do this?\");\n  return lhs < static_cast<std::int_least32_t>(rhs);\n\
    }\n\n}  // namespace lib\n\n#ifdef warn_not_defined\n#  undef warn\n#  undef warn_not_defined\n\
    // warn may be defined 2 times (by uncommenting line 17)\n#  ifdef warn\n#   \
    \ undef warn\n#  endif\n#endif\n\n#endif  // STATIC_MODINT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/algebra/static_modint.hpp
  requiredBy: []
  timestamp: '2021-08-03 15:46:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/combinatorics/factorial/1.test.cpp
  - test/combinatorics/factorial/2.test.cpp
  - test/algebra/pow/1.test.cpp
  - test/algebra/static_modint/3.test.cpp
  - test/algebra/static_modint/1.test.cpp
  - test/algebra/static_modint/2.test.cpp
  - test/data_structure/binary_indexed_tree/1.test.cpp
  - test/data_structure/binary_indexed_tree/2.test.cpp
documentation_of: include/algebra/static_modint.hpp
layout: document
title: Modint (for compile-time constant modulo)
---

「1000000007 で割った余りを求めよ」等の要求がある問題で使える `static_modint` 構造体が定義されています。演算子オーバーロードによって四則演算を行った時に指定された数で割った余りが自動的に計算されます。何で割った余りを求めるかがコンパイル時に確定しない場合(標準入力から与えられる等)には [`dynamic_modint`](https://naskya.github.io/cp-library/include/algebra/dynamic_modint.hpp) を使用してください。

---

### クラステンプレート

`static_modint` 構造体は 1 つの `std::int_least32_t` 型のテンプレート引数をとります。以下のように型エイリアスを宣言して使うとよいです。

```cpp
using mint = lib::static_modint<1000000007>;
```

計算の高速化のために、`static_modint<M>` 型の 2 つの値を足し合わせても(剰余を計算する前の時点で)オーバーフローが起きない事を仮定しています。そのため、`std::int_least32_t` の最大値の半分を超える値をテンプレート引数に取ることはできません。

```cpp
using mint = lib::static_modint<2000000000>;  // error
```

この仕様でも多くの競技プログラミングの問題では困らないはずです。

$p$ が素数のとき、`static_modint<p>` は $0$ から $p - 1$ までの $p$ 個の元からなる剰余体 $\mathbf{Z}/p\mathbf{Z}$ を表す型として扱えます。

### コンストラクタ

```cpp
using mint = lib::static_modint<1000000007>;

mint a;                   // 1.
std::vector<mint> A(10);  // 1.

mint b = 100;             // 2.
mint c = 10000000000LL;   // 2.
mint d(10000000000LL);    // 2.

static_assert(a == 0);
assert(std::all_of(std::cbegin(A), std::cend(A), [](auto val) { val == 0; }));
static_assert(b == 100);
static_assert(c == (10000000000LL % mint::mod()));
static_assert(d == (10000000000LL % mint::mod()));
```

1. 引数無しで初期化すると、値は 0 で初期化されます。
1. 引数を 1 つ与えて初期化すると、値が代入されます。必要に応じて余りも計算されます。

### 演算子

以下の演算子がオーバーロードされています。

- `++` (前置, 後置)
- `--` (前置, 後置)
- `+` (単項, 二項)
- `-` (単項, 二項)
- `*` (二項)
- `/`
- `+=`
- `-=`
- `*=`
- `/=`
- `==`
- `!=`
- `>>` (`std::istream&` からの入力)
- `<<` (`std::ostream&` への出力)

以下の演算子もオーバーロードされていますが、使用すると標準エラー出力に警告が出ます。この警告は 16 行目のコメントアウトを解除すると抑制できます。

- `%`
- `|`
- `^`
- `&` (二項)
- `>>` (ビット演算)
- `<<` (ビット演算)
- `%=`
- `|=`
- `^=`
- `&=`
- `>>=`
- `<<=`
- `>`
- `<`
- `>=`
- `<=`
- `!`
- `~`

### メンバ関数

以下の関数が使用できます。ここで、変数が保持している値を $x$ とします。

#### `inv()`

$x$ の乗法の逆元 $x^{-1}$ を返します。$x = 0$ である時の動作は未定義です。

#### `pow(n)`

$x^n$ を返します。

#### `to_frac()`

$x = a \cdot b^{-1}$ であるような $(a, b)$ の組のうち $a + b$ が最小であるものを返します。例えば $x = 2$ の時 `x.inv().to_frac()` は $(1, 2)$ を返します。

---
