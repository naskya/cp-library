#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B"
#include <iostream>

#include "../../../include/data_structure/segment_tree.hpp"

int main() {
  int n, q;
  std::cin >> n >> q;
  lib::segment_tree tree(n);

  while (q--) {
    int c, x, y;
    std::cin >> c >> x >> y;
    --x;

    if (c == 0)
      tree.add(x, y);
    else
      std::cout << tree.prod(x, y) << '\n';
  }
}
