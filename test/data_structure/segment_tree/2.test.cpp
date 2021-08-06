#define PROBLEM "https://atcoder.jp/contests/abc185/tasks/abc185_f"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

#include "../../../include/data_structure/segment_tree.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, Q;
  std::cin >> N >> Q;

  lib::segment_tree<int, std::bit_xor<>> tree(N);

  {
    lib::no_range_query_in_this_scope query_lock(tree);
    for (int i = 0; i < N; ++i) {
      int buf;
      std::cin >> buf;
      tree.set(i, buf);
    }
  }

  while (Q--) {
    int t, x, y;
    std::cin >> t >> x >> y;
    --x;

    if (t == 1)
      tree.set(x, tree.get(x) ^ y);
    else
      std::cout << tree.prod(x, y) << '\n';
  }
}
