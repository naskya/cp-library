#define PROBLEM "https://yukicoder.me/problems/no/1300"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>

#include "../../../include/algebra/static_modint.hpp"
#include "../../../include/data_structure/binary_indexed_tree.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N;
  std::cin >> N;

  std::vector<int> A(N);
  std::copy_n(std::istream_iterator<int>(std::cin), N, std::begin(A));

  std::map<int, int> count;
  std::for_each(std::cbegin(A), std::cend(A), [&](const int a) { ++count[a]; });

  std::vector<std::pair<int, int>> L, R;
  std::for_each(std::cbegin(count), std::cend(count), [&](const auto p) { L.emplace_back(p); R.emplace_back(p); });

  std::sort(std::begin(L), std::end(L));
  std::sort(std::rbegin(R), std::rend(R));

  const int M = static_cast<int>(std::size(L));

  lib::binary_indexed_tree<long long> L_acc(M), R_acc(M);
  lib::binary_indexed_tree<int> L_cnt(M), R_cnt(M);

  for (int i = 0; i < M; i++) {
    L_acc.add(i, L[i].first * L[i].second);
    L_cnt.add(i, L[i].second);
    R_acc.add(i, R[i].first * R[i].second);
    R_cnt.add(i, R[i].second);
  }

  using mint = lib::static_modint<998244353>;

  std::vector<mint> right(N), left(N);
  std::vector<int> rs(N), ls(N);

  for (int i = 0; i < N - 1; i++) {
    const int idx = static_cast<int>(std::distance(std::cbegin(L), std::lower_bound(std::cbegin(L), std::cend(L), std::pair {A[i], 0})));
    L_cnt.add(idx, -1);
    L_acc.add(idx, -A[i]);

    if (i == 0 || idx == 0)
      continue;

    right[i] = mint(L_acc.sum(0, idx));
    rs[i]    = L_cnt.sum(0, idx);
  }

  for (int i = 0; i < N - 1; i++) {
    const int idx = static_cast<int>(std::distance(std::lower_bound(std::crbegin(R), std::crend(R), std::pair {A[N - 1 - i], 0}), std::crend(R)) - 1);
    --R[idx].second;
    R_cnt.add(idx, -1);
    R_acc.add(idx, -A[N - 1 - i]);

    if (i == 0 || idx == 0)
      continue;

    left[i] = mint(R_acc.sum(0, idx));
    ls[i]   = R_cnt.sum(0, idx);
  }

  std::reverse(std::begin(left), std::end(left));
  std::reverse(std::begin(ls), std::end(ls));

  mint res;

  for (int i = 0; i < N - 1; i++) {
    res += mint(right[i]) * ls[i];
    res += mint(left[i]) * rs[i];
    res += mint(A[i]) * rs[i] * ls[i];
  }

  std::cout << res << '\n';
}
