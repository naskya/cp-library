#define PROBLEM "https://atcoder.jp/contests/abc223/tasks/abc223_d"
#include <functional>
#include <iostream>
#include <vector>

#include "../../../include/graph/topological_sort.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, M;
  std::cin >> N >> M;

  std::vector<std::vector<int>> graph(N);
  for (int i = 0; i < M; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u;
    --v;
    graph[u].emplace_back(v);
  }

  if (const auto sorted = lib::topological_sort<std::less<>>(graph); static_cast<int>(std::size(sorted)) == N) {
    bool first = true;
    for (const int i : sorted) {
      if (!first) {
        std::cout << ' ';
      } else {
        first = false;
      }
      std::cout << i + 1;
    }
    std::cout << '\n';
  } else {
    std::cout << "-1\n";
  }
}
