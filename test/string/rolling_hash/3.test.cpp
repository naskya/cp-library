#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"
#include <iostream>
#include <string>

#define ROLLING_HASH_MAX_LENGTH 1000000
#include "../../../include/string/rolling_hash.hpp"

int main() {
  std::string T, P;
  std::cin >> T >> P;

  const int T_len = static_cast<int>(std::size(T));
  const int P_len = static_cast<int>(std::size(P));

  const auto T_rhash = lib::get_rolling_hash(T);
  const auto P_hash  = lib::get_single_hash(P);

  for (int i = 0; i <= T_len - P_len; ++i)
    if (T_rhash.substring(i, P_len) == P_hash)
      std::cout << i << '\n';
}
