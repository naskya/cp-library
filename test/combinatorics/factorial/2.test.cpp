#define PROBLEM "https://atcoder.jp/contests/abc156/tasks/abc156_d"
#include <iostream>

#include "../../../include/algebra/static_modint.hpp"
#include "../../../include/combinatorics/factorial.hpp"

int main() {
  int N, A, B;
  std::cin >> N >> A >> B;

  using mint = lib::static_modint<1000000007>;

  mint res = mint(2).pow(N) - 1;
  res -= lib::combination<int, mint>(N, A);
  res -= lib::combination<int, mint>(N, B);

  std::cout << res << '\n';
}
