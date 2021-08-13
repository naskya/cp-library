---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/string/rolling_hash/1.test.cpp
    title: test/string/rolling_hash/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/string/rolling_hash/2.test.cpp
    title: test/string/rolling_hash/2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/string/rolling_hash/3.test.cpp
    title: test/string/rolling_hash/3.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Assert macro
    links:
    - https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
    - https://wandbox.org/permlink/26ZTzuIfTivSz2lR
    - https://wandbox.org/permlink/xpqiYobUkI1EGpgo
  bundledCode: "#line 1 \"include/string/rolling_hash.hpp\"\n\n//! @file rolling_hash.hpp\n\
    //! @note The implementation is based on this article https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\
    \n#ifndef CP_LIBRARY_ROLLING_HASH_HPP\n#define CP_LIBRARY_ROLLING_HASH_HPP\n\n\
    #ifndef CP_LIBRARY_ROLLING_HASH_MAX_LENGTH\n#  warning Please define CP_LIBRARY_ROLLING_HASH_MAX_LENGTH\
    \ (default: 200000).\n#  define CP_LIBRARY_ROLLING_HASH_MAX_LENGTH 200000\n# \
    \ define CP_LIBRARY_ROLLING_HASH_MAX_LENGTH_NOT_DEFINED\n#endif\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n\
    #include <limits>\n#include <string>\n#include <tuple>\n#include <vector>\n\n\
    #ifndef CP_LIBRARY_ASSERT\n//! @brief Assert macro\n#  define CP_LIBRARY_ASSERT(...)\
    \ assert(__VA_ARGS__)\n#  define CP_LIBRARY_ASSERT_NOT_DEFINED\n#endif\n\n#ifndef\
    \ CP_LIBRARY_ERROR\n#  if (CP_LIBRARY_DEBUG_LEVEL >= 2)\n//! @brief Print error\
    \ message and exit\n#    define CP_LIBRARY_ERROR(...) \\\n      do {         \
    \               \\\n        __VA_ARGS__               \\\n        CP_LIBRARY_ASSERT(false);\
    \ \\\n      } while (false)\n#  else\n#    define CP_LIBRARY_ERROR(...) (static_cast<void>(0))\n\
    #  endif\n#  define CP_LIBRARY_ERROR_NOT_DEFINED\n#endif\n\nnamespace lib {\n\n\
    namespace internal::rolling_hash_hpp {\n  using u64 = std::uint_least64_t;\n\n\
    \  template <unsigned index>\n  constexpr u64 mask = (u64(1) << index) - 1;\n\n\
    \  template <unsigned index>\n  constexpr u64 pad = mask<index>* mask<std::numeric_limits<u64>::digits\
    \ - index>;\n\n  [[gnu::const]] [[nodiscard]] constexpr u64 mod_mersenne_61(const\
    \ u64 x) noexcept {\n    if (const u64 res = (x >> 61) + (x & mask<61>); res >=\
    \ mask<61>)\n      return res - mask<61>;\n    else\n      return res;\n  }\n\n\
    \  [[gnu::const]] [[nodiscard]] constexpr u64 mult(const u64 x, const u64 y) noexcept\
    \ {\n    const u64 x_upper = (x >> 31);\n    const u64 x_lower = (x & mask<31>);\n\
    \    const u64 y_upper = (y >> 31);\n    const u64 y_lower = (y & mask<31>);\n\
    \    const u64 z       = x_upper * y_lower + x_lower * y_upper;\n    return ((x_upper\
    \ * y_upper) << 1) + (z >> 30) + ((z & mask<30>) << 31) + (x_lower * y_lower);\n\
    \  }\n\n  template <u64 base>\n  [[nodiscard]] u64 pow_mod_mersenne_61(unsigned\
    \ index) {\n    static bool first = true;\n    static std::array<u64, CP_LIBRARY_ROLLING_HASH_MAX_LENGTH\
    \ + 1> res;\n\n    if (__builtin_expect(first, 0)) {\n      first  = false;\n\
    \      res[0] = 1;\n      for (unsigned i = 1; i <= CP_LIBRARY_ROLLING_HASH_MAX_LENGTH;\
    \ ++i)\n        res[i] = mod_mersenne_61(mult(res[i - 1], base));\n    }\n\n \
    \   return res[index];\n  }\n\n  template <class TupleType, std::size_t... Is>\n\
    \  void print_tuple(const TupleType& arg, std::ostream& os, std::index_sequence<Is...>)\
    \ {\n    static_cast<void>(((os << (Is == 0 ? \"\" : \", \"), (os << std::get<Is>(arg))),\
    \ ...));\n  }\n\n  // Using the following type alias unables GCC to compile the\
    \ code. (no problem with Clang/MSVC. maybe a bug.)\n  // template <std::uint32_t...\
    \ Bases>\n  // using hash_t = decltype(std::tuple {(static_cast<u64>(Bases))...});\n\
    \  // See:  https://wandbox.org/permlink/xpqiYobUkI1EGpgo (on GCC 12.0.0)\n  //\
    \       https://wandbox.org/permlink/26ZTzuIfTivSz2lR (on Clang 13.0.0)\n  //\
    \ ToDo: Replace decltype(std::tuple {(static_cast<u64>(Bases))...}) with hash_t<Bases...>\n\
    \  //       and replace decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})\
    \ with internal::rolling_hash_hpp::hash_t<Bases...>\n  //       when we figure\
    \ out the workaround or this bug(?) is fixed.\n\n  template <std::uint32_t...\
    \ Bases, typename Container, std::size_t... Is>\n  void build_hash_sequence_impl(const\
    \ Container& src,\n                                std::vector<decltype(std::tuple\
    \ {(static_cast<u64>(Bases))...})>& dest,\n                                std::index_sequence<Is...>)\
    \ {\n    constexpr std::tuple bases_tuple = std::tuple {Bases...};\n    const\
    \ std::size_t size           = std::size(src);\n    auto iter                \
    \        = std::cbegin(src);\n\n    for (std::size_t i = 0; i < size; ++iter,\
    \ ++i)\n      static_cast<void>(((std::get<Is>(dest[i + 1]) = mod_mersenne_61(mult(std::get<Is>(dest[i]),\
    \ std::get<Is>(bases_tuple)) + static_cast<u64>(*iter))), ...));\n  }\n\n  template\
    \ <std::uint32_t... Bases, typename Container>\n  [[nodiscard]] std::vector<decltype(std::tuple\
    \ {(static_cast<u64>(Bases))...})> build_hash_sequence(const Container& src) {\n\
    \    std::vector<decltype(std::tuple {(static_cast<u64>(Bases))...})> res(std::size(src)\
    \ + 1);\n    build_hash_sequence_impl<Bases...>(src, res, std::make_index_sequence<sizeof...(Bases)>\
    \ {});\n    return res;\n  }\n\n  template <std::uint32_t... Bases, std::size_t...\
    \ Is>\n  [[nodiscard]] constexpr decltype(std::tuple {(static_cast<u64>(Bases))...})\
    \ substr_hash_impl(const std::vector<decltype(std::tuple {(static_cast<u64>(Bases))...})>&\
    \ hashes, const int starts, const int length, std::index_sequence<Is...>) {\n\
    \    constexpr std::tuple bases_tuple = std::tuple {Bases...};\n    decltype(std::tuple\
    \ {(static_cast<u64>(Bases))...}) res;\n    static_cast<void>(((std::get<Is>(res)\
    \ = mod_mersenne_61(std::get<Is>(hashes[starts + length]) + pad<61> - mod_mersenne_61(mult(std::get<Is>(hashes[starts]),\
    \ pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(length))))), ...));\n    return\
    \ res;\n  }\n\n  template <std::uint32_t... Bases>\n  [[nodiscard]] constexpr\
    \ decltype(std::tuple {(static_cast<u64>(Bases))...}) substr_hash(const std::vector<decltype(std::tuple\
    \ {(static_cast<u64>(Bases))...})>& hashes, const int starts, const int length)\
    \ {\n    return substr_hash_impl<Bases...>(hashes, starts, length, std::make_index_sequence<sizeof...(Bases)>\
    \ {});\n  }\n\n}  // namespace internal::rolling_hash_hpp\n\n#if (CP_LIBRARY_DEBUG_LEVEL\
    \ >= 2)\ntemplate <typename Elem, std::uint32_t... Bases>\nclass rolling_hash\
    \ {\nprivate:\n  static constexpr std::tuple bases_tuple {Bases...};\n  std::vector<Elem>\
    \ src;\n  std::vector<decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})>\
    \ hashes;\n\n  struct single_hash {\n  private:\n    std::vector<Elem> src;\n\
    \    decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})\
    \ val;\n    int length;\n\n    template <std::size_t... Is>\n    [[nodiscard]]\
    \ auto concat_impl(const single_hash& rhs, std::index_sequence<Is...>) const {\n\
    \      single_hash res;\n      res.src = src;\n      res.src.insert(std::end(res.src),\
    \ std::cbegin(rhs.src), std::cend(rhs.src));\n      res.length = length + rhs.length;\n\
    \      static_cast<void>(((std::get<Is>(res.val) = internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mult(std::get<Is>(val),\
    \ internal::rolling_hash_hpp::pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(rhs.length)))\
    \ + std::get<Is>(rhs.val))), ...));\n      return res;\n    }\n\n    template\
    \ <std::size_t... Is>\n    void concat_self_impl(const single_hash& rhs, std::index_sequence<Is...>)\
    \ {\n      src.insert(std::end(src), std::cbegin(rhs.src), std::cend(rhs.src));\n\
    \      length += rhs.length;\n      static_cast<void>(((std::get<Is>(val) = internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mult(std::get<Is>(val),\
    \ internal::rolling_hash_hpp::pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(rhs.length)))\
    \ + std::get<Is>(rhs.val))), ...));\n    }\n\n  public:\n    //! @brief Construct\
    \ empty single_hash object.\n    //! @note Time complexity: O(number of bases),\
    \ which can be regarded as constant time\n    constexpr single_hash() noexcept\n\
    \        : val(), length() {}\n\n    //! @brief Construct singli_hash object from\
    \ hash value and size.\n    //! @note Time complexity: O(number of bases), which\
    \ can be regarded as constant time\n    single_hash(const std::vector<Elem>& source,\
    \ const decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})&\
    \ hash, const int size)\n        : src(source), val(hash), length(size) {}\n\n\
    \    //! @brief Construct singli_hash object from hash value and size.\n    //!\
    \ @note Time complexity: O(number of bases), which can be regarded as constant\
    \ time\n    single_hash(std::vector<Elem>&& source, decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})&&\
    \ hash, const int size)\n        : src(std::move(source)), val(std::move(hash)),\
    \ length(size) {}\n\n    //! @return The length of the sequence\n    //! @note\
    \ Time complexity: O(1)\n    [[nodiscard]] int size() const noexcept {\n     \
    \ return length;\n    }\n\n    //! @return Whether both sides are the same sequence\n\
    \    //! @param rhs another sequence\n    //! @note Time complexity: O(size) since\
    \ you are in debugging mode\n    [[nodiscard]] bool operator==(const single_hash&\
    \ rhs) const {\n      const bool res         = (val == rhs.val);\n      const\
    \ bool precise_res = (src == rhs.src);\n      if (__builtin_expect(res != precise_res,\
    \ 0)) {\n        CP_LIBRARY_ERROR(\n          const std::ios_base::fmtflags prev_state\
    \ = std::cerr.flags();\n          std::cerr << \"*** Hash collision detected ***\\\
    n\"\n                    << \"Hash value: (\" << std::hex;\n          internal::rolling_hash_hpp::print_tuple(val,\
    \ std::cerr, std::make_index_sequence<std::tuple_size_v<decltype(val)>> {});\n\
    \          std::cerr << \")\\n\\n\";\n          std::cerr.flags(prev_state);\n\
    \          if constexpr (std::is_same_v<char, Elem>) {\n            std::cerr\
    \ << \"String 1: \\\"\";\n            std::for_each(std::cbegin(src), std::cend(src),\
    \ [](const char c) { std::cerr << c; });\n            std::cerr << \"\\\"\\n\"\
    ;\n            std::cerr << \"String 2: \\\"\";\n            std::for_each(std::cbegin(rhs.src),\
    \ std::cend(rhs.src), [](const char c) { std::cerr << c; });\n            std::cerr\
    \ << \"\\\"\\n\\n\";\n          } else {\n            std::cerr << \"Sequence\
    \ 1: [ \";\n            std::for_each(std::cbegin(src), std::cend(src), [](const\
    \ Elem& e) { std::cerr << e << ' '; });\n            std::cerr << \"]\\n\";\n\
    \            std::cerr << \"Sequence 2: [ \";\n            std::for_each(std::cbegin(rhs.src),\
    \ std::cend(rhs.src), [](const Elem& e) { std::cerr << e << ' '; });\n       \
    \     std::cerr << \"]\\n\\n\";\n          });\n      }\n      return res;\n \
    \   }\n\n    //! @return Whether both sides are NOT the same sequence\n    //!\
    \ @param rhs another sequence\n    //! @note Time complexity: O(number of bases),\
    \ which can be regarded as constant time\n    [[nodiscard]] bool operator!=(const\
    \ single_hash& rhs) const {\n      return !(*this == rhs);\n    }\n\n    //! @brief\
    \ Concatenate two sequences.\n    //! @param rhs another sequence\n    //! @return\
    \ Concatenated sequence\n    //! @note Time complexity: O(length of the resulting\
    \ sequence) since you are in debugging mode\n    [[nodiscard]] single_hash operator+(const\
    \ single_hash& rhs) const {\n      return concat_impl(rhs, std::make_index_sequence<std::tuple_size_v<decltype(bases_tuple)>>\
    \ {});\n    }\n\n    //! @brief Append a sequence at the end.\n    //! @param\
    \ rhs another sequence\n    //! @note Time complexity: O(length of rhs) since\
    \ you are in debugging mode\n    single_hash& operator+=(const single_hash& rhs)\
    \ {\n      concat_self_impl(rhs, std::make_index_sequence<std::tuple_size_v<decltype(bases_tuple)>>\
    \ {});\n      return *this;\n    }\n\n    //! @return Hash value\n    //! @note\
    \ The return value is not just an integer, but a tuple that contains multiple\
    \ integers.\n    //! @note Time complexity: O(number of bases), which can be regarded\
    \ as constant time\n    [[nodiscard]] auto hash_value() const noexcept {\n   \
    \   return val;\n    }\n\n    //! @brief Print information for debugging if CP_LIBRARY_DEBUG_LEVEL\
    \ >= 1 (which is satisfied)\n    void debug_print(const std::string& name = \"\
    \", std::ostream& os = std::cerr) const {\n      if (!name.empty())\n        os\
    \ << name << \": \";\n\n      if constexpr (std::is_same_v<char, Elem>) {\n  \
    \      os << \"    String = \\\"\";\n        std::for_each(std::cbegin(src), std::cend(src),\
    \ [&](const char c) { os << c; });\n        os << \"\\\"\\n\";\n      } else {\n\
    \        os << \"  Sequence = [ \";\n        std::for_each(std::cbegin(src), std::cend(src),\
    \ [&](const Elem& e) { os << e << ' '; });\n        os << \"]\\n\";\n      }\n\
    \n      const std::ios_base::fmtflags prev_state = os.flags();\n      os << (name.empty()\
    \ ? std::string() : std::string(std::size(name) + 2, ' '))\n         << \"Hash\
    \ value = \" << std::hex << '(';\n      internal::rolling_hash_hpp::print_tuple(val,\
    \ os, std::make_index_sequence<std::tuple_size_v<decltype(val)>> {});\n      os\
    \ << \")\\n\\n\";\n      os.flags(prev_state);\n    }\n  };\n\npublic:\n  //!\
    \ @brief Construct a rolling_hash object from source container.\n  //! @note Time\
    \ complexity: O(length)\n  template <typename Container>\n  rolling_hash(const\
    \ Container& source)\n      : src(std::cbegin(source), std::cend(source)), hashes(internal::rolling_hash_hpp::build_hash_sequence<Bases...>(src))\
    \ {}\n\n  //! @return The length of the sequence\n  [[nodiscard]] int size() const\
    \ noexcept(noexcept(std::size(src))) {\n    return static_cast<int>(std::size(src));\n\
    \  }\n\n  //! @return An object that represents the hash value of the entire sequence\n\
    \  //! @note Time complexity: O(length) since you are in debugging mode\n  [[nodiscard]]\
    \ single_hash whole_string() const {\n    return single_hash(src, hashes.back(),\
    \ size());\n  }\n\n  //! @param starts The index where the substring starts (0-indexed)\n\
    \  //! @param length The length of the substring\n  //! @return An object that\
    \ represents the hash value of the substring\n  //! @note Time complexity: O(length)\
    \ since you are in debugging mode\n  [[nodiscard]] single_hash substring(const\
    \ int starts, int length = std::numeric_limits<int>::max()) const {\n    length\
    \ = std::min(static_cast<int>(std::size(src)) - starts, length);\n    return single_hash(std::vector<Elem>(std::cbegin(src)\
    \ + starts, std::cbegin(src) + starts + length), internal::rolling_hash_hpp::substr_hash<Bases...>(hashes,\
    \ starts, length), length);\n  }\n};\n#else\n//! @brief Object that can quickly\
    \ compute the hash value of a substring as well as the entire string.\n//! @tparam\
    \ Elem element type (e.g. char for std::string)\n//! @tparam Bases base (radix)\
    \ integers\ntemplate <typename Elem, std::uint32_t... Bases>\nclass rolling_hash\
    \ {\nprivate:\n  static constexpr std::tuple bases_tuple {Bases...};\n  std::vector<decltype(std::tuple\
    \ {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})> hashes;\n\n  //!\
    \ @brief Object that represents string hash.\n  struct single_hash {\n  private:\n\
    \    decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})\
    \ val;\n    int length;\n\n    template <std::size_t... Is>\n    [[nodiscard]]\
    \ auto concat_impl(const single_hash& rhs, std::index_sequence<Is...>) const {\n\
    \      single_hash res;\n      res.length = length + rhs.length;\n      static_cast<void>(((std::get<Is>(res.val)\
    \ = internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mult(std::get<Is>(val),\
    \ internal::rolling_hash_hpp::pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(rhs.length)))\
    \ + std::get<Is>(rhs.val))), ...));\n      return res;\n    }\n\n    template\
    \ <std::size_t... Is>\n    void concat_self_impl(const single_hash& rhs, std::index_sequence<Is...>)\
    \ {\n      length += rhs.length;\n      static_cast<void>(((std::get<Is>(val)\
    \ = internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mult(std::get<Is>(val),\
    \ internal::rolling_hash_hpp::pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(rhs.length)))\
    \ + std::get<Is>(rhs.val))), ...));\n    }\n\n  public:\n    //! @brief Construct\
    \ empty single_hash object.\n    //! @note Time complexity: O(number of bases),\
    \ which can be regarded as constant time\n    constexpr single_hash() noexcept\n\
    \        : val(), length() {}\n\n    //! @brief Construct singli_hash object from\
    \ hash value and size.\n    //! @note Time complexity: O(number of bases), which\
    \ can be regarded as constant time\n    single_hash(const decltype(std::tuple\
    \ {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})& hash, const int\
    \ size)\n        : val(hash), length(size) {}\n\n    //! @brief Construct singli_hash\
    \ object from hash value and size.\n    //! @note Time complexity: O(number of\
    \ bases), which can be regarded as constant time\n    single_hash(decltype(std::tuple\
    \ {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})&& hash, const int\
    \ size)\n        : val(std::move(hash)), length(size) {}\n\n    //! @return The\
    \ length of the sequence\n    //! @note Time complexity: O(1)\n    [[nodiscard]]\
    \ int size() const noexcept {\n      return length;\n    }\n\n    //! @param rhs\
    \ another sequence\n    //! @return Whether both sides are the same sequence\n\
    \    //! @note Time complexity: O(number of bases), which can be regarded as constant\
    \ time\n    [[nodiscard]] bool operator==(const single_hash& rhs) const noexcept\
    \ {\n      return (length == rhs.length) && (val == rhs.val);\n    }\n\n    //!\
    \ @param rhs another sequence\n    //! @return Whether both sides are NOT the\
    \ same sequence\n    //! @note Time complexity: O(number of bases), which can\
    \ be regarded as constant time\n    [[nodiscard]] bool operator!=(const single_hash&\
    \ rhs) const noexcept {\n      return !(*this == rhs);\n    }\n\n    //! @brief\
    \ Concatenate two sequences.\n    //! @param rhs another sequence\n    //! @return\
    \ Concatenated sequence\n    //! @note Time complexity: O(number of bases), which\
    \ can be regarded as constant time\n    [[nodiscard]] single_hash operator+(const\
    \ single_hash& rhs) const {\n      return concat_impl(rhs, std::make_index_sequence<std::tuple_size_v<decltype(bases_tuple)>>\
    \ {});\n    }\n\n    //! @brief Append a sequence at the end.\n    //! @param\
    \ rhs another sequence\n    //! @note Time complexity: O(number of bases), which\
    \ can be regarded as constant time\n    single_hash& operator+=(const single_hash&\
    \ rhs) {\n      concat_self_impl(rhs, std::make_index_sequence<std::tuple_size_v<decltype(bases_tuple)>>\
    \ {});\n      return *this;\n    }\n\n    //! @return Hash value\n    //! @note\
    \ The return value is not just an integer, but a tuple that contains multiple\
    \ integers.\n    //! @note Time complexity: O(number of bases), which can be regarded\
    \ as constant time\n    [[nodiscard]] auto hash_value() const noexcept {\n   \
    \   return val;\n    }\n\n    //! @brief Print information for debugging if CP_LIBRARY_DEBUG_LEVEL\
    \ >= 1\n    void debug_print([[maybe_unused]] const std::string& name = \"\",\
    \ [[maybe_unused]] std::ostream& os = std::cerr) const {\n#  if (CP_LIBRARY_DEBUG_LEVEL\
    \ >= 1)\n      if (!name.empty())\n        os << name << \": \";\n\n      const\
    \ std::ios_base::fmtflags prev_state = os.flags();\n      os << \"Hash value =\
    \ \" << std::hex << '(';\n      internal::rolling_hash_hpp::print_tuple(val, os,\
    \ std::make_index_sequence<std::tuple_size_v<decltype(val)>> {});\n      os <<\
    \ \")\\n\";\n      os.flags(prev_state);\n#  endif\n    }\n  };\n\npublic:\n \
    \ //! @brief Construct a rolling_hash object from source container.\n  //! @note\
    \ Time complexity: O(length)\n  template <typename Container>\n  rolling_hash(const\
    \ Container& source)\n      : hashes(internal::rolling_hash_hpp::build_hash_sequence<Bases...>(source))\
    \ {}\n\n  //! @return The length of the sequence\n  [[nodiscard]] int size() const\
    \ noexcept(noexcept(std::size(hashes))) {\n    return static_cast<int>(std::size(hashes))\
    \ - 1;\n  }\n\n  //! @return An object that represents the hash value of the entire\
    \ sequence\n  //! @note Time complexity: O(number of bases), which can be regarded\
    \ as constant time\n  [[nodiscard]] single_hash whole_string() const {\n    return\
    \ single_hash(hashes.back(), size());\n  }\n\n  //! @param starts The index where\
    \ the substring starts (0-indexed)\n  //! @param length The length of the substring\n\
    \  //! @return An object that represents the hash value of the substring\n  //!\
    \ @note Time complexity: O(number of bases), which can be regarded as constant\
    \ time\n  [[nodiscard]] single_hash substring(const int starts, int length = std::numeric_limits<int>::max())\
    \ const {\n    length = std::min(static_cast<int>(std::size(hashes)) - starts\
    \ - 1, length);\n    return single_hash(internal::rolling_hash_hpp::substr_hash<Bases...>(hashes,\
    \ starts, length), length);\n  }\n};\n#endif\n\n//! @brief Returns an object that\
    \ can quickly compute the hash value of a substring as well as the entire string.\n\
    //! @tparam Container source container type (deduced from parameter)\n//! @param\
    \ src source (std::string, std::vector, std::array, ...)\n//! @return An object\
    \ of type rolling_hash_t<Container>.\n//! @note Time complexity: O(size(src))\n\
    template <typename Container>\n[[nodiscard]] auto get_rolling_hash(const Container&\
    \ src) {\n  return rolling_hash<std::decay_t<decltype(*std::cbegin(std::declval<Container>()))>,\
    \ 436523069, 681531337, 843203861>(src);\n}\n\n//! @brief Returns an object that\
    \ represents the hash value of the entire string.\n//! @tparam Container source\
    \ container type (deduced from parameter)\n//! @param src source (std::string,\
    \ std::vector, std::array, ...)\n//! @return An object of type single_hash_t<Container>.\n\
    //! @note Time complexity: O(size(src))\ntemplate <typename Container>\n[[nodiscard]]\
    \ auto get_single_hash(const Container& src) {\n  return get_rolling_hash(src).whole_string();\n\
    }\n\n//! @brief return type of get_rolling_hash function\ntemplate <typename Container>\n\
    using rolling_hash_t = decltype(get_rolling_hash(std::declval<Container>()));\n\
    \n//! @brief return type of get_single_hash function\ntemplate <typename Container>\n\
    using single_hash_t = decltype(get_single_hash(std::declval<Container>()));\n\n\
    }  // namespace lib\n\n#ifdef CP_LIBRARY_ERROR_NOT_DEFINED\n#  undef CP_LIBRARY_ERROR\n\
    #  undef CP_LIBRARY_ERROR_NOT_DEFINED\n#endif\n\n#ifdef CP_LIBRARY_ASSERT_NOT_DEFINED\n\
    #  undef CP_LIBRARY_ASSERT\n#  undef CP_LIBRARY_ASSERT_NOT_DEFINED\n#endif\n\n\
    #ifdef CP_LIBRARY_ROLLING_HASH_MAX_LENGTH_NOT_DEFINED\n#  undef CP_LIBRARY_ROLLING_HASH_MAX_LENGTH\n\
    #  undef CP_LIBRARY_ROLLING_HASH_MAX_LENGTH_NOT_DEFINED\n#endif\n\n#endif  //\
    \ CP_LIBRARY_ROLLING_HASH_HPP\n"
  code: "\n//! @file rolling_hash.hpp\n//! @note The implementation is based on this\
    \ article https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\n#ifndef CP_LIBRARY_ROLLING_HASH_HPP\n\
    #define CP_LIBRARY_ROLLING_HASH_HPP\n\n#ifndef CP_LIBRARY_ROLLING_HASH_MAX_LENGTH\n\
    #  warning Please define CP_LIBRARY_ROLLING_HASH_MAX_LENGTH (default: 200000).\n\
    #  define CP_LIBRARY_ROLLING_HASH_MAX_LENGTH 200000\n#  define CP_LIBRARY_ROLLING_HASH_MAX_LENGTH_NOT_DEFINED\n\
    #endif\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include\
    \ <cstdint>\n#include <iostream>\n#include <limits>\n#include <string>\n#include\
    \ <tuple>\n#include <vector>\n\n#ifndef CP_LIBRARY_ASSERT\n//! @brief Assert macro\n\
    #  define CP_LIBRARY_ASSERT(...) assert(__VA_ARGS__)\n#  define CP_LIBRARY_ASSERT_NOT_DEFINED\n\
    #endif\n\n#ifndef CP_LIBRARY_ERROR\n#  if (CP_LIBRARY_DEBUG_LEVEL >= 2)\n//! @brief\
    \ Print error message and exit\n#    define CP_LIBRARY_ERROR(...) \\\n      do\
    \ {                        \\\n        __VA_ARGS__               \\\n        CP_LIBRARY_ASSERT(false);\
    \ \\\n      } while (false)\n#  else\n#    define CP_LIBRARY_ERROR(...) (static_cast<void>(0))\n\
    #  endif\n#  define CP_LIBRARY_ERROR_NOT_DEFINED\n#endif\n\nnamespace lib {\n\n\
    namespace internal::rolling_hash_hpp {\n  using u64 = std::uint_least64_t;\n\n\
    \  template <unsigned index>\n  constexpr u64 mask = (u64(1) << index) - 1;\n\n\
    \  template <unsigned index>\n  constexpr u64 pad = mask<index>* mask<std::numeric_limits<u64>::digits\
    \ - index>;\n\n  [[gnu::const]] [[nodiscard]] constexpr u64 mod_mersenne_61(const\
    \ u64 x) noexcept {\n    if (const u64 res = (x >> 61) + (x & mask<61>); res >=\
    \ mask<61>)\n      return res - mask<61>;\n    else\n      return res;\n  }\n\n\
    \  [[gnu::const]] [[nodiscard]] constexpr u64 mult(const u64 x, const u64 y) noexcept\
    \ {\n    const u64 x_upper = (x >> 31);\n    const u64 x_lower = (x & mask<31>);\n\
    \    const u64 y_upper = (y >> 31);\n    const u64 y_lower = (y & mask<31>);\n\
    \    const u64 z       = x_upper * y_lower + x_lower * y_upper;\n    return ((x_upper\
    \ * y_upper) << 1) + (z >> 30) + ((z & mask<30>) << 31) + (x_lower * y_lower);\n\
    \  }\n\n  template <u64 base>\n  [[nodiscard]] u64 pow_mod_mersenne_61(unsigned\
    \ index) {\n    static bool first = true;\n    static std::array<u64, CP_LIBRARY_ROLLING_HASH_MAX_LENGTH\
    \ + 1> res;\n\n    if (__builtin_expect(first, 0)) {\n      first  = false;\n\
    \      res[0] = 1;\n      for (unsigned i = 1; i <= CP_LIBRARY_ROLLING_HASH_MAX_LENGTH;\
    \ ++i)\n        res[i] = mod_mersenne_61(mult(res[i - 1], base));\n    }\n\n \
    \   return res[index];\n  }\n\n  template <class TupleType, std::size_t... Is>\n\
    \  void print_tuple(const TupleType& arg, std::ostream& os, std::index_sequence<Is...>)\
    \ {\n    static_cast<void>(((os << (Is == 0 ? \"\" : \", \"), (os << std::get<Is>(arg))),\
    \ ...));\n  }\n\n  // Using the following type alias unables GCC to compile the\
    \ code. (no problem with Clang/MSVC. maybe a bug.)\n  // template <std::uint32_t...\
    \ Bases>\n  // using hash_t = decltype(std::tuple {(static_cast<u64>(Bases))...});\n\
    \  // See:  https://wandbox.org/permlink/xpqiYobUkI1EGpgo (on GCC 12.0.0)\n  //\
    \       https://wandbox.org/permlink/26ZTzuIfTivSz2lR (on Clang 13.0.0)\n  //\
    \ ToDo: Replace decltype(std::tuple {(static_cast<u64>(Bases))...}) with hash_t<Bases...>\n\
    \  //       and replace decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})\
    \ with internal::rolling_hash_hpp::hash_t<Bases...>\n  //       when we figure\
    \ out the workaround or this bug(?) is fixed.\n\n  template <std::uint32_t...\
    \ Bases, typename Container, std::size_t... Is>\n  void build_hash_sequence_impl(const\
    \ Container& src,\n                                std::vector<decltype(std::tuple\
    \ {(static_cast<u64>(Bases))...})>& dest,\n                                std::index_sequence<Is...>)\
    \ {\n    constexpr std::tuple bases_tuple = std::tuple {Bases...};\n    const\
    \ std::size_t size           = std::size(src);\n    auto iter                \
    \        = std::cbegin(src);\n\n    for (std::size_t i = 0; i < size; ++iter,\
    \ ++i)\n      static_cast<void>(((std::get<Is>(dest[i + 1]) = mod_mersenne_61(mult(std::get<Is>(dest[i]),\
    \ std::get<Is>(bases_tuple)) + static_cast<u64>(*iter))), ...));\n  }\n\n  template\
    \ <std::uint32_t... Bases, typename Container>\n  [[nodiscard]] std::vector<decltype(std::tuple\
    \ {(static_cast<u64>(Bases))...})> build_hash_sequence(const Container& src) {\n\
    \    std::vector<decltype(std::tuple {(static_cast<u64>(Bases))...})> res(std::size(src)\
    \ + 1);\n    build_hash_sequence_impl<Bases...>(src, res, std::make_index_sequence<sizeof...(Bases)>\
    \ {});\n    return res;\n  }\n\n  template <std::uint32_t... Bases, std::size_t...\
    \ Is>\n  [[nodiscard]] constexpr decltype(std::tuple {(static_cast<u64>(Bases))...})\
    \ substr_hash_impl(const std::vector<decltype(std::tuple {(static_cast<u64>(Bases))...})>&\
    \ hashes, const int starts, const int length, std::index_sequence<Is...>) {\n\
    \    constexpr std::tuple bases_tuple = std::tuple {Bases...};\n    decltype(std::tuple\
    \ {(static_cast<u64>(Bases))...}) res;\n    static_cast<void>(((std::get<Is>(res)\
    \ = mod_mersenne_61(std::get<Is>(hashes[starts + length]) + pad<61> - mod_mersenne_61(mult(std::get<Is>(hashes[starts]),\
    \ pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(length))))), ...));\n    return\
    \ res;\n  }\n\n  template <std::uint32_t... Bases>\n  [[nodiscard]] constexpr\
    \ decltype(std::tuple {(static_cast<u64>(Bases))...}) substr_hash(const std::vector<decltype(std::tuple\
    \ {(static_cast<u64>(Bases))...})>& hashes, const int starts, const int length)\
    \ {\n    return substr_hash_impl<Bases...>(hashes, starts, length, std::make_index_sequence<sizeof...(Bases)>\
    \ {});\n  }\n\n}  // namespace internal::rolling_hash_hpp\n\n#if (CP_LIBRARY_DEBUG_LEVEL\
    \ >= 2)\ntemplate <typename Elem, std::uint32_t... Bases>\nclass rolling_hash\
    \ {\nprivate:\n  static constexpr std::tuple bases_tuple {Bases...};\n  std::vector<Elem>\
    \ src;\n  std::vector<decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})>\
    \ hashes;\n\n  struct single_hash {\n  private:\n    std::vector<Elem> src;\n\
    \    decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})\
    \ val;\n    int length;\n\n    template <std::size_t... Is>\n    [[nodiscard]]\
    \ auto concat_impl(const single_hash& rhs, std::index_sequence<Is...>) const {\n\
    \      single_hash res;\n      res.src = src;\n      res.src.insert(std::end(res.src),\
    \ std::cbegin(rhs.src), std::cend(rhs.src));\n      res.length = length + rhs.length;\n\
    \      static_cast<void>(((std::get<Is>(res.val) = internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mult(std::get<Is>(val),\
    \ internal::rolling_hash_hpp::pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(rhs.length)))\
    \ + std::get<Is>(rhs.val))), ...));\n      return res;\n    }\n\n    template\
    \ <std::size_t... Is>\n    void concat_self_impl(const single_hash& rhs, std::index_sequence<Is...>)\
    \ {\n      src.insert(std::end(src), std::cbegin(rhs.src), std::cend(rhs.src));\n\
    \      length += rhs.length;\n      static_cast<void>(((std::get<Is>(val) = internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mult(std::get<Is>(val),\
    \ internal::rolling_hash_hpp::pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(rhs.length)))\
    \ + std::get<Is>(rhs.val))), ...));\n    }\n\n  public:\n    //! @brief Construct\
    \ empty single_hash object.\n    //! @note Time complexity: O(number of bases),\
    \ which can be regarded as constant time\n    constexpr single_hash() noexcept\n\
    \        : val(), length() {}\n\n    //! @brief Construct singli_hash object from\
    \ hash value and size.\n    //! @note Time complexity: O(number of bases), which\
    \ can be regarded as constant time\n    single_hash(const std::vector<Elem>& source,\
    \ const decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})&\
    \ hash, const int size)\n        : src(source), val(hash), length(size) {}\n\n\
    \    //! @brief Construct singli_hash object from hash value and size.\n    //!\
    \ @note Time complexity: O(number of bases), which can be regarded as constant\
    \ time\n    single_hash(std::vector<Elem>&& source, decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})&&\
    \ hash, const int size)\n        : src(std::move(source)), val(std::move(hash)),\
    \ length(size) {}\n\n    //! @return The length of the sequence\n    //! @note\
    \ Time complexity: O(1)\n    [[nodiscard]] int size() const noexcept {\n     \
    \ return length;\n    }\n\n    //! @return Whether both sides are the same sequence\n\
    \    //! @param rhs another sequence\n    //! @note Time complexity: O(size) since\
    \ you are in debugging mode\n    [[nodiscard]] bool operator==(const single_hash&\
    \ rhs) const {\n      const bool res         = (val == rhs.val);\n      const\
    \ bool precise_res = (src == rhs.src);\n      if (__builtin_expect(res != precise_res,\
    \ 0)) {\n        CP_LIBRARY_ERROR(\n          const std::ios_base::fmtflags prev_state\
    \ = std::cerr.flags();\n          std::cerr << \"*** Hash collision detected ***\\\
    n\"\n                    << \"Hash value: (\" << std::hex;\n          internal::rolling_hash_hpp::print_tuple(val,\
    \ std::cerr, std::make_index_sequence<std::tuple_size_v<decltype(val)>> {});\n\
    \          std::cerr << \")\\n\\n\";\n          std::cerr.flags(prev_state);\n\
    \          if constexpr (std::is_same_v<char, Elem>) {\n            std::cerr\
    \ << \"String 1: \\\"\";\n            std::for_each(std::cbegin(src), std::cend(src),\
    \ [](const char c) { std::cerr << c; });\n            std::cerr << \"\\\"\\n\"\
    ;\n            std::cerr << \"String 2: \\\"\";\n            std::for_each(std::cbegin(rhs.src),\
    \ std::cend(rhs.src), [](const char c) { std::cerr << c; });\n            std::cerr\
    \ << \"\\\"\\n\\n\";\n          } else {\n            std::cerr << \"Sequence\
    \ 1: [ \";\n            std::for_each(std::cbegin(src), std::cend(src), [](const\
    \ Elem& e) { std::cerr << e << ' '; });\n            std::cerr << \"]\\n\";\n\
    \            std::cerr << \"Sequence 2: [ \";\n            std::for_each(std::cbegin(rhs.src),\
    \ std::cend(rhs.src), [](const Elem& e) { std::cerr << e << ' '; });\n       \
    \     std::cerr << \"]\\n\\n\";\n          });\n      }\n      return res;\n \
    \   }\n\n    //! @return Whether both sides are NOT the same sequence\n    //!\
    \ @param rhs another sequence\n    //! @note Time complexity: O(number of bases),\
    \ which can be regarded as constant time\n    [[nodiscard]] bool operator!=(const\
    \ single_hash& rhs) const {\n      return !(*this == rhs);\n    }\n\n    //! @brief\
    \ Concatenate two sequences.\n    //! @param rhs another sequence\n    //! @return\
    \ Concatenated sequence\n    //! @note Time complexity: O(length of the resulting\
    \ sequence) since you are in debugging mode\n    [[nodiscard]] single_hash operator+(const\
    \ single_hash& rhs) const {\n      return concat_impl(rhs, std::make_index_sequence<std::tuple_size_v<decltype(bases_tuple)>>\
    \ {});\n    }\n\n    //! @brief Append a sequence at the end.\n    //! @param\
    \ rhs another sequence\n    //! @note Time complexity: O(length of rhs) since\
    \ you are in debugging mode\n    single_hash& operator+=(const single_hash& rhs)\
    \ {\n      concat_self_impl(rhs, std::make_index_sequence<std::tuple_size_v<decltype(bases_tuple)>>\
    \ {});\n      return *this;\n    }\n\n    //! @return Hash value\n    //! @note\
    \ The return value is not just an integer, but a tuple that contains multiple\
    \ integers.\n    //! @note Time complexity: O(number of bases), which can be regarded\
    \ as constant time\n    [[nodiscard]] auto hash_value() const noexcept {\n   \
    \   return val;\n    }\n\n    //! @brief Print information for debugging if CP_LIBRARY_DEBUG_LEVEL\
    \ >= 1 (which is satisfied)\n    void debug_print(const std::string& name = \"\
    \", std::ostream& os = std::cerr) const {\n      if (!name.empty())\n        os\
    \ << name << \": \";\n\n      if constexpr (std::is_same_v<char, Elem>) {\n  \
    \      os << \"    String = \\\"\";\n        std::for_each(std::cbegin(src), std::cend(src),\
    \ [&](const char c) { os << c; });\n        os << \"\\\"\\n\";\n      } else {\n\
    \        os << \"  Sequence = [ \";\n        std::for_each(std::cbegin(src), std::cend(src),\
    \ [&](const Elem& e) { os << e << ' '; });\n        os << \"]\\n\";\n      }\n\
    \n      const std::ios_base::fmtflags prev_state = os.flags();\n      os << (name.empty()\
    \ ? std::string() : std::string(std::size(name) + 2, ' '))\n         << \"Hash\
    \ value = \" << std::hex << '(';\n      internal::rolling_hash_hpp::print_tuple(val,\
    \ os, std::make_index_sequence<std::tuple_size_v<decltype(val)>> {});\n      os\
    \ << \")\\n\\n\";\n      os.flags(prev_state);\n    }\n  };\n\npublic:\n  //!\
    \ @brief Construct a rolling_hash object from source container.\n  //! @note Time\
    \ complexity: O(length)\n  template <typename Container>\n  rolling_hash(const\
    \ Container& source)\n      : src(std::cbegin(source), std::cend(source)), hashes(internal::rolling_hash_hpp::build_hash_sequence<Bases...>(src))\
    \ {}\n\n  //! @return The length of the sequence\n  [[nodiscard]] int size() const\
    \ noexcept(noexcept(std::size(src))) {\n    return static_cast<int>(std::size(src));\n\
    \  }\n\n  //! @return An object that represents the hash value of the entire sequence\n\
    \  //! @note Time complexity: O(length) since you are in debugging mode\n  [[nodiscard]]\
    \ single_hash whole_string() const {\n    return single_hash(src, hashes.back(),\
    \ size());\n  }\n\n  //! @param starts The index where the substring starts (0-indexed)\n\
    \  //! @param length The length of the substring\n  //! @return An object that\
    \ represents the hash value of the substring\n  //! @note Time complexity: O(length)\
    \ since you are in debugging mode\n  [[nodiscard]] single_hash substring(const\
    \ int starts, int length = std::numeric_limits<int>::max()) const {\n    length\
    \ = std::min(static_cast<int>(std::size(src)) - starts, length);\n    return single_hash(std::vector<Elem>(std::cbegin(src)\
    \ + starts, std::cbegin(src) + starts + length), internal::rolling_hash_hpp::substr_hash<Bases...>(hashes,\
    \ starts, length), length);\n  }\n};\n#else\n//! @brief Object that can quickly\
    \ compute the hash value of a substring as well as the entire string.\n//! @tparam\
    \ Elem element type (e.g. char for std::string)\n//! @tparam Bases base (radix)\
    \ integers\ntemplate <typename Elem, std::uint32_t... Bases>\nclass rolling_hash\
    \ {\nprivate:\n  static constexpr std::tuple bases_tuple {Bases...};\n  std::vector<decltype(std::tuple\
    \ {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})> hashes;\n\n  //!\
    \ @brief Object that represents string hash.\n  struct single_hash {\n  private:\n\
    \    decltype(std::tuple {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})\
    \ val;\n    int length;\n\n    template <std::size_t... Is>\n    [[nodiscard]]\
    \ auto concat_impl(const single_hash& rhs, std::index_sequence<Is...>) const {\n\
    \      single_hash res;\n      res.length = length + rhs.length;\n      static_cast<void>(((std::get<Is>(res.val)\
    \ = internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mult(std::get<Is>(val),\
    \ internal::rolling_hash_hpp::pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(rhs.length)))\
    \ + std::get<Is>(rhs.val))), ...));\n      return res;\n    }\n\n    template\
    \ <std::size_t... Is>\n    void concat_self_impl(const single_hash& rhs, std::index_sequence<Is...>)\
    \ {\n      length += rhs.length;\n      static_cast<void>(((std::get<Is>(val)\
    \ = internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mod_mersenne_61(internal::rolling_hash_hpp::mult(std::get<Is>(val),\
    \ internal::rolling_hash_hpp::pow_mod_mersenne_61<std::get<Is>(bases_tuple)>(rhs.length)))\
    \ + std::get<Is>(rhs.val))), ...));\n    }\n\n  public:\n    //! @brief Construct\
    \ empty single_hash object.\n    //! @note Time complexity: O(number of bases),\
    \ which can be regarded as constant time\n    constexpr single_hash() noexcept\n\
    \        : val(), length() {}\n\n    //! @brief Construct singli_hash object from\
    \ hash value and size.\n    //! @note Time complexity: O(number of bases), which\
    \ can be regarded as constant time\n    single_hash(const decltype(std::tuple\
    \ {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})& hash, const int\
    \ size)\n        : val(hash), length(size) {}\n\n    //! @brief Construct singli_hash\
    \ object from hash value and size.\n    //! @note Time complexity: O(number of\
    \ bases), which can be regarded as constant time\n    single_hash(decltype(std::tuple\
    \ {(static_cast<internal::rolling_hash_hpp::u64>(Bases))...})&& hash, const int\
    \ size)\n        : val(std::move(hash)), length(size) {}\n\n    //! @return The\
    \ length of the sequence\n    //! @note Time complexity: O(1)\n    [[nodiscard]]\
    \ int size() const noexcept {\n      return length;\n    }\n\n    //! @param rhs\
    \ another sequence\n    //! @return Whether both sides are the same sequence\n\
    \    //! @note Time complexity: O(number of bases), which can be regarded as constant\
    \ time\n    [[nodiscard]] bool operator==(const single_hash& rhs) const noexcept\
    \ {\n      return (length == rhs.length) && (val == rhs.val);\n    }\n\n    //!\
    \ @param rhs another sequence\n    //! @return Whether both sides are NOT the\
    \ same sequence\n    //! @note Time complexity: O(number of bases), which can\
    \ be regarded as constant time\n    [[nodiscard]] bool operator!=(const single_hash&\
    \ rhs) const noexcept {\n      return !(*this == rhs);\n    }\n\n    //! @brief\
    \ Concatenate two sequences.\n    //! @param rhs another sequence\n    //! @return\
    \ Concatenated sequence\n    //! @note Time complexity: O(number of bases), which\
    \ can be regarded as constant time\n    [[nodiscard]] single_hash operator+(const\
    \ single_hash& rhs) const {\n      return concat_impl(rhs, std::make_index_sequence<std::tuple_size_v<decltype(bases_tuple)>>\
    \ {});\n    }\n\n    //! @brief Append a sequence at the end.\n    //! @param\
    \ rhs another sequence\n    //! @note Time complexity: O(number of bases), which\
    \ can be regarded as constant time\n    single_hash& operator+=(const single_hash&\
    \ rhs) {\n      concat_self_impl(rhs, std::make_index_sequence<std::tuple_size_v<decltype(bases_tuple)>>\
    \ {});\n      return *this;\n    }\n\n    //! @return Hash value\n    //! @note\
    \ The return value is not just an integer, but a tuple that contains multiple\
    \ integers.\n    //! @note Time complexity: O(number of bases), which can be regarded\
    \ as constant time\n    [[nodiscard]] auto hash_value() const noexcept {\n   \
    \   return val;\n    }\n\n    //! @brief Print information for debugging if CP_LIBRARY_DEBUG_LEVEL\
    \ >= 1\n    void debug_print([[maybe_unused]] const std::string& name = \"\",\
    \ [[maybe_unused]] std::ostream& os = std::cerr) const {\n#  if (CP_LIBRARY_DEBUG_LEVEL\
    \ >= 1)\n      if (!name.empty())\n        os << name << \": \";\n\n      const\
    \ std::ios_base::fmtflags prev_state = os.flags();\n      os << \"Hash value =\
    \ \" << std::hex << '(';\n      internal::rolling_hash_hpp::print_tuple(val, os,\
    \ std::make_index_sequence<std::tuple_size_v<decltype(val)>> {});\n      os <<\
    \ \")\\n\";\n      os.flags(prev_state);\n#  endif\n    }\n  };\n\npublic:\n \
    \ //! @brief Construct a rolling_hash object from source container.\n  //! @note\
    \ Time complexity: O(length)\n  template <typename Container>\n  rolling_hash(const\
    \ Container& source)\n      : hashes(internal::rolling_hash_hpp::build_hash_sequence<Bases...>(source))\
    \ {}\n\n  //! @return The length of the sequence\n  [[nodiscard]] int size() const\
    \ noexcept(noexcept(std::size(hashes))) {\n    return static_cast<int>(std::size(hashes))\
    \ - 1;\n  }\n\n  //! @return An object that represents the hash value of the entire\
    \ sequence\n  //! @note Time complexity: O(number of bases), which can be regarded\
    \ as constant time\n  [[nodiscard]] single_hash whole_string() const {\n    return\
    \ single_hash(hashes.back(), size());\n  }\n\n  //! @param starts The index where\
    \ the substring starts (0-indexed)\n  //! @param length The length of the substring\n\
    \  //! @return An object that represents the hash value of the substring\n  //!\
    \ @note Time complexity: O(number of bases), which can be regarded as constant\
    \ time\n  [[nodiscard]] single_hash substring(const int starts, int length = std::numeric_limits<int>::max())\
    \ const {\n    length = std::min(static_cast<int>(std::size(hashes)) - starts\
    \ - 1, length);\n    return single_hash(internal::rolling_hash_hpp::substr_hash<Bases...>(hashes,\
    \ starts, length), length);\n  }\n};\n#endif\n\n//! @brief Returns an object that\
    \ can quickly compute the hash value of a substring as well as the entire string.\n\
    //! @tparam Container source container type (deduced from parameter)\n//! @param\
    \ src source (std::string, std::vector, std::array, ...)\n//! @return An object\
    \ of type rolling_hash_t<Container>.\n//! @note Time complexity: O(size(src))\n\
    template <typename Container>\n[[nodiscard]] auto get_rolling_hash(const Container&\
    \ src) {\n  return rolling_hash<std::decay_t<decltype(*std::cbegin(std::declval<Container>()))>,\
    \ 436523069, 681531337, 843203861>(src);\n}\n\n//! @brief Returns an object that\
    \ represents the hash value of the entire string.\n//! @tparam Container source\
    \ container type (deduced from parameter)\n//! @param src source (std::string,\
    \ std::vector, std::array, ...)\n//! @return An object of type single_hash_t<Container>.\n\
    //! @note Time complexity: O(size(src))\ntemplate <typename Container>\n[[nodiscard]]\
    \ auto get_single_hash(const Container& src) {\n  return get_rolling_hash(src).whole_string();\n\
    }\n\n//! @brief return type of get_rolling_hash function\ntemplate <typename Container>\n\
    using rolling_hash_t = decltype(get_rolling_hash(std::declval<Container>()));\n\
    \n//! @brief return type of get_single_hash function\ntemplate <typename Container>\n\
    using single_hash_t = decltype(get_single_hash(std::declval<Container>()));\n\n\
    }  // namespace lib\n\n#ifdef CP_LIBRARY_ERROR_NOT_DEFINED\n#  undef CP_LIBRARY_ERROR\n\
    #  undef CP_LIBRARY_ERROR_NOT_DEFINED\n#endif\n\n#ifdef CP_LIBRARY_ASSERT_NOT_DEFINED\n\
    #  undef CP_LIBRARY_ASSERT\n#  undef CP_LIBRARY_ASSERT_NOT_DEFINED\n#endif\n\n\
    #ifdef CP_LIBRARY_ROLLING_HASH_MAX_LENGTH_NOT_DEFINED\n#  undef CP_LIBRARY_ROLLING_HASH_MAX_LENGTH\n\
    #  undef CP_LIBRARY_ROLLING_HASH_MAX_LENGTH_NOT_DEFINED\n#endif\n\n#endif  //\
    \ CP_LIBRARY_ROLLING_HASH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/string/rolling_hash.hpp
  requiredBy: []
  timestamp: '2021-08-11 13:50:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/string/rolling_hash/3.test.cpp
  - test/string/rolling_hash/1.test.cpp
  - test/string/rolling_hash/2.test.cpp
