
//! @file dynamic_modint.hpp

#ifndef CP_LIBRARY_DYNAMIC_MODINT_HPP
#define CP_LIBRARY_DYNAMIC_MODINT_HPP

#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <type_traits>

#define CP_LIBRARY_USE_CONSTEXPR

#ifndef CP_LIBRARY_WARN
#  if (CP_LIBRARY_DEBUG_LEVEL >= 1)
//! @brief Print warning message
//! @note You can suppress the warning by uncommenting the following line
#    define CP_LIBRARY_WARN(msg) (std::cerr << (msg) << '\n')
// #  define CP_LIBRARY_WARN(msg) (static_cast<void>(0))
#  else
#    define CP_LIBRARY_WARN(msg) (static_cast<void>(0))
#    undef CP_LIBRARY_USE_CONSTEXPR
#    define CP_LIBRARY_USE_CONSTEXPR constexpr
#  endif
#  define CP_LIBRARY_WARN_NOT_DEFINED
#endif

#ifndef CP_LIBRARY_ASSERT
//! @brief Assert macro
#  define CP_LIBRARY_ASSERT(...) assert(__VA_ARGS__)
#  define CP_LIBRARY_ASSERT_NOT_DEFINED
#endif

namespace lib {

namespace internal::dynamic_modint_hpp {
  template <typename Tp, std::enable_if_t<std::is_integral_v<Tp>, std::nullptr_t> = nullptr>
  using LongInt = std::conditional_t<(64 <= std::numeric_limits<Tp>::digits), __int128_t, std::int_least64_t>;
}

//! @brief modint (for runtime constant modulo)
//! @tparam Tp underlying integer type (e.g. int)
//! @tparam modulo_ptr pointer to modulo variable
template <typename Tp, Tp* modulo_ptr>
struct dynamic_modint {
private:
  Tp value;

  //! @param n non-zero integer
  //! @return multiplicative inverse of n
  //! @note Time complexity: O(log(n))
  template <typename Sp>
  [[nodiscard]] static Tp calc_inverse(Sp n) {
    CP_LIBRARY_ASSERT(n != 0);

    Tp b = *modulo_ptr, u = 1, v = 0, t;
    while (b > 0) {
      t      = n / b;
      Tp tmp = (n -= t * b);
      n      = b;
      b      = tmp;
      tmp    = (u -= t * v);
      u      = v;
      v      = tmp;
    }
    if (u < 0)
      u += *modulo_ptr;
    return static_cast<Tp>(u);
  }

  //! @brief Calculate modulo and keep the value within [0, modulo)
  //! @param v integer
  //! @return integer within [0, *modulo_ptr)
  //! @note Time complexity: O(1)
  template <typename Sp>
  static constexpr Tp clamp(Sp v) noexcept {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
    if (*modulo_ptr <= v || v < -*modulo_ptr)
      v %= *modulo_ptr;
#pragma GCC diagnostic pop
    if (v < 0)
      v += *modulo_ptr;
    return static_cast<Tp>(v);
  }

public:
  //! @brief underlying integer type
  using type = Tp;

  //! @return reference to modulo (e.g. 1000000007)
  [[nodiscard]] static type& mod() {
    return *modulo_ptr;
  }

  //! @brief Create a modint of value 0
  constexpr dynamic_modint() noexcept : value(0) {}

  //! @brief Create a modint without taking modulo
  constexpr dynamic_modint(const Tp v, bool) noexcept : value(v) {}

  //! @brief Create a modint
  template <typename ValueType>
  constexpr dynamic_modint(const ValueType v) noexcept : value(clamp(v)) {}

