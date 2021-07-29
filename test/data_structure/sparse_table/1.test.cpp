#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "../../../include/data_structure/sparse_table.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, Q;
  std::cin >> N >> Q;

  std::vector<int> A(N);
  std::copy_n(std::istream_iterator<int>(std::cin), N, std::begin(A));

  const auto F  = [](const int x, const int y) constexpr { return std::min(x, y); };
  const auto st = lib::make_sparse_table(A, F);

  while (Q--) {
    int l, r;
    std::cin >> l >> r;
    std::cout << st.query(l, r) << '\n';
  }
}
