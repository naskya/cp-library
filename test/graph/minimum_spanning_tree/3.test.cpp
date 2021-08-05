#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A"
#include <iostream>
#include <vector>

#include "../../../include/graph/minimum_spanning_tree.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int V, E;
  std::cin >> V >> E;

  std::vector<std::vector<std::pair<int, int>>> adjacency_list(V);

  for (int i = 0; i < E; ++i) {
    int node_1, node_2, cost;
    std::cin >> node_1 >> node_2 >> cost;
    adjacency_list[node_1].emplace_back(node_2, cost);
    adjacency_list[node_2].emplace_back(node_1, cost);
  }

  std::cout << lib::minimum_spanning_tree<int>(adjacency_list).second << '\n';
}