  [[nodiscard]] constexpr dynamic_modint operator+(const dynamic_modint rhs) const noexcept {
    return dynamic_modint(value + rhs.value);
  }
  [[nodiscard]] constexpr dynamic_modint operator-(const dynamic_modint rhs) const noexcept {
    return dynamic_modint(value - rhs.value);
  }
  [[nodiscard]] constexpr dynamic_modint operator*(const dynamic_modint rhs) const noexcept {
    return dynamic_modint((internal::dynamic_modint_hpp::LongInt<Tp>) value * rhs.value);
  }
  [[nodiscard]] dynamic_modint operator/(const dynamic_modint rhs) const {
    return dynamic_modint((internal::dynamic_modint_hpp::LongInt<Tp>) value * calc_inverse(rhs.value));
  }

  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator%(const dynamic_modint rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator% : Are you sure you want to do this?");
    return dynamic_modint(value % rhs.value, true);
  }

  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator&(const dynamic_modint rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator& : Are you sure you want to do this?");
    return dynamic_modint(value & rhs.value, true);
  }
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator|(const dynamic_modint rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator| : Are you sure you want to do this?");
    return dynamic_modint(value | rhs.value);
  }
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator^(const dynamic_modint rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator^ : Are you sure you want to do this?");
    return dynamic_modint(value ^ rhs.value);
  }
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator<<(const dynamic_modint rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator<< : Are you sure you want to do this?");
    return dynamic_modint((internal::dynamic_modint_hpp::LongInt<Tp>) value << rhs.value);
  }
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator>>(const dynamic_modint rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator>> : Are you sure you want to do this?");
    return dynamic_modint(value >> rhs.value, true);
  }

  constexpr dynamic_modint& operator+=(const dynamic_modint rhs) noexcept {
    value += rhs.value;
    if (value >= *modulo_ptr)
      value -= *modulo_ptr;
    return *this;
  }
  constexpr dynamic_modint& operator-=(const dynamic_modint rhs) noexcept {
    value -= rhs.value;
    if (value < 0)
      value += *modulo_ptr;
    return *this;
  }
  constexpr dynamic_modint& operator*=(const dynamic_modint rhs) noexcept {
    value = clamp((internal::dynamic_modint_hpp::LongInt<Tp>) value * rhs.value);
    return *this;
  }
  dynamic_modint& operator/=(const dynamic_modint rhs) {
    value = clamp((internal::dynamic_modint_hpp::LongInt<Tp>) value * calc_inverse(rhs.value));
    return *this;
  }

  CP_LIBRARY_USE_CONSTEXPR dynamic_modint& operator%=(const dynamic_modint rhs) {
    CP_LIBRARY_WARN("dynamic_modint::operator%= : Are you sure you want to do this?");

    value %= rhs.value;
    if (value < 0)
      value += *modulo_ptr;
    return *this;
  }

  CP_LIBRARY_USE_CONSTEXPR dynamic_modint& operator&=(const dynamic_modint rhs) noexcept {
    CP_LIBRARY_WARN("dynamic_modint::operator&= : Are you sure you want to do this?");
    value &= rhs.value;
    return *this;
  }
  CP_LIBRARY_USE_CONSTEXPR dynamic_modint& operator|=(const dynamic_modint rhs) noexcept {
    CP_LIBRARY_WARN("dynamic_modint::operator|= : Are you sure you want to do this?");
    value |= rhs.value;
    clamp();
    return *this;
  }
  CP_LIBRARY_USE_CONSTEXPR dynamic_modint& operator^=(const dynamic_modint rhs) noexcept {
    CP_LIBRARY_WARN("dynamic_modint::operator^= : Are you sure you want to do this?");
    value ^= rhs.value;
    clamp();
    return *this;
  }
  CP_LIBRARY_USE_CONSTEXPR dynamic_modint& operator<<=(const dynamic_modint rhs) noexcept {
    CP_LIBRARY_WARN("operator<<= : Are you sure you want to do this?");
    value = clamp((internal::dynamic_modint_hpp::LongInt<Tp>) value << rhs.value);
    return *this;
  }
  CP_LIBRARY_USE_CONSTEXPR dynamic_modint& operator>>=(const dynamic_modint rhs) noexcept {
    CP_LIBRARY_WARN("operator>>= : Are you sure you want to do this?");
    value >>= rhs.value;
    return *this;
  }

