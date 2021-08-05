#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A"
#include <iostream>
#include <vector>

#include "../../../include/graph/minimum_spanning_tree.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int V, E;
  std::cin >> V >> E;

  constexpr int INF = 1000000005;
  std::vector adjacency_matrix(V, std::vector<int>(V, INF));

  for (int i = 0; i < V; ++i)
    adjacency_matrix[i][i] = 0;

  for (int i = 0; i < E; ++i) {
    int node_1, node_2;
    std::cin >> node_1 >> node_2 >> adjacency_matrix[node_1][node_2];
    adjacency_matrix[node_2][node_1] = adjacency_matrix[node_1][node_2];
  }

  std::cout << lib::minimum_spanning_tree<int>(adjacency_matrix, INF).second << '\n';
}
