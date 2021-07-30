
//! @file pow.hpp

#ifndef POW_HPP
#define POW_HPP

namespace lib {

//! @tparam ValueType base type (deduced from parameter).
//! @tparam IntType index type (deduced from parameter).
//! @param base base. This doesn't have to be an integer.
//! @param index index. This must be an integer, but doesn't have to be primitive.
//! @return the index-th power of base
//! @note Time complexity: O(log(index) * (time needed to calculate (base * base)))
template <typename ValueType, typename IntType>
[[nodiscard]] ValueType pow(ValueType base, IntType index) {
  ValueType res = 1;
  while (index != 0) {
    if ((index & 1) == 1)
      res *= base;
    base *= base;
    index >>= 1;
  }
  return res;
}

//! @tparam ValueType base type (deduced from parameter).
//! @tparam IntType index type (deduced from parameter).
//! @param base base. This doesn't have to be an integer.
//! @param index index. This must be an integer, but doesn't have to be primitive.
//! @param id multiplicative identity
//! @return the index-th power of base
//! @note Time complexity: O(log(index) * (time needed to calculate (base * base)))
template <typename ValueType, typename IntType>
[[nodiscard]] ValueType pow(ValueType base, IntType index, ValueType id) {
  while (index != 0) {
    if ((index & 1) == 1)
      id *= base;
    base *= base;
    index >>= 1;
  }
  return id;
}

}  // namespace lib

#endif  // POW_HPP
