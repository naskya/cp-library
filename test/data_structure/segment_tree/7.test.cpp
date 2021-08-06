#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A"
#include <algorithm>
#include <iostream>

#include "../../../include/data_structure/segment_tree.hpp"

int main() {
  int n, q;
  std::cin >> n >> q;

  const auto op     = [](const auto& x, const auto& y) constexpr { return std::min(x, y); };
  lib::segment_tree tree(n, 2147483647, 2147483647, op);

  while (q--) {
    int c, x, y;
    std::cin >> c >> x >> y;

    if (c == 0)
      tree.set(x, y);
    else
      std::cout << tree.prod(x, y + 1) << '\n';
  }
}
