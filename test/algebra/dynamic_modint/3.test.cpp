#define PROBLEM "https://yukicoder.me/problems/no/1299"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

#include "../../../include/algebra/dynamic_modint.hpp"

int MOD = 998244353;

int main() {
  int N;
  long long K;
  std::cin >> N >> K;

  using mint = lib::dynamic_modint<decltype(MOD), &MOD>;

  std::vector<mint> A(N);
  std::copy_n(std::istream_iterator<mint>(std::cin), N, std::begin(A));
  const mint sum = std::reduce(std::cbegin(A), std::cend(A), mint());

  std::cout << sum * mint(2).pow(K) << '\n';
}
