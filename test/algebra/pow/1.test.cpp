#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_B"
#include <iostream>

#include "../../../include/algebra/pow.hpp"
#include "../../../include/algebra/static_modint.hpp"

int main() {
  lib::static_modint<1'000'000'007> m;
  int n;

  std::cin >> m >> n;
  std::cout << lib::pow(m, n) << '\n';
}
