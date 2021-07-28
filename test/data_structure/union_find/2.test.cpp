#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_A"
#include <iostream>

#include "../../../include/data_structure/union_find.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, Q;
  std::cin >> N >> Q;

  lib::union_find uf(N);

  while (Q--) {
    int t, u, v;
    std::cin >> t >> u >> v;

    if (t == 0)
      uf.merge(u, v);
    else
      std::cout << static_cast<int>(uf.same(u, v)) << '\n';
  }
}
