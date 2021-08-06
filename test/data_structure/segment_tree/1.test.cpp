#define PROBLEM "https://atcoder.jp/contests/abc185/tasks/abc185_f"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

#include "../../../include/data_structure/segment_tree.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, Q;
  std::cin >> N >> Q;

  std::vector<int> A(N);
  std::copy_n(std::istream_iterator<int>(std::cin), N, std::begin(A));

  lib::segment_tree<int, std::bit_xor<>> tree(A);

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
