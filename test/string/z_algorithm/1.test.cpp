#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include <iostream>
#include <string>

#include "../../../include/string/z_algorithm.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string S;
  std::cin >> S;

  for (auto&& l : lib::z_algorithm(S))
    std::cout << l << ' ';

  std::cout << '\n';
}
