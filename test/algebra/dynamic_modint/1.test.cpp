#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_B"
#include <iostream>

#include "../../../include/algebra/dynamic_modint.hpp"

int mod = 1000000007;

int main() {
  lib::dynamic_modint<decltype(mod), &mod> m;

  int n;
  std::cin >> m >> n;

  std::cout << m.pow(n) << '\n';
}