  template <typename RhsType>
  [[nodiscard]] constexpr dynamic_modint operator+(const RhsType rhs) const noexcept {
    return dynamic_modint(value + clamp(rhs));
  }
  template <typename RhsType>
  [[nodiscard]] constexpr dynamic_modint operator-(const RhsType rhs) const noexcept {
    return dynamic_modint(value - clamp(rhs));
  }
  template <typename RhsType>
  [[nodiscard]] constexpr dynamic_modint operator*(const RhsType rhs) const noexcept {
    return dynamic_modint((internal::dynamic_modint_hpp::LongInt<Tp>) value * clamp(rhs));
  }
  template <typename RhsType>
  [[nodiscard]] dynamic_modint operator/(const RhsType rhs) const {
    internal::dynamic_modint_hpp::LongInt<Tp> mul = (rhs > 0) ? calc_inverse(rhs) : -calc_inverse(-rhs);
    return dynamic_modint(mul * value);
  }

  template <typename RhsType>
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator%(const RhsType rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator% : Are you sure you want to do this?");
    return dynamic_modint(value % rhs, true);
  }

  template <typename RhsType>
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator&(const RhsType rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator& : Are you sure you want to do this?");
    return dynamic_modint(value & rhs, true);
  }
  template <typename RhsType>
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator|(const RhsType rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator| : Are you sure you want to do this?");
    return dynamic_modint(value | rhs);
  }
  template <typename RhsType>
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator^(const RhsType rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator^ : Are you sure you want to do this?");
    return dynamic_modint(value ^ rhs);
  }
  template <typename RhsType>
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator<<(const RhsType rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator<< : Are you sure you want to do this?");
    return dynamic_modint((internal::dynamic_modint_hpp::LongInt<Tp>) value << rhs);
  }
  template <typename RhsType>
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator>>(const RhsType rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator>> : Are you sure you want to do this?");
    return dynamic_modint(value >> rhs, true);
  }

  template <typename RhsType>
  constexpr dynamic_modint& operator+=(const RhsType rhs) noexcept {
    value = clamp(value + clamp(rhs));
    return *this;
  }
  template <typename RhsType>
  constexpr dynamic_modint& operator-=(const RhsType rhs) noexcept {
    value = clamp(value - clamp(rhs));
    return *this;
  }
  template <typename RhsType>
  constexpr dynamic_modint& operator*=(const RhsType rhs) noexcept {
    value = clamp(value * clamp(rhs));
    return *this;
  }
  template <typename RhsType>
  dynamic_modint& operator/=(const RhsType rhs) {
    internal::dynamic_modint_hpp::LongInt<Tp> mul = (rhs > 0) ? calc_inverse(rhs) : -calc_inverse(-rhs);
    value                                         = clamp(mul * value);
    return *this;
  }

  template <typename RhsType>
  CP_LIBRARY_USE_CONSTEXPR dynamic_modint& operator%=(const RhsType rhs) {
    CP_LIBRARY_WARN("dynamic_modint::operator%= : Are you sure you want to do this?");
    value %= rhs;
    return *this;
  }

