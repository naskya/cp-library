#define PROBLEM "https://atcoder.jp/contests/abc141/tasks/abc141_e"
#include <algorithm>
#include <iostream>
#include <string>

#define CP_LIBRARY_ROLLING_HASH_MAX_LENGTH 5000
#include "../../../include/string/rolling_hash.hpp"

int main() {
  int N, res = 0;
  std::string S;
  std::cin >> N >> S;

  const auto S_hash = lib::get_rolling_hash(S);

  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      int tmp = res;

      while (true) {
        if (i + tmp >= j || j + tmp >= N)
          break;
        if (S_hash.substring(i, tmp + 1) != S_hash.substring(j, tmp + 1))
          break;
        ++tmp;
      }

      res = std::max(res, tmp);
    }
  }

  std::cout << res << '\n';
}
