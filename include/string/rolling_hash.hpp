
//! @file rolling_hash.hpp
//! @note The implementation is based on this article https://qiita.com/keymoon/items/11fac5627672a6d6a9f6

#ifndef CP_LIBRARY_ROLLING_HASH_HPP
#define CP_LIBRARY_ROLLING_HASH_HPP

#ifndef CP_LIBRARY_ROLLING_HASH_MAX_LENGTH
#  warning Please define CP_LIBRARY_ROLLING_HASH_MAX_LENGTH (default: 200000).
#  define CP_LIBRARY_ROLLING_HASH_MAX_LENGTH 200000
#  define CP_LIBRARY_ROLLING_HASH_MAX_LENGTH_NOT_DEFINED
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <vector>

#ifndef CP_LIBRARY_ASSERT
//! @brief Assert macro
#  define CP_LIBRARY_ASSERT(...) assert(__VA_ARGS__)
#  define CP_LIBRARY_ASSERT_NOT_DEFINED
#endif

#ifndef CP_LIBRARY_ERROR
#  if (CP_LIBRARY_DEBUG_LEVEL >= 2)
//! @brief Print error message and exit
#    define CP_LIBRARY_ERROR(...) \
      do {                        \
        __VA_ARGS__               \
        CP_LIBRARY_ASSERT(false); \
      } while (false)
#  else
#    define CP_LIBRARY_ERROR(...) (static_cast<void>(0))
#  endif
#  define CP_LIBRARY_ERROR_NOT_DEFINED
#endif

namespace lib {

namespace internal::rolling_hash_hpp {
  using u64 = std::uint_least64_t;

  template <unsigned index>
  constexpr u64 mask = (u64(1) << index) - 1;

  template <unsigned index>
  constexpr u64 pad = mask<index>* mask<std::numeric_limits<u64>::digits - index>;

  [[gnu::const]] [[nodiscard]] constexpr u64 mod_mersenne_61(const u64 x) noexcept {
    if (const u64 res = (x >> 61) + (x & mask<61>); res >= mask<61>)
      return res - mask<61>;
    else
      return res;
  }

  [[gnu::const]] [[nodiscard]] constexpr u64 mult(const u64 x, const u64 y) noexcept {
    const u64 x_upper = (x >> 31);
    const u64 x_lower = (x & mask<31>);
    const u64 y_upper = (y >> 31);
    const u64 y_lower = (y & mask<31>);
    const u64 z       = x_upper * y_lower + x_lower * y_upper;
    return ((x_upper * y_upper) << 1) + (z >> 30) + ((z & mask<30>) << 31) + (x_lower * y_lower);
  }

  template <u64 base>
  [[nodiscard]] u64 pow_mod_mersenne_61(unsigned index) {
    static bool first = true;
    static std::array<u64, CP_LIBRARY_ROLLING_HASH_MAX_LENGTH + 1> res;

    if (__builtin_expect(first, 0)) {
      first  = false;
      res[0] = 1;
      for (unsigned i = 1; i <= CP_LIBRARY_ROLLING_HASH_MAX_LENGTH; ++i)
        res[i] = mod_mersenne_61(mult(res[i - 1], base));
    }

    return res[index];
  }

  template <class TupleType, std::size_t... Is>
  void print_tuple(const TupleType& arg, std::ostream& os, std::index_sequence<Is...>) {
    static_cast<void>(((os << (Is == 0 ? "" : ", "), (os << std::get<Is>(arg))), ...));
  }

  // Using the following type alias unables GCC to compile the code. (no problem with Clang/MSVC. maybe a bug.)
  // template <std::uint32_t... Bases>
  // using hash_t = decltype(std::tuple {(static_cast<u64>(Bases))...});
  // See:  https://wandbox.org/permlink/xpqiYobUkI1EGpgo (on GCC 12.0.0)
  //       https://wandbox.org/permlink/26ZTzuIfTivSz2lR (on Clang 13.0.0)
  // ToDo: Replace decltype(std::tuple {(static_cast<u64>(Bases))...}) with hash_t<Bases...>
  //       and replace decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...}) with internal::rolling_hash_hpp::hash_t<Bases...>
  //       when we figure out the workaround or this bug(?) is fixed.

