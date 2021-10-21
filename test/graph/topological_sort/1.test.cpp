// ToDo: remove this line
// The problem is not available for testing due to the specitications of verification-helper.
// see: https://github.com/online-judge-tools/verification-helper/issues/377
// However, we can get AC by submitting the program manually.
#define IGNORE

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_B"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "../../../include/graph/topological_sort.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int V, E;
  std::cin >> V >> E;

  std::vector<std::vector<int>> graph(V);
  for (int i = 0; i < E; ++i) {
    int s, t;
    std::cin >> s >> t;
    graph[s].emplace_back(t);
  }

  const auto sorted = lib::topological_sort(graph);
  std::copy(std::cbegin(sorted), std::cend(sorted), std::ostream_iterator<int>(std::cout, "\n"));
}
