
//! @file pow.hpp

#ifndef CP_LIBRARY_POW_HPP
#define CP_LIBRARY_POW_HPP

#include <cassert>
#include <type_traits>

#ifndef CP_LIBRARY_ASSERT
//! @brief Assert macro
#  define CP_LIBRARY_ASSERT(...) assert(__VA_ARGS__)
#  define CP_LIBRARY_ASSERT_NOT_DEFINED
#endif

namespace lib {

//! @tparam ValueType base type (deduced from parameter).
//! @tparam IntType index type (deduced from parameter).
//! @param base base. This doesn't have to be an integer.
//! @param index index. This must be an integer, but doesn't have to be primitive.
//! @return the index-th power of base
//! @note Time complexity: O(log(index) * (time needed to calculate (base * base)))
template <typename ValueType, typename IntType>
[[nodiscard]] ValueType pow(ValueType base, IntType index) {
  if constexpr (!std::is_unsigned_v<IntType>)
    CP_LIBRARY_ASSERT(0 <= index);
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
[[nodiscard]] ValueType pow(ValueType base, IntType index, const ValueType& id) {
  if constexpr (!std::is_unsigned_v<IntType>)
    CP_LIBRARY_ASSERT(0 <= index);
  ValueType res = id;
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
[[nodiscard]] ValueType pow(ValueType base, IntType index, ValueType&& id) {
  if constexpr (!std::is_unsigned_v<IntType>)
    CP_LIBRARY_ASSERT(0 <= index);
  while (index != 0) {
    if ((index & 1) == 1)
      id *= base;
    base *= base;
    index >>= 1;
  }
  return id;
}

}  // namespace lib

#ifdef CP_LIBRARY_ASSERT_NOT_DEFINED
#  undef CP_LIBRARY_ASSERT
#  undef CP_LIBRARY_ASSERT_NOT_DEFINED
#endif

#endif  // CP_LIBRARY_POW_HPP
