#define PROBLEM "https://atcoder.jp/contests/abc179/tasks/abc179_d"
#include <iostream>
#include <vector>

#include "../../../include/algebra/static_modint.hpp"
#include "../../../include/data_structure/binary_indexed_tree.hpp"

int main() {
  int N, K;
  std::cin >> N >> K;

  std::vector<int> L(K), R(K);
  for (int i = 0; i < K; ++i)
    std::cin >> L[i] >> R[i];

  lib::binary_indexed_tree<lib::static_modint<998244353>> tree(N);
  tree.add(0, 1);

  for (int i = 0; i < N; ++i) {
    const auto current = tree.get(i);

    for (int j = 0; j < K; ++j) {
      const int l = i + L[j];
      const int r = std::min(N, i + 1 + R[j]);

      if (l < N)
        tree.uniform_add(l, r, current);
    }
  }

  std::cout << tree.get(N - 1) << '\n';
}
