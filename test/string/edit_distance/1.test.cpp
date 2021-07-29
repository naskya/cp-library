#define PROBLEM "https://atcoder.jp/contests/abc185/tasks/abc185_e"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "../../../include/string/edit_distance.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, M;
  std::cin >> N >> M;

  std::vector<int> A(N), B(M);
  std::copy_n(std::istream_iterator<int>(std::cin), N, std::begin(A));
  std::copy_n(std::istream_iterator<int>(std::cin), M, std::begin(B));

  std::cout << lib::edit_distance(A, B) << '\n';
}
