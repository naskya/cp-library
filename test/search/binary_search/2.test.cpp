#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_4_A"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "../../../include/search/binary_search.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> S(n + 2);
  std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(S) + 1);
  std::sort(std::begin(S) + 1, std::end(S) - 1);

  S.front() = -2000000000;
  S.back()  = 2000000000;

  int q;
  std::cin >> q;

  int t;
  const auto lower_bound = [&](const int idx) -> bool { return S[idx] <= t; };

  long long res = 0;

  while (q--) {
    std::cin >> t;
    const int idx = lib::binary_search(0, n + 1, lower_bound);
    res += (S[idx] == t);
  }

  std::cout << res << "\n";
}
