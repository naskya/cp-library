
//! @file static_modint.hpp
//! @brief Modint (for compile-time constant modulo)

#ifndef STATIC_MODINT_HPP
#define STATIC_MODINT_HPP

#include <cstdint>
#include <iostream>
#include <limits>
#include <type_traits>

#ifndef warn
//! @brief Print warning message
//! @note You can suppress the warning by uncommenting line 17
#  define warn(msg) (std::cerr << (msg) << '\n')
// #  define warn(msg) (static_cast<void>(0))
#  define warn_not_defined
#endif

namespace lib {

//! @brief modint (for compile-time constant modulo)
//! @tparam modulo modulo (e.g. 1000000007).
template <std::int_least32_t modulo,
          std::enable_if_t<(1 < modulo) && (modulo < std::numeric_limits<std::int_least32_t>::max() / 2),
                           std::nullptr_t> = nullptr>
struct static_modint {
private:
  std::int_least32_t value;

  //! @param n non-zero integer
  //! @return multiplicative inverse of n
  template <typename Tp>
  [[nodiscard]] static constexpr std::int_least32_t calc_inverse(Tp n) noexcept {
    Tp b = modulo, u = 1, v = 0, t;
    while (b > 0) {
      t = n / b;
      // std::swap is not necessarily constexpr in C++17
      // std::swap(n -= t * b, b);
      Tp tmp = std::move(n -= t * b);
      n      = std::move(b);
      b      = std::move(tmp);
      // std::swap(u -= t * v, v);
      tmp = std::move(u -= t * v);
      u   = std::move(v);
      v   = std::move(tmp);
    }
    if (u < 0) u += modulo;
    return static_cast<std::int_least32_t>(u);
  }

  //! @brief Calculate modulo and keep the value within [0, modulo)
  //! @param v integer
  //! @return integer within [0, modulo)
  //! @note Time complexity: O(1)
  template <typename Tp>
  [[nodiscard]] static constexpr std::int_least32_t clamp_ll(Tp v) noexcept {
    if (modulo <= v || v < -modulo) v %= modulo;
    if (v < 0) v += modulo;
    return static_cast<std::int_least32_t>(v);
  }

  //! @brief Calculate modulo and keep the value within [0, modulo)
  //! @note Time complexity: O(1)
  constexpr void clamp_self() noexcept {
    if (0 <= value) {
      if (value < modulo) return;
      if (value < modulo * 2)
        value -= modulo;
      else
        value -= modulo * 2;
    } else {
      if (-modulo < value)
        value += modulo;
      else if (-modulo * 2 < value)
        value += modulo * 2;
      else {
        value += modulo;
        value += modulo * 2;
      }
    }
  }

public:
  //! @brief underlying integer type
  using type = std::int_least32_t;

  //! @return modulo (e.g. 1000000007)
  [[nodiscard]] static constexpr type mod() noexcept {
    return modulo;
  }

  //! @brief Create a modint of value 0
  constexpr static_modint() noexcept : value(0) {}

  //! @brief Create a modint without taking modulo
  constexpr static_modint(const type v, bool) noexcept : value(v) {}

  //! @brief Create a modint
  template <typename ValueType>
  constexpr static_modint(const ValueType v) noexcept {
    if constexpr (std::is_integral_v<ValueType> && (std::numeric_limits<ValueType>::digits <= 32)) {
      value = v;
      clamp_self();
    } else {
      value = clamp_ll(v);
    }
  }

  [[nodiscard]] constexpr static_modint operator+(const static_modint rhs) const noexcept {
    return static_modint(value + rhs.value);
  }
  [[nodiscard]] constexpr static_modint operator-(const static_modint rhs) const noexcept {
    return static_modint(value - rhs.value);
  }
  [[nodiscard]] constexpr static_modint operator*(const static_modint rhs) const noexcept {
    return static_modint(static_cast<std::int_least64_t>(value) * rhs.value);
  }
  [[nodiscard]] constexpr static_modint operator/(const static_modint rhs) const {
    return static_modint(static_cast<std::int_least64_t>(value) * calc_inverse(rhs.value));
  }

  [[nodiscard]] constexpr static_modint operator%(const static_modint rhs) const {
    warn("operator% : Are you sure you want to do this?");
    return static_modint(value % rhs.value);
  }

