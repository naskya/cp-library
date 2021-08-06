#define PROBLEM "https://atcoder.jp/contests/abc194/tasks/abc194_e"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "../../../include/data_structure/segment_tree.hpp"

long long min(long long x, long long y) {
  return x < y ? x : y;
}

int main() {
  int N, M;
  std::cin >> N >> M;

  std::vector<int> A(N);
  std::copy_n(std::istream_iterator<int>(std::cin), N, std::begin(A));

  constexpr long long INF  = 1000000005;
  constexpr long long LINF = 1000000000000000005;

  lib::segment_tree tree(N, LINF, &min);

  {
    lib::no_range_query_in_this_scope query_lock(tree);
    for (int i = 0; i < N; ++i)
      tree.set(i, i);
    for (int i = 0; i < M; ++i)
      tree.add(A[i], INF);
  }

  long long res = N;

  for (int i = 0; i <= N - M; ++i) {
    res = std::min(res, tree.all_prod());
    tree.add(A[i], -INF);
    if (i < N - M)
      tree.add(A[i + M], INF);
  }

  std::cout << res << '\n';
}