  template <typename RhsType>
  CP_LIBRARY_USE_CONSTEXPR dynamic_modint& operator&=(const RhsType rhs) {
    CP_LIBRARY_WARN("dynamic_modint::operator&= : Are you sure you want to do this?");
    value &= rhs;
    return *this;
  }
  template <typename RhsType>
  CP_LIBRARY_USE_CONSTEXPR dynamic_modint& operator|=(const RhsType rhs) {
    CP_LIBRARY_WARN("dynamic_modint::operator|= : Are you sure you want to do this?");
    value |= rhs;
    clamp();
    return *this;
  }
  template <typename RhsType>
  CP_LIBRARY_USE_CONSTEXPR dynamic_modint& operator^=(const RhsType rhs) {
    CP_LIBRARY_WARN("dynamic_modint::operator^= : Are you sure you want to do this?");
    value ^= rhs;
    clamp();
    return *this;
  }
  template <typename RhsType>
  CP_LIBRARY_USE_CONSTEXPR dynamic_modint& operator<<=(const RhsType rhs) {
    CP_LIBRARY_WARN("operator<<= : Are you sure you want to do this?");
    value = clamp((internal::dynamic_modint_hpp::LongInt<Tp>) value << rhs);
    return *this;
  }
  template <typename RhsType>
  CP_LIBRARY_USE_CONSTEXPR dynamic_modint& operator>>=(const RhsType rhs) {
    CP_LIBRARY_WARN("operator>>= : Are you sure you want to do this?");
    value >>= rhs;
    return *this;
  }

  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator!() const {
    CP_LIBRARY_WARN("dynamic_modint::operator! : Are you sure you want to do this?");
    return value == 0;
  }
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint operator~() const {
    CP_LIBRARY_WARN("dynamic_modint::operator~ : Are you sure you want to do this?");
    return dynamic_modint(~value);
  }
  [[nodiscard]] constexpr dynamic_modint operator-() const noexcept {
    return dynamic_modint(value == 0 ? 0 : *modulo_ptr - value, true);
  }
  [[nodiscard]] constexpr dynamic_modint& operator+() const noexcept {
    return *this;
  }

  constexpr dynamic_modint& operator++() noexcept {
    value = ((value + 1 == *modulo_ptr) ? 0 : value + 1);
    return *this;
  }
  constexpr dynamic_modint& operator--() noexcept {
    value = ((value == 0) ? *modulo_ptr - 1 : value - 1);
    return *this;
  }
  constexpr dynamic_modint operator++(int) noexcept {
    Tp res = value;
    ++(*this);
    return dynamic_modint(res, true);
  }
  constexpr dynamic_modint operator--(int) noexcept {
    Tp res = value;
    --(*this);
    return dynamic_modint(res, true);
  }

  [[nodiscard]] constexpr bool operator==(const dynamic_modint rhs) const noexcept {
    return value == rhs.value;
  }
  [[nodiscard]] constexpr bool operator!=(const dynamic_modint rhs) const noexcept {
    return value != rhs.value;
  }
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator<(const dynamic_modint rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator< : Are you sure you want to do this?");
    return value < rhs.value;
  }
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator<=(const dynamic_modint rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator<= : Are you sure you want to do this?");
    return value <= rhs.value;
  }
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator>(const dynamic_modint rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator> : Are you sure you want to do this?");
    return value > rhs.value;
  }
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator>=(const dynamic_modint rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator>= : Are you sure you want to do this?");
    return value >= rhs.value;
  }

