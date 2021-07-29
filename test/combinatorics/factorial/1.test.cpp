#define PROBLEM "https://yukicoder.me/problems/no/797"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "../../../include/algebra/static_modint.hpp"
#include "../../../include/combinatorics/factorial.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  using mint = lib::static_modint<1000000007>;

  int N;
  std::cin >> N;

  std::vector<mint> a(N);
  std::copy_n(std::istream_iterator<mint>(std::cin), N, std::begin(a));

  const auto fact     = lib::factorial_array<100000, mint>();
  const auto fact_inv = lib::factorial_modinv_array<100000>(fact.back());

  mint res;

  for (int i = 0; i < N; ++i)
    res += a[i] * fact[N - 1] * fact_inv[i] * fact_inv[N - 1 - i];

  std::cout << res << "\n";
}