  template <std::uint32_t... Bases, typename Container, std::size_t... Is>
  void build_hash_sequence_impl(const Container& src,
                                std::vector<decltype(std::tuple {(static_cast<u64>(Bases))...})>& dest,
                                std::index_sequence<Is...>) {
    constexpr std::tuple bases_tuple = std::tuple {Bases...};
    const std::size_t size           = std::size(src);
    auto iter                        = std::cbegin(src);

    for (std::size_t i = 0; i < size; ++iter, ++i)
      static_cast<void>(((std::get<Is>(dest[i + 1]) = mod_mersenne_61(mult(std::get<Is>(dest[i]), std::get<Is>(bases_tuple)) + static_cast<u64>(*iter))), ...));
  }

  template <std::uint32_t... Bases, typename Container>
  [[nodiscard]] std::vector<decltype(std::tuple {(static_cast<u64>(Bases))...})> build_hash_sequence(const Container& src) {
    std::vector<decltype(std::tuple {(static_cast<u64>(Bases))...})> res(std::size(src) + 1);
    build_hash_sequence_impl<Bases...>(src, res, std::make_index_sequence<sizeof...(Bases)> {});
    return res;
  }

  template <std::uint32_t... Bases, std::size_t... Is>
  [[nodiscard]] constexpr decltype(std::tuple {(static_cast<u64>(Bases))...}) substr_hash_impl(const std::vector<decltype(std::tuple {(static_cast<u64>(Bases))...})>& hashes, const int starts, const int length, std::index_sequence<Is...>) {
    constexpr std::tuple bases_tuple = std::tuple {Bases...};
    decltype(std::tuple {(static_cast<u64>(Bases))...}) res;
    static_cast<void>(((std::get<Is>(res) = mod_mersenne_61(std::get<Is>(hashes[starts + length]) + pad<61> - mod_mersenne_61(mult(std::get<Is>(hashes[starts]), pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(length))))), ...));
    return res;
  }