  [[nodiscard]] constexpr static_modint operator&(const static_modint rhs) const {
    warn("operator& : Are you sure you want to do this?");
    return static_modint(value & rhs.value, true);
  }
  [[nodiscard]] constexpr static_modint operator|(const static_modint rhs) const {
    warn("operator| : Are you sure you want to do this?");
    return static_modint(value | rhs.value);
  }
  [[nodiscard]] constexpr static_modint operator^(const static_modint rhs) const {
    warn("operator^ : Are you sure you want to do this?");
    return static_modint(value ^ rhs.value);
  }
  [[nodiscard]] constexpr static_modint operator<<(const static_modint rhs) const {
    warn("operator<< : Are you sure you want to do this?");
    return static_modint(static_cast<std::int_least64_t>(value) << rhs.value);
  }
  [[nodiscard]] constexpr static_modint operator>>(const static_modint rhs) const {
    warn("operator>> : Are you sure you want to do this?");
    return static_modint(value >> rhs.value, true);
  }

  constexpr static_modint& operator+=(const static_modint rhs) noexcept {
    value += rhs.value;
    if (value >= modulo) value -= modulo;
    return *this;
  }
  constexpr static_modint& operator-=(const static_modint rhs) noexcept {
    value -= rhs.value;
    if (value < 0) value += modulo;
    return *this;
  }
  constexpr static_modint& operator*=(const static_modint rhs) noexcept {
    value = clamp_ll(static_cast<std::int_least64_t>(value) * rhs.value);
    return *this;
  }
  constexpr static_modint& operator/=(const static_modint rhs) {
    value = clamp_ll(static_cast<std::int_least64_t>(value) * calc_inverse(rhs.value));
    return *this;
  }

  constexpr static_modint& operator%=(const static_modint rhs) {
    warn("operator%= : Are you sure you want to do this?");
    value %= rhs.value;
    if (value < 0) value += modulo;
    return *this;
  }

  constexpr static_modint& operator&=(const static_modint rhs) noexcept {
    warn("operator&= : Are you sure you want to do this?");
    value &= rhs.value;
    return *this;
  }
  constexpr static_modint& operator|=(const static_modint rhs) noexcept {
    warn("operator|= : Are you sure you want to do this?");
    value |= rhs.value;
    clamp_self();
    return *this;
  }
  constexpr static_modint& operator^=(const static_modint rhs) noexcept {
    warn("operator^= : Are you sure you want to do this?");
    value ^= rhs.value;
    clamp_self();
    return *this;
  }
  constexpr static_modint& operator<<=(const static_modint rhs) noexcept {
    warn("operator<<= : Are you sure you want to do this?");
    value = clamp_ll(static_cast<std::int_least64_t>(value) << rhs.value);
    return *this;
  }
  constexpr static_modint& operator>>=(const static_modint rhs) noexcept {
    warn("operator>>= : Are you sure you want to do this?");
    value >>= rhs.value;
    return *this;
  }

  template <typename RhsType>
  [[nodiscard]] constexpr static_modint operator+(const RhsType rhs) const noexcept {
    return static_modint(value + clamp_ll(rhs));
  }
  template <typename RhsType>
  [[nodiscard]] constexpr static_modint operator-(const RhsType rhs) const noexcept {
    return static_modint(value - clamp_ll(rhs));
  }
  template <typename RhsType>
  [[nodiscard]] constexpr static_modint operator*(const RhsType rhs) const noexcept {
    return static_modint(static_cast<std::int_least64_t>(value) * clamp_ll(rhs));
  }
  template <typename RhsType>
  [[nodiscard]] constexpr static_modint operator/(const RhsType rhs) const {
    std::int_least64_t mul = (rhs > 0) ? calc_inverse(rhs) : -calc_inverse(-rhs);
    return static_modint(value * mul);
  }

  template <typename RhsType>
  [[nodiscard]] constexpr static_modint operator%(const RhsType rhs) const {
    warn("operator% : Are you sure you want to do this?");
    return static_modint(value % rhs, true);
  }

  template <typename RhsType>
  [[nodiscard]] constexpr static_modint operator&(const RhsType rhs) const {
    warn("operator& : Are you sure you want to do this?");
    return static_modint(value & rhs, true);
  }
  template <typename RhsType>
  [[nodiscard]] constexpr static_modint operator|(const RhsType rhs) const {
    warn("operator| : Are you sure you want to do this?");
    return static_modint(value | rhs);
  }
  template <typename RhsType>
  [[nodiscard]] constexpr static_modint operator^(const RhsType rhs) const {
    warn("operator^ : Are you sure you want to do this?");
    return static_modint(value ^ rhs);
  }
  template <typename RhsType>
  [[nodiscard]] constexpr static_modint operator<<(const RhsType rhs) const {
    warn("operator<< : Are you sure you want to do this?");
    return static_modint(static_cast<std::int_least64_t>(value) << rhs);
  }
  template <typename RhsType>
  [[nodiscard]] constexpr static_modint operator>>(const RhsType rhs) const {
    warn("operator>> : Are you sure you want to do this?");
    return static_modint(value >> rhs, true);
  }

