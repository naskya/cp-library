#define PROBLEM "https://yukicoder.me/problems/no/1552"
#include <iostream>
#include <vector>

#include "../../../include/algebra/static_modint.hpp"

int main() {
  long long N;
  int M;
  std::cin >> N >> M;

  using mint = lib::static_modint<998244353>;

  mint res = 0, s = 0;
  std::vector<mint> l(M + 1), m(M + 2);

  for (int i = 1; i <= M; ++i) {
    s += i;
    l[i]         = mint(i).pow(N - 1) * N * s;
    m[M - i + 1] = mint(i).pow(N) * N * (M + 1) - l[i];
  }

  for (int i = 1; i <= M; ++i) {
    res += i * (l[i] - l[i - 1]);
    res -= i * (m[i] - m[i + 1]);
  }

  std::cout << res << '\n';
}