  template <std::uint32_t... Bases>
  [[nodiscard]] constexpr decltype(std::tuple {(static_cast<u64>(Bases))...}) substr_hash(const std::vector<decltype(std::tuple {(static_cast<u64>(Bases))...})>& hashes, const int starts, const int length) {
    return substr_hash_impl<Bases...>(hashes, starts, length, std::make_index_sequence<sizeof...(Bases)> {});
  }

}  // namespace internal::rolling_hash_hpp

#if (CP_LIBRARY_DEBUG_LEVEL >= 2)
template <typename Elem, std::uint32_t... Bases>
class rolling_hash {
private:
  static constexpr std::tuple bases_tuple {Bases...};
  std::vector<Elem> src;
  std::vector<decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})> hashes;

  struct single_hash {
  private:
    std::vector<Elem> src;
    decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...}) val;
    int length;

    template <std::size_t... Is>
    [[nodiscard]] auto concat_impl(const single_hash& rhs, std::index_sequence<Is...>) const {
      single_hash res;
      res.src = src;
      res.src.insert(std::end(res.src), std::cbegin(rhs.src), std::cend(rhs.src));
      res.length = length + rhs.length;
      static_cast<void>(((std::get<Is>(res.val) = internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mult(std::get<Is>(val), internal::rolling_hash_hpp::pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(rhs.length))) + std::get<Is>(rhs.val))), ...));
      return res;
    }

    template <std::size_t... Is>
    void concat_self_impl(const single_hash& rhs, std::index_sequence<Is...>) {
      src.insert(std::end(src), std::cbegin(rhs.src), std::cend(rhs.src));
      length += rhs.length;
      static_cast<void>(((std::get<Is>(val) = internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mult(std::get<Is>(val), internal::rolling_hash_hpp::pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(rhs.length))) + std::get<Is>(rhs.val))), ...));
    }

  public:
    //! @brief Construct empty single_hash object.
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    constexpr single_hash() noexcept
        : val(), length() {}

    //! @brief Construct singli_hash object from hash value and size.
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    single_hash(const std::vector<Elem>& source, const decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})& hash, const int size)
        : src(source), val(hash), length(size) {}

    //! @brief Construct singli_hash object from hash value and size.
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    single_hash(std::vector<Elem>&& source, decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})&& hash, const int size)
        : src(std::move(source)), val(std::move(hash)), length(size) {}

    //! @return The length of the sequence
    //! @note Time complexity: O(1)
    [[nodiscard]] int size() const noexcept {
      return length;
    }

    //! @return Whether both sides are the same sequence
    //! @param rhs another sequence
    //! @note Time complexity: O(size) since you are in debugging mode
    [[nodiscard]] bool operator==(const single_hash& rhs) const {
      const bool res         = (val == rhs.val);
      const bool precise_res = (src == rhs.src);
      if (__builtin_expect(res != precise_res, 0)) {
        CP_LIBRARY_ERROR(
          const std::ios_base::fmtflags prev_state = std::cerr.flags();
          std::cerr << "*** Hash collision detected ***\n"
                    << "Hash value: (" << std::hex;
          internal::rolling_hash_hpp::print_tuple(val, std::cerr, std::make_index_sequence<std::tuple_size_v<decltype(val)>> {});
          std::cerr << ")\n\n";
          std::cerr.flags(prev_state);
          if constexpr (std::is_same_v<char, Elem>) {
            std::cerr << "String 1: \"";
            std::for_each(std::cbegin(src), std::cend(src), [](const char c) { std::cerr << c; });
            std::cerr << "\"\n";
            std::cerr << "String 2: \"";
            std::for_each(std::cbegin(rhs.src), std::cend(rhs.src), [](const char c) { std::cerr << c; });
            std::cerr << "\"\n\n";
          } else {
            std::cerr << "Sequence 1: [ ";
            std::for_each(std::cbegin(src), std::cend(src), [](const Elem& e) { std::cerr << e << ' '; });
            std::cerr << "]\n";
            std::cerr << "Sequence 2: [ ";
            std::for_each(std::cbegin(rhs.src), std::cend(rhs.src), [](const Elem& e) { std::cerr << e << ' '; });
            std::cerr << "]\n\n";
          });
      }
      return res;
    }

    //! @return Whether both sides are NOT the same sequence
    //! @param rhs another sequence
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    [[nodiscard]] bool operator!=(const single_hash& rhs) const {
      return !(*this == rhs);
    }

    //! @brief Concatenate two sequences.
    //! @param rhs another sequence
    //! @return Concatenated sequence
    //! @note Time complexity: O(length of the resulting sequence) since you are in debugging mode
    [[nodiscard]] single_hash operator+(const single_hash& rhs) const {
      return concat_impl(rhs, std::make_index_sequence<std::tuple_size_v<decltype(bases_tuple)>> {});
    }

    //! @brief Append a sequence at the end.
    //! @param rhs another sequence
    //! @note Time complexity: O(length of rhs) since you are in debugging mode
    single_hash& operator+=(const single_hash& rhs) {
      concat_self_impl(rhs, std::make_index_sequence<std::tuple_size_v<decltype(bases_tuple)>> {});
      return *this;
    }

    //! @return Hash value
    //! @note The return value is not just an integer, but a tuple that contains multiple integers.
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    [[nodiscard]] auto hash_value() const noexcept {
      return val;
    }

    //! @brief Print information for debugging if CP_LIBRARY_DEBUG_LEVEL >= 1 (which is satisfied)
    void debug_print(const std::string& name = "", std::ostream& os = std::cerr) const {
      if (!name.empty())
        os << name << ": ";

      if constexpr (std::is_same_v<char, Elem>) {
        os << "    String = \"";
        std::for_each(std::cbegin(src), std::cend(src), [&](const char c) { os << c; });
        os << "\"\n";
      } else {
        os << "  Sequence = [ ";
        std::for_each(std::cbegin(src), std::cend(src), [&](const Elem& e) { os << e << ' '; });
        os << "]\n";
      }

      const std::ios_base::fmtflags prev_state = os.flags();
      os << (name.empty() ? std::string() : std::string(std::size(name) + 2, ' '))
         << "Hash value = " << std::hex << '(';
      internal::rolling_hash_hpp::print_tuple(val, os, std::make_index_sequence<std::tuple_size_v<decltype(val)>> {});
      os << ")\n\n";
      os.flags(prev_state);
    }
  };

