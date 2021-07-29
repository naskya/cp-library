#define PROBLEM "https://atcoder.jp/contests/abc186/tasks/abc186_e"
#include <iostream>
#include <numeric>

#include "../../../include/algebra/dynamic_modint.hpp"

int MOD;

int main() {
  using mint = lib::dynamic_modint<decltype(MOD), &MOD>;

  int T;
  std::cin >> T;

  while (T--) {
    int N, S, K;
    std::cin >> N >> S >> K;

    int G = std::gcd(N, K);

    if (K % N == 0 || (G != 1 && S % G != 0)) {
      std::cout << -1 << '\n';
      continue;
    }

    G = std::gcd(G, S);

    MOD = N / G;
    S /= G;
    K /= G;

    std::cout << mint(-S) / K << '\n';
  }
}
