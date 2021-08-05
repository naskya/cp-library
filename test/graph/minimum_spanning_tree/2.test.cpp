#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A"
#include <iostream>
#include <utility>
#include <vector>

#include "../../../include/graph/minimum_spanning_tree.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int V, E;
  std::cin >> V >> E;

  std::vector<std::tuple<int, int, int>> edges(E);

  for (int i = 0; i < E; ++i)
    std::cin >> std::get<0>(edges[i]) >> std::get<1>(edges[i]) >> std::get<2>(edges[i]);

  std::cout << lib::minimum_spanning_tree<int>(V, std::move(edges)).second << '\n';
}