public:
  //! @brief Construct a rolling_hash object from source container.
  //! @note Time complexity: O(length)
  template <typename Container>
  rolling_hash(const Container& source)
      : src(std::cbegin(source), std::cend(source)), hashes(internal::rolling_hash_hpp::build_hash_sequence<Bases...>(src)) {}

  //! @return The length of the sequence
  [[nodiscard]] int size() const noexcept(noexcept(std::size(src))) {
    return static_cast<int>(std::size(src));
  }

  //! @return An object that represents the hash value of the entire sequence
  //! @note Time complexity: O(length) since you are in debugging mode
  [[nodiscard]] single_hash whole_string() const {
    return single_hash(src, hashes.back(), size());
  }

  //! @param starts The index where the substring starts (0-indexed)
  //! @param length The length of the substring
  //! @return An object that represents the hash value of the substring
  //! @note Time complexity: O(length) since you are in debugging mode
  [[nodiscard]] single_hash substring(const int starts, int length = std::numeric_limits<int>::max()) const {
    length = std::min(static_cast<int>(std::size(src)) - starts, length);
    return single_hash(std::vector<Elem>(std::cbegin(src) + starts, std::cbegin(src) + starts + length), internal::rolling_hash_hpp::substr_hash<Bases...>(hashes, starts, length), length);
  }
};
#else
//! @brief Object that can quickly compute the hash value of a substring as well as the entire string.
//! @tparam Elem element type (e.g. char for std::string)
//! @tparam Bases base (radix) integers
template <typename Elem, std::uint32_t... Bases>
class rolling_hash {
private:
  static constexpr std::tuple bases_tuple {Bases...};
  std::vector<decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})> hashes;

  //! @brief Object that represents string hash.
  struct single_hash {
  private:
    decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...}) val;
    int length;

    template <std::size_t... Is>
    [[nodiscard]] auto concat_impl(const single_hash& rhs, std::index_sequence<Is...>) const {
      single_hash res;
      res.length = length + rhs.length;
      static_cast<void>(((std::get<Is>(res.val) = internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mult(std::get<Is>(val), internal::rolling_hash_hpp::pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(rhs.length))) + std::get<Is>(rhs.val))), ...));
      return res;
    }

    template <std::size_t... Is>
    void concat_self_impl(const single_hash& rhs, std::index_sequence<Is...>) {
      length += rhs.length;
      static_cast<void>(((std::get<Is>(val) = internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mult(std::get<Is>(val), internal::rolling_hash_hpp::pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(rhs.length))) + std::get<Is>(rhs.val))), ...));
    }

  public:
    //! @brief Construct empty single_hash object.
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    constexpr single_hash() noexcept
        : val(), length() {}

    //! @brief Construct singli_hash object from hash value and size.
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    single_hash(const decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})& hash, const int size)
        : val(hash), length(size) {}

    //! @brief Construct singli_hash object from hash value and size.
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    single_hash(decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})&& hash, const int size)
        : val(std::move(hash)), length(size) {}

    //! @return The length of the sequence
    //! @note Time complexity: O(1)
    [[nodiscard]] int size() const noexcept {
      return length;
    }

    //! @param rhs another sequence
    //! @return Whether both sides are the same sequence
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    [[nodiscard]] bool operator==(const single_hash& rhs) const noexcept {
      return (length == rhs.length) && (val == rhs.val);
    }

    //! @param rhs another sequence
    //! @return Whether both sides are NOT the same sequence
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    [[nodiscard]] bool operator!=(const single_hash& rhs) const noexcept {
      return !(*this == rhs);
    }

    //! @brief Concatenate two sequences.
    //! @param rhs another sequence
    //! @return Concatenated sequence
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    [[nodiscard]] single_hash operator+(const single_hash& rhs) const {
      return concat_impl(rhs, std::make_index_sequence<std::tuple_size_v<decltype(bases_tuple)>> {});
    }

    //! @brief Append a sequence at the end.
    //! @param rhs another sequence
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    single_hash& operator+=(const single_hash& rhs) {
      concat_self_impl(rhs, std::make_index_sequence<std::tuple_size_v<decltype(bases_tuple)>> {});
      return *this;
    }

    //! @return Hash value
    //! @note The return value is not just an integer, but a tuple that contains multiple integers.
    //! @note Time complexity: O(number of bases), which can be regarded as constant time
    [[nodiscard]] auto hash_value() const noexcept {
      return val;
    }

    //! @brief Print information for debugging if CP_LIBRARY_DEBUG_LEVEL >= 1
    void debug_print([[maybe_unused]] const std::string& name = "", [[maybe_unused]] std::ostream& os = std::cerr) const {
#  if (CP_LIBRARY_DEBUG_LEVEL >= 1)
      if (!name.empty())
        os << name << ": ";

      const std::ios_base::fmtflags prev_state = os.flags();
      os << "Hash value = " << std::hex << '(';
      internal::rolling_hash_hpp::print_tuple(val, os, std::make_index_sequence<std::tuple_size_v<decltype(val)>> {});
      os << ")\n";
      os.flags(prev_state);
#  endif
    }
  };