  template <typename RhsType> constexpr static_modint& operator+=(const RhsType rhs) noexcept {
    value = clamp_ll(static_cast<std::int_least64_t>(value) + rhs);
    return *this;
  }
  template <typename RhsType> constexpr static_modint& operator-=(const RhsType rhs) noexcept {
    value = clamp_ll(static_cast<std::int_least64_t>(value) - rhs);
    return *this;
  }
  template <typename RhsType> constexpr static_modint& operator*=(const RhsType rhs) noexcept {
    value = clamp_ll(static_cast<std::int_least64_t>(value) * clamp_ll(rhs));
    return *this;
  }
  template <typename RhsType> constexpr static_modint& operator/=(const RhsType rhs) {
    std::int_least64_t mul = (rhs > 0) ? calc_inverse(rhs) : -calc_inverse(-rhs);
    value                  = clamp_ll(value * mul);
    return *this;
  }

  template <typename RhsType> constexpr static_modint& operator%=(const RhsType rhs) {
    warn("operator%= : Are you sure you want to do this?");
    value %= rhs;
    return *this;
  }

  template <typename RhsType> constexpr static_modint& operator&=(const RhsType rhs) noexcept {
    warn("operator&= : Are you sure you want to do this?");
    value &= rhs;
    return *this;
  }
  template <typename RhsType> constexpr static_modint& operator|=(const RhsType rhs) noexcept {
    warn("operator|= : Are you sure you want to do this?");
    value |= rhs;
    clamp_self();
    return *this;
  }
  template <typename RhsType> constexpr static_modint& operator^=(const RhsType rhs) noexcept {
    warn("operator^= : Are you sure you want to do this?");
    value ^= rhs;
    clamp_self();
    return *this;
  }
  template <typename RhsType> constexpr static_modint& operator<<=(const RhsType rhs) noexcept {
    warn("operator<<= : Are you sure you want to do this?");
    value = clamp_ll(static_cast<std::int_least64_t>(value) << rhs);
    return *this;
  }
  template <typename RhsType> constexpr static_modint& operator>>=(const RhsType rhs) noexcept {
    warn("operator>>= : Are you sure you want to do this?");
    value >>= rhs;
    return *this;
  }

  [[nodiscard]] constexpr bool operator!() const {
    warn("operator! : Are you sure you want to do this?");
    return value == 0;
  }
  [[nodiscard]] constexpr static_modint operator~() const {
    warn("operator~ : Are you sure you want to do this?");
    return static_modint(~value);
  }
  [[nodiscard]] constexpr static_modint operator-() const noexcept {
    return static_modint(value == 0 ? 0 : modulo - value, true);
  }
  [[nodiscard]] constexpr static_modint& operator+() const noexcept {
    return *this;
  }

  constexpr static_modint& operator++() noexcept {
    value = ((value + 1 == modulo) ? 0 : value + 1);
    return *this;
  }
  constexpr static_modint& operator--() noexcept {
    value = ((value == 0) ? modulo - 1 : value - 1);
    return *this;
  }
  constexpr static_modint operator++(int) noexcept {
    std::int_least32_t res = value;
    ++(*this);
    return static_modint(res, true);
  }
  constexpr static_modint operator--(int) noexcept {
    std::int_least32_t res = value;
    --(*this);
    return static_modint(res, true);
  }

