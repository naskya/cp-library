#define PROBLEM "https://yukicoder.me/problems/no/430"
#include <iostream>
#include <string>

#define ROLLING_HASH_MAX_LENGTH 50000
#include "../../../include/string/rolling_hash.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string S;
  std::cin >> S;

  const auto S_hashes = lib::get_rolling_hash(S);
  const auto S_len    = static_cast<int>(std::size(S));

  std::vector precalc_hashes(S_len, std::vector<lib::single_hash_t<std::string>>(11));

  for (int len = 1; len <= 10; ++len)
    for (int start = 0; start <= S_len - len; ++start)
      precalc_hashes[start][len] = S_hashes.substring(start, len);

  int M, res = 0;
  std::cin >> M;

  std::string tmp;

  while (M--) {
    std::cin >> tmp;
    const auto tmp_hash = lib::get_single_hash(tmp);
    const auto tmp_len  = static_cast<int>(std::size(tmp));

    std::cerr << tmp << '\n';

    for (int start = 0; start <= S_len - tmp_len; ++start)
      res += static_cast<int>(precalc_hashes[start][tmp_len] == tmp_hash);
  }

  std::cout << res << '\n';
}