public:
  //! @brief Construct a rolling_hash object from source container.
  //! @note Time complexity: O(length)
  template <typename Container>
  rolling_hash(const Container& source)
      : hashes(internal::rolling_hash_hpp::build_hash_sequence<Bases...>(source)) {}

  //! @return The length of the sequence
  [[nodiscard]] int size() const noexcept(noexcept(std::size(hashes))) {
    return static_cast<int>(std::size(hashes)) - 1;
  }

  //! @return An object that represents the hash value of the entire sequence
  //! @note Time complexity: O(number of bases), which can be regarded as constant time
  [[nodiscard]] single_hash whole_string() const {
    return single_hash(hashes.back(), size());
  }

  //! @param starts The index where the substring starts (0-indexed)
  //! @param length The length of the substring
  //! @return An object that represents the hash value of the substring
  //! @note Time complexity: O(number of bases), which can be regarded as constant time
  [[nodiscard]] single_hash substring(const int starts, int length = std::numeric_limits<int>::max()) const {
    length = std::min(static_cast<int>(std::size(hashes)) - starts - 1, length);
    return single_hash(internal::rolling_hash_hpp::substr_hash<Bases...>(hashes, starts, length), length);
  }
};
#endif

//! @brief Returns an object that can quickly compute the hash value of a substring as well as the entire string.
//! @tparam Container source container type (deduced from parameter)
//! @param src source (std::string, std::vector, std::array, ...)
//! @return An object of type rolling_hash_t<Container>.
//! @note Time complexity: O(size(src))
template <typename Container>
[[nodiscard]] auto get_rolling_hash(const Container& src) {
  return rolling_hash<std::decay_t<decltype(*std::cbegin(std::declval<Container>()))>, 436523069, 681531337, 843203861>(src);
}

//! @brief Returns an object that represents the hash value of the entire string.
//! @tparam Container source container type (deduced from parameter)
//! @param src source (std::string, std::vector, std::array, ...)
//! @return An object of type single_hash_t<Container>.
//! @note Time complexity: O(size(src))
template <typename Container>
[[nodiscard]] auto get_single_hash(const Container& src) {
  return get_rolling_hash(src).whole_string();
}

//! @brief return type of get_rolling_hash function
template <typename Container>
using rolling_hash_t = decltype(get_rolling_hash(std::declval<Container>()));

//! @brief return type of get_single_hash function
template <typename Container>
using single_hash_t = decltype(get_single_hash(std::declval<Container>()));

}  // namespace lib

#ifdef CP_LIBRARY_ERROR_NOT_DEFINED
#  undef CP_LIBRARY_ERROR
#  undef CP_LIBRARY_ERROR_NOT_DEFINED
#endif

#ifdef CP_LIBRARY_ASSERT_NOT_DEFINED
#  undef CP_LIBRARY_ASSERT
#  undef CP_LIBRARY_ASSERT_NOT_DEFINED
#endif

#ifdef CP_LIBRARY_ROLLING_HASH_MAX_LENGTH_NOT_DEFINED
#  undef CP_LIBRARY_ROLLING_HASH_MAX_LENGTH
#  undef CP_LIBRARY_ROLLING_HASH_MAX_LENGTH_NOT_DEFINED
#endif

#endif  // CP_LIBRARY_ROLLING_HASH_HPP