  [[nodiscard]] constexpr bool operator==(const static_modint rhs) const noexcept {
    return value == rhs.value;
  }
  [[nodiscard]] constexpr bool operator!=(const static_modint rhs) const noexcept {
    return value != rhs.value;
  }
  [[nodiscard]] constexpr bool operator<(const static_modint rhs) const {
    warn("operator< : Are you sure you want to do this?");
    return value < rhs.value;
  }
  [[nodiscard]] constexpr bool operator<=(const static_modint rhs) const {
    warn("operator<= : Are you sure you want to do this?");
    return value <= rhs.value;
  }
  [[nodiscard]] constexpr bool operator>(const static_modint rhs) const {
    warn("operator> : Are you sure you want to do this?");
    return value > rhs.value;
  }
  [[nodiscard]] constexpr bool operator>=(const static_modint rhs) const {
    warn("operator>= : Are you sure you want to do this?");
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
  [[nodiscard]] constexpr bool operator<(const RhsType rhs) const {
    warn("operator< : Are you sure you want to do this?");
    return value < rhs;
  }
  template <typename RhsType>
  [[nodiscard]] constexpr bool operator<=(const RhsType rhs) const {
    warn("operator<= : Are you sure you want to do this?");
    return value <= rhs;
  }
  template <typename RhsType>
  [[nodiscard]] constexpr bool operator>(const RhsType rhs) const {
    warn("operator> : Are you sure you want to do this?");
    return value > rhs;
  }
  template <typename RhsType>
  [[nodiscard]] constexpr bool operator>=(const RhsType rhs) const {
    warn("operator>= : Are you sure you want to do this?");
    return value >= rhs;
  }

  [[nodiscard]] constexpr operator std::int_least32_t() const noexcept {
    return value;
  }

  //! @brief Read value (64-bit signed integer) from std::istream& is, take modulo, and store it in rhs.
  //! @return std::istream& is
  friend std::istream& operator>>(std::istream& is, static_modint& rhs) {
    std::int_least64_t tmp;
    is >> tmp;
    if (tmp < -modulo || modulo <= tmp) tmp %= modulo;
    if (tmp < 0) tmp += modulo;
    rhs.value = static_cast<std::int_least32_t>(tmp);
    return is;
  }
  //! @brief Print value to std::ostream& os
  //! @return std::ostream& os
  friend std::ostream& operator<<(std::ostream& os, static_modint& rhs) {
    return os << rhs.value;
  }

  //! @return multiplicative inverse
  [[nodiscard]] constexpr static_modint inv() const {
    return static_modint(calc_inverse(value), true);
  }
  //! @tparam index_positive_guaranteed set true if and only if you can promise that index is positive
  //! @tparam Tp integer type (deduced from parameter)
  //! @param index index. This must be an integer, but doesn't have to be primitive.
  //! @return index-th power of the value
  //! @note Time complexity: O(log(index))
  template <bool index_positive_guaranteed = true, typename Tp = std::int_least32_t>
  [[nodiscard]] constexpr static_modint pow(Tp index) const noexcept {
    if constexpr (!index_positive_guaranteed) {
      if (value == 0) return static_modint(0, true);
      if (index == 0) return static_modint(1, true);
      if (index < 0) return static_modint(value, true).inv().pow<true>(-index);
    }
    static_modint res(1, true), base(value, true);
    while (index > 0) {
      if ((index & 1) == 1) res *= base;
      base *= base;
      index >>= 1;
    }
    return res;
  }
  //! @return a pair (a, b) such that b > 0, value is equal to a * (mult inverse of b), and (a + b) is minimal
  [[nodiscard]] constexpr std::pair<std::int_least32_t, std::int_least32_t> to_frac() const noexcept {
    std::int_least32_t x = modulo - value, y = value, u = 1, v = 1;
    std::pair<std::int_least32_t, std::int_least32_t> res {value, 1};

    std::int_least32_t num = value, den = 1;
    std::int_least32_t cost = num + den;

    while (x > 0) {
      if (x <= num) {
        std::int_least32_t q = num / x;
        num                  = num % x;
        den += q * u;
        if (num == 0) break;
        if (num + den < cost) {
          cost       = num + den;
          res.first  = num;
          res.second = den;
        }
      }
      std::int_least32_t q = y / x;
      y                    = y % x;
      v += q * u;
      q = x / y;
      x = x % y;
      u += q * v;
    }

    return res;
  }
};

template <typename LhsType, std::int_least32_t modulo>
[[nodiscard]] constexpr static_modint<modulo> operator+(const LhsType lhs, const static_modint<modulo> rhs) noexcept {
  return rhs + lhs;
}
template <typename LhsType, std::int_least32_t modulo>
[[nodiscard]] constexpr static_modint<modulo> operator-(const LhsType lhs, const static_modint<modulo> rhs) noexcept {
  return -rhs + lhs;
}
template <typename LhsType, std::int_least32_t modulo>
[[nodiscard]] constexpr static_modint<modulo> operator*(const LhsType lhs, const static_modint<modulo> rhs) noexcept {
  return rhs * lhs;
}
template <typename LhsType, std::int_least32_t modulo>
[[nodiscard]] constexpr static_modint<modulo> operator/(const LhsType lhs, const static_modint<modulo> rhs) {
  return rhs.inv() * lhs;
}

template <typename LhsType, std::int_least32_t modulo>
[[nodiscard]] constexpr static_modint<modulo> operator%(const LhsType lhs, const static_modint<modulo> rhs) {
  warn("operator% : Are you sure you want to do this?");
  return static_modint<modulo>(lhs % static_cast<std::int_least32_t>(rhs), true);
}

template <typename LhsType, std::int_least32_t modulo, std::enable_if_t<std::is_integral_v<LhsType>, std::nullptr_t> = nullptr>
[[nodiscard]] constexpr static_modint<modulo> operator<<(const LhsType lhs, const static_modint<modulo> rhs) {
  warn("operator<< : Are you sure you want to do this?");
  return static_modint<modulo>(static_cast<std::int_least64_t>(lhs) << static_cast<std::int_least32_t>(rhs));
}
template <typename LhsType, std::int_least32_t modulo, std::enable_if_t<std::is_integral_v<LhsType>, std::nullptr_t> = nullptr>
[[nodiscard]] constexpr static_modint<modulo> operator>>(const LhsType lhs, const static_modint<modulo> rhs) {
  warn("operator>> : Are you sure you want to do this?");
  return static_modint<modulo>(lhs >> static_cast<std::int_least32_t>(rhs));
}

template <typename LhsType, std::int_least32_t modulo>
constexpr LhsType& operator+=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {
  return lhs += static_cast<std::int_least32_t>(rhs);
}
template <typename LhsType, std::int_least32_t modulo>
constexpr LhsType& operator-=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {
  return lhs -= static_cast<std::int_least32_t>(rhs);
}
template <typename LhsType, std::int_least32_t modulo>
constexpr LhsType& operator*=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {
  return lhs *= static_cast<std::int_least32_t>(rhs);
}
template <typename LhsType, std::int_least32_t modulo>
constexpr LhsType& operator/=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {
  return lhs /= static_cast<std::int_least32_t>(rhs);
}

template <typename LhsType, std::int_least32_t modulo>
constexpr LhsType& operator%=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {
  warn("operator%= : Are you sure you want to do this?");
  return lhs %= static_cast<std::int_least32_t>(rhs);
}

template <typename LhsType, std::int_least32_t modulo>
constexpr LhsType& operator&=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {
  warn("operator&= : Are you sure you want to do this?");
  return lhs &= static_cast<std::int_least32_t>(rhs);
}
template <typename LhsType, std::int_least32_t modulo>
constexpr LhsType& operator|=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {
  warn("operator|= : Are you sure you want to do this?");
  return lhs |= static_cast<std::int_least32_t>(rhs);
}
template <typename LhsType, std::int_least32_t modulo>
constexpr LhsType& operator^=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {
  warn("operator^= : Are you sure you want to do this?");
  return lhs ^= static_cast<std::int_least32_t>(rhs);
}
template <typename LhsType, std::int_least32_t modulo>
constexpr LhsType& operator<<=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {
  warn("operator<<= : Are you sure you want to do this?");
  return lhs <<= static_cast<std::int_least32_t>(rhs);
}
template <typename LhsType, std::int_least32_t modulo>
constexpr LhsType& operator>>=(LhsType& lhs, const static_modint<modulo> rhs) noexcept {
  warn("operator>>= : Are you sure you want to do this?");
  return lhs >>= static_cast<std::int_least32_t>(rhs);
}

template <typename LhsType, std::int_least32_t modulo>
[[nodiscard]] constexpr bool operator<(const LhsType lhs, const static_modint<modulo> rhs) {
  warn("operator< : Are you sure you want to do this?");
  return lhs < static_cast<std::int_least32_t>(rhs);
}
template <typename LhsType, std::int_least32_t modulo>
[[nodiscard]] constexpr bool operator<=(const LhsType lhs, const static_modint<modulo> rhs) {
  warn("operator<= : Are you sure you want to do this?");
  return lhs < static_cast<std::int_least32_t>(rhs);
}
template <typename LhsType, std::int_least32_t modulo>
[[nodiscard]] constexpr bool operator>(const LhsType lhs, const static_modint<modulo> rhs) {
  warn("operator> : Are you sure you want to do this?");
  return lhs < static_cast<std::int_least32_t>(rhs);
}
template <typename LhsType, std::int_least32_t modulo>
[[nodiscard]] constexpr bool operator>=(const LhsType lhs, const static_modint<modulo> rhs) {
  warn("operator>= : Are you sure you want to do this?");
  return lhs < static_cast<std::int_least32_t>(rhs);
}

}  // namespace lib

#ifdef warn_not_defined
#  undef warn
#  undef warn_not_defined
#endif

#endif  // STATIC_MODINT_HPP
