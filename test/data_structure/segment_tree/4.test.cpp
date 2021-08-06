#define PROBLEM "https://atcoder.jp/contests/abc194/tasks/abc194_e"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "../../../include/data_structure/segment_tree.hpp"

template <typename T1, typename T2>
std::pair<T1, T2> operator+(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) {
  return {lhs.first + rhs.first, lhs.second + rhs.second};
}

int main() {
  int N, M;
  std::cin >> N >> M;

  std::vector<int> A(N);
  std::copy_n(std::istream_iterator<int>(std::cin), N, std::begin(A));

  using P = std::pair<int, int>;

  const auto op    = [](const P& x, const P& y) constexpr { return std::min(x, y); };
  constexpr P PINF = {1000000005, 1000000005};

  lib::segment_tree tree(N, PINF, op);

  {
    lib::no_range_query_in_this_scope query_lock(tree);
    for (int i = 0; i < N; ++i)
      tree.set(i, {0, i});
    for (int i = 0; i < M; ++i)
      tree.add(A[i], {1, 0});
  }

  std::pair<int, int> res {0, N};

  for (int i = 0; i <= N - M; ++i) {
    res = std::min(res, tree.all_prod());
    tree.add(A[i], {-1, 0});
    if (i < N - M)
      tree.add(A[i + M], {1, 0});
  }

  std::cout << res.second << '\n';
}