documentation_of: include/string/rolling_hash.hpp
layout: document
title: Rolling hash
---

ハッシュ値を前計算しておくことで文字列や配列の大量の比較を定数時間で行うための `rolling_hash` クラスと `single_hash` 構造体が定義されています。実装は[安全で爆速なRollingHashの話](https://qiita.com/keymoon/items/11fac5627672a6d6a9f6)を参考にしています。

文字列([`std::string`](https://cpprefjp.github.io/reference/string/basic_string.html))以外のコンテナ([`std::vector<int>`](https://cpprefjp.github.io/reference/vector/vector.html) 等)でもハッシュ値を計算する事が可能です。以下では便宜上、計算の入力に用いるコンテナを文字列と呼びます。

---

## `rolling_hash` クラス

`rolling_hash` クラスは元となる文字列の(元の文字列自体を含む)連続部分文字列のハッシュ値を高速に計算するための情報を保持するクラスです。このクラスは連続部分文字列のハッシュ値の計算のためにあり、文字列のハッシュ値そのものを表現するためのものではありません。文字列のハッシュ値は `single_hash` 構造体で表現されます。

以下「ハッシュ値」は `single_hash` 型のオブジェクトを指します。

つまり `rolling_hash` 型のオブジェクトは様々な情報を保持した「未分化な状態」で、そこから連続部分文字列の情報を取り出すことで特定の文字列に対するハッシュ値を取得します。連続部分文字列のハッシュ値を計算する必要が無い場合、[後述](https://naskya.github.io/cp-library/include/string/rolling_hash.hpp#single_hash-%E6%A7%8B%E9%80%A0%E4%BD%93)の方法で直接ハッシュ値を取得するとよいです。

### 構築

文字列を `get_rolling_hash` 関数に渡して使います。戻り値の型は `rolling_hash_t<コンテナの型>` と同じです。

```cpp
// 文字列のローリングハッシュを取得
std::string S = "Hello";
const auto S_rhash = lib::get_rolling_hash(S);

// 型名が必要な場合は rolling_hash_t を用いる
std::vector<lib::rolling_hash_t<std::string>> rhash;
rhash.emplace_back(S_rhash);  // OK

// 文字列以外のローリングハッシュも取得可能
std::vector<int> A {1, 2, 3};
const auto A_rhash = lib::get_rolling_hash(A);
```

### メンバ関数

#### `size()`

元の文字列の長さを返します。

#### `substring(start, length)`

C++ の標準ライブラリの [`std::string`](https://cpprefjp.github.io/reference/string/basic_string.html) のメンバ関数 [`substr`](https://cpprefjp.github.io/reference/string/basic_string/substr.html) と同様に、連続部分文字列の開始位置 `start` と長さ `length` を指定することで元の文字列に含まれる連続部分文字列のハッシュ値を取得します。`length` を省略すると文字列の末尾までの連続部分文字列を指定したことになります。戻り値の型は `single_hash_t<コンテナの型>` と同じです。

#### `whole_string()`

文字列全体のハッシュ値(`substring(0)` や `substring(0, size())` と同じ値)を返します。戻り値の型は `single_hash_t<コンテナの型>` と同じです。

```cpp
const std::string S = "0123456789";
const auto S_rhash  = lib::get_rolling_hash(S);

const auto a = S_rhash.substring(5);     // 文字列 "56789" のハッシュ値 (single_hash 型のオブジェクト)
const auto b = S_rhash.substring(2, 3);  // 文字列 "234" のハッシュ値
const auto c = S_rhash.whole_string();   // 文字列 "0123456789" のハッシュ値
```

---

## `single_hash` 構造体

文字列のハッシュ値を保持する構造体です。この構造体のオブジェクトは文字列のハッシュ値と長さの情報だけを持ちます。そのため `single_hash` 構造体のオブジェクトからその文字列に含まれる連続部分文字列のハッシュ値の計算をすることはできません。

### 構築

連続部分文字列のハッシュ値を計算する必要が無く、文字列のハッシュ値を直接取得したい時は `get_single_hash` 関数を使います。戻り値の型は `single_hash_t<コンテナの型>` と同じです。

```cpp
// 文字列のハッシュ値を取得
std::string S = "good";
const auto S_hash = lib::get_single_hash(S);
// const auto S_hash = lib::get_rolling_hash(S).whole_string(); と同じ

// 型名が必要な場合は single_hash_t を用いる
std::vector<lib::single_hash_t<std::string>> hash;
hash.emplace_back(S_hash);  // OK

// 文字列以外のハッシュ値も取得可能
std::vector<int> A {9, 8, 7};
const auto A_hash = lib::get_single_hash(A);
```

### 演算子

以下の演算子がオーバーロードされています。

- `==`
- `!=`
- `+`
- `+=`

#### `operator==`

両辺の `single_hash` 型のオブジェクトが等しいか定数時間で比較します。文字列の長さの比較とハッシュ値の比較が行われ、どちらも等しい時に `true` を、そうでないときに `false` を返します。

```cpp
const std::string A = "This";
const std::string B = "is";
const bool check = (lib::get_rolling_hash(A).substring(2) == lib::get_single_hash(B));  // true
```

[デバッグレベル](https://naskya.github.io/cp-library/about#cp_library_debug_level-%E3%83%9E%E3%82%AF%E3%83%AD)が $2$ 以上の値として定義されている場合には線形時間を掛けて元の文字列を直接比較し、ハッシュ値が等しいのに文字列が異なっている状態(ハッシュ値の衝突)を検知した場合にそれを報告して異常終了します。

#### `operator!=`

`A != B` は `operator==` を呼び出し、`!(A == B)` と同じ値を返します。

#### `operator+`

文字列を結合します。

```cpp
const std::string A = "This ";
const std::string B = "is";
const std::string C = "This is";

const auto A_hash = lib::get_single_hash(A);
const auto B_hash = lib::get_single_hash(B);
const auto C_hash = lib::get_single_hash(C);

const bool check = ((A_hash + B_hash) == C_hash);  // true
```

#### `operator+=`

文字列を末尾に加えます。

```cpp
const std::string A = "This ";
const std::string B = "is";
const std::string C = "This is";

      auto A_hash = lib::get_single_hash(A);  // const 修飾すると += は使えない
const auto B_hash = lib::get_single_hash(B);
const auto C_hash = lib::get_single_hash(C);

A_hash += B_hash;

const bool check = (A_hash == C_hash);  // true
```

### メンバ関数

#### `size()`

文字列の長さを返します。

#### `hash_value()`

ハッシュ値を返します。戻り値は [`std::uint_least64_t`](https://cpprefjp.github.io/reference/cstdint/uint_least64_t.html) がいくつか入ったタプル ([`std::tuple<std::uint_least64_t, std::uint_least64_t, ...>`](https://cpprefjp.github.io/reference/tuple/tuple.html)) です。比較判定などはこの関数でハッシュ値を取得しなくても行えるので基本的には使用する必要の無い関数です。

#### `debug_print()`

[デバッグレベル](https://naskya.github.io/cp-library/about#cp_library_debug_level-%E3%83%9E%E3%82%AF%E3%83%AD)が $1$ 以上のとき、標準エラー出力にデバッグ情報(`hash_value()` の返す値)を出力します。
[デバッグレベル](https://naskya.github.io/cp-library/about#cp_library_debug_level-%E3%83%9E%E3%82%AF%E3%83%AD)が $2$ 以上のとき、文字列の内容も加えて出力します。

---