  template <typename RhsType>
  [[nodiscard]] constexpr bool operator==(const RhsType rhs) const noexcept {
    return value == rhs;
  }
  template <typename RhsType>
  [[nodiscard]] constexpr bool operator!=(const RhsType rhs) const noexcept {
    return value != rhs;
  }
  template <typename RhsType>
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator<(const RhsType rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator< : Are you sure you want to do this?");
    return value < rhs;
  }
  template <typename RhsType>
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator<=(const RhsType rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator<= : Are you sure you want to do this?");
    return value <= rhs;
  }
  template <typename RhsType>
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator>(const RhsType rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator> : Are you sure you want to do this?");
    return value > rhs;
  }
  template <typename RhsType>
  [[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator>=(const RhsType rhs) const {
    CP_LIBRARY_WARN("dynamic_modint::operator>= : Are you sure you want to do this?");
    return value >= rhs;
  }

  [[nodiscard]] constexpr operator Tp() const {
    CP_LIBRARY_WARN("A value of type static_modint has been cast to a primitive integer type.");
    return value;
  }

  //! @brief Read value (64-bit signed integer) from std::istream& is, take modulo, and store it in rhs.
  //! @return std::istream& is
  friend std::istream& operator>>(std::istream& is, dynamic_modint& rhs) {
    std::conditional_t<std::is_integral_v<Tp>, long long, Tp> tmp;
    is >> tmp;
    if (tmp < -*modulo_ptr || *modulo_ptr <= tmp)
      tmp %= *modulo_ptr;
    if (tmp < 0)
      tmp += *modulo_ptr;
    rhs.value = Tp(tmp);
    return is;
  }
  //! @brief Print value to std::ostream& os
  //! @return std::ostream& os
  friend std::ostream& operator<<(std::ostream& os, dynamic_modint& rhs) {
    return os << rhs.value;
  }

  //! @return multiplicative inverse
  [[nodiscard]] dynamic_modint inv() const {
    return dynamic_modint(calc_inverse(value), true);
  }
  //! @tparam index_positive_guaranteed set true if and only if you can promise that index is positive
  //! @tparam Tp integer type (deduced from parameter)
  //! @param index index. This must be an integer, but doesn't have to be primitive.
  //! @return index-th power of the value
  //! @note Time complexity: O(log(index))
  template <bool index_positive_guaranteed = true, typename T = int>
  [[nodiscard]] dynamic_modint pow(T index) const {
    if constexpr (!index_positive_guaranteed) {
      if (value == 0)
        return dynamic_modint(0, true);
      if (index == 0)
        return dynamic_modint(1, true);
      if (index < 0)
        return dynamic_modint(value, true).inv().pow<true>(-index);
    }
    dynamic_modint res(1, true), base(value, true);
    while (index > 0) {
      if (index & 1)
        res *= base;
      base *= base;
      index >>= 1;
    }
    return res;
  }
  //! @return a pair (a, b) such that b > 0, value is equal to a * (mult inverse of b), and (a + b) is minimal
  [[nodiscard]] constexpr std::pair<Tp, Tp> to_frac() const noexcept {
    Tp x = (*modulo_ptr) - value, y = value, u = 1, v = 1;
    std::pair<Tp, Tp> res {value, 1};

    Tp num = value, den = 1;
    Tp cost = num + den;

    while (x > 0) {
      if (x <= num) {
        Tp q = num / x;
        num  = num % x;
        den += q * u;
        if (num == 0)
          break;
        if (num + den < cost) {
          cost       = num + den;
          res.first  = num;
          res.second = den;
        }
      }
      Tp q = y / x;
      y    = y % x;
      v += q * u;
      q = x / y;
      x = x % y;
      u += q * v;
    }

    return res;
  }
};

template <typename LhsType, typename Tp, Tp* modulo_ptr>
[[nodiscard]] constexpr dynamic_modint<Tp, modulo_ptr> operator+(const LhsType lhs, const dynamic_modint<Tp, modulo_ptr> rhs) noexcept {
  return rhs + lhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
[[nodiscard]] constexpr dynamic_modint<Tp, modulo_ptr> operator-(const LhsType lhs, const dynamic_modint<Tp, modulo_ptr> rhs) noexcept {
  return -rhs + lhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
[[nodiscard]] constexpr dynamic_modint<Tp, modulo_ptr> operator*(const LhsType lhs, const dynamic_modint<Tp, modulo_ptr> rhs) noexcept {
  return rhs * lhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
[[nodiscard]] dynamic_modint<Tp, modulo_ptr> operator/(const LhsType lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  return rhs.inv() * lhs;
}

template <typename LhsType, typename Tp, Tp* modulo_ptr>
[[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint<Tp, modulo_ptr>
operator%(const LhsType lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("dynamic_modint::operator% : Are you sure you want to do this?");
  return dynamic_modint<Tp, modulo_ptr>(lhs % (Tp) rhs, true);
}

template <typename LhsType, typename Tp, Tp* modulo_ptr, std::enable_if_t<std::is_integral_v<LhsType>, std::nullptr_t> = nullptr>
[[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint<Tp, modulo_ptr>
operator<<(const LhsType lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("dynamic_modint::operator<< : Are you sure you want to do this?");
  return dynamic_modint<Tp, modulo_ptr>((internal::dynamic_modint_hpp::LongInt<Tp>) lhs << (Tp) rhs);
}
template <typename LhsType, typename Tp, Tp* modulo_ptr, std::enable_if_t<std::is_integral_v<LhsType>, std::nullptr_t> = nullptr>
[[nodiscard]] CP_LIBRARY_USE_CONSTEXPR dynamic_modint<Tp, modulo_ptr>
operator>>(const LhsType lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("dynamic_modint::operator>> : Are you sure you want to do this?");
  return dynamic_modint<Tp, modulo_ptr>(lhs >> (Tp) rhs);
}

template <typename LhsType, typename Tp, Tp* modulo_ptr>
CP_LIBRARY_USE_CONSTEXPR LhsType& operator+=(LhsType& lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  return lhs += (Tp) rhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
CP_LIBRARY_USE_CONSTEXPR LhsType& operator-=(LhsType& lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  return lhs -= (Tp) rhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
CP_LIBRARY_USE_CONSTEXPR LhsType& operator*=(LhsType& lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  return lhs *= (Tp) rhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
CP_LIBRARY_USE_CONSTEXPR LhsType& operator/=(LhsType& lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  return lhs /= (Tp) rhs;
}

template <typename LhsType, typename Tp, Tp* modulo_ptr>
CP_LIBRARY_USE_CONSTEXPR LhsType& operator%=(LhsType& lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("dynamic_modint::operator%= : Are you sure you want to do this?");
  return lhs %= (Tp) rhs;
}

template <typename LhsType, typename Tp, Tp* modulo_ptr>
CP_LIBRARY_USE_CONSTEXPR LhsType& operator&=(LhsType& lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("dynamic_modint::operator&= : Are you sure you want to do this?");
  return lhs &= (Tp) rhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
CP_LIBRARY_USE_CONSTEXPR LhsType& operator|=(LhsType& lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("dynamic_modint::operator|= : Are you sure you want to do this?");
  return lhs |= (Tp) rhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
CP_LIBRARY_USE_CONSTEXPR LhsType& operator^=(LhsType& lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("dynamic_modint::operator^= : Are you sure you want to do this?");
  return lhs ^= (Tp) rhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
CP_LIBRARY_USE_CONSTEXPR LhsType& operator<<=(LhsType& lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("operator<<= : Are you sure you want to do this?");
  return lhs <<= (Tp) rhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
CP_LIBRARY_USE_CONSTEXPR LhsType& operator>>=(LhsType& lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("operator>>= : Are you sure you want to do this?");
  return lhs >>= (Tp) rhs;
}

template <typename LhsType, typename Tp, Tp* modulo_ptr>
[[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator<(const LhsType lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("dynamic_modint::operator< : Are you sure you want to do this?");
  return lhs < (Tp) rhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
[[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator<=(const LhsType lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("dynamic_modint::operator<= : Are you sure you want to do this?");
  return lhs < (Tp) rhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
[[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator>(const LhsType lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("dynamic_modint::operator> : Are you sure you want to do this?");
  return lhs < (Tp) rhs;
}
template <typename LhsType, typename Tp, Tp* modulo_ptr>
[[nodiscard]] CP_LIBRARY_USE_CONSTEXPR bool operator>=(const LhsType lhs, const dynamic_modint<Tp, modulo_ptr> rhs) {
  CP_LIBRARY_WARN("dynamic_modint::operator>= : Are you sure you want to do this?");
  return lhs < (Tp) rhs;
}

}  // namespace lib

#undef CP_LIBRARY_USE_CONSTEXPR

#ifdef CP_LIBRARY_WARN_NOT_DEFINED
#  undef CP_LIBRARY_WARN
#  undef CP_LIBRARY_WARN_NOT_DEFINED
#  ifdef CP_LIBRARY_WARN
#    undef CP_LIBRARY_WARN
#  endif
#endif

#ifdef CP_LIBRARY_ASSERT_NOT_DEFINED
#  undef CP_LIBRARY_ASSERT
#  undef CP_LIBRARY_ASSERT_NOT_DEFINED
#endif

#endif  // CP_LIBRARY_DYNAMIC_MODINT_HPP
