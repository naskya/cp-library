
//! @file minimum_spanning_tree.hpp

#ifndef CP_LIBRARY_MINIMUM_SPANNING_TREE_HPP
#define CP_LIBRARY_MINIMUM_SPANNING_TREE_HPP

#include <algorithm>
#include <cassert>
#include <queue>
#include <tuple>
#include <vector>

#ifndef CP_LIBRARY_WARN
#  if (CP_LIBRARY_DEBUG_LEVEL >= 1)
//! @brief Print warning message
//! @note You can suppress the warning by uncommenting line 18
#    define CP_LIBRARY_WARN(msg) (std::cerr << (msg) << '\n')
// #  define CP_LIBRARY_WARN(msg) (static_cast<void>(0))
#  else
#    define CP_LIBRARY_WARN(msg) (static_cast<void>(0))
#  endif
#  define CP_LIBRARY_WARN_NOT_DEFINED
#endif

#ifndef CP_LIBRARY_ASSERT
//! @brief Assert macro
#  define CP_LIBRARY_ASSERT(...) assert(__VA_ARGS__)
#  define CP_LIBRARY_ASSERT_NOT_DEFINED
#endif

namespace lib {

namespace internal {
  //! @note from union_find.hpp
  class simple_union_find {
  private:
    const int nodes;
    mutable std::vector<int> par_or_size;

  public:
    simple_union_find(const int number_of_nodes)
        : nodes(number_of_nodes), par_or_size(number_of_nodes, -1) {}

    [[nodiscard]] int parent(const int node) const {
      CP_LIBRARY_ASSERT(0 <= node && node < nodes);
      if (par_or_size[node] < 0)
        return node;
      else
        return par_or_size[node] = parent(par_or_size[node]);
    }

    [[maybe_unused]] bool merge(int node_1, int node_2) {
      node_1 = parent(node_1);
      node_2 = parent(node_2);

      if (node_1 == node_2)
        return false;

      if (par_or_size[node_1] > par_or_size[node_2])
        std::swap(node_1, node_2);
      par_or_size[node_1] += par_or_size[node_2];
      par_or_size[node_2] = node_1;

      return true;
    }
  };
}  // namespace internal

//! @brief Find the minimum spanning tree from edge list using Kruskal method.
//! @tparam TotalCostType type of total cost (NOT deduced from parameter, int or long long should work in most cases)
//! @tparam NodeIndexType type of node indices (deduced from parameter)
//! @tparam CostType type of costs (deduced from parameter)
//! @tparam Container container type of edge list (deduced from parameter)
//! @param nodes number of nodes
//! @param edge_list list of edges (edges must be represented as {node_1, node_2, cost})
//! @return std::pair<vector, CostType> (list of edges in minimum spanning tree, total cost)
//! @note time complexity: O(E log V) where E is number of edges and V is number of nodes
template <typename TotalCostType, typename NodeIndexType, typename CostType, template <typename...> typename Container>
[[nodiscard]] auto minimum_spanning_tree(const int nodes,
                                         const Container<std::tuple<NodeIndexType, NodeIndexType, CostType>>& edge_list) {
  using Edge = std::tuple<NodeIndexType, NodeIndexType, CostType>;
  std::pair<std::vector<Edge>, TotalCostType> res {{}, TotalCostType(0)};

  if (edge_list.empty()) {
    CP_LIBRARY_WARN("An empty edge list is provided.");
    return res;
  }

  auto edge_list_cpy = edge_list;

  std::sort(std::begin(edge_list_cpy), std::end(edge_list_cpy), [](const Edge& lhs, const Edge& rhs) {
    return std::get<2>(lhs) < std::get<2>(rhs);
  });

  internal::simple_union_find uf(nodes);

  for (auto&& [node_1, node_2, cost] : edge_list_cpy) {
    if (uf.merge(node_1, node_2)) {
      res.first.emplace_back(node_1, node_2, cost);
      res.second += cost;
    }
  }

  return res;
}

//! @brief Find the minimum spanning tree from edge list using Kruskal method.
//! @tparam TotalCostType type of total cost (NOT deduced from parameter, int or long long should work in most cases)
//! @tparam NodeIndexType type of node indices (deduced from parameter)
//! @tparam CostType type of costs (deduced from parameter)
//! @tparam Container container type of edge list (deduced from parameter)
//! @param nodes number of nodes
//! @param edge_list list of edges (edges must be represented as {node_1, node_2, cost})
//! @return std::pair<vector, CostType> (list of edges in minimum spanning tree, total cost)
//! @note time complexity: O(E log V) where E is number of edges and V is number of nodes
template <typename TotalCostType, typename NodeIndexType, typename CostType, template <typename...> typename Container>
[[nodiscard]] auto minimum_spanning_tree(const int nodes,
                                         Container<std::tuple<NodeIndexType, NodeIndexType, CostType>>&& edge_list) {
  using Edge = std::tuple<NodeIndexType, NodeIndexType, CostType>;
  std::pair<std::vector<Edge>, TotalCostType> res {{}, TotalCostType(0)};

  if (edge_list.empty()) {
    CP_LIBRARY_WARN("An empty edge list is provided.");
    return res;
  }

  std::sort(std::begin(edge_list), std::end(edge_list), [](const Edge& lhs, const Edge& rhs) {
    return std::get<2>(lhs) < std::get<2>(rhs);
  });

  internal::simple_union_find uf(nodes);

  for (auto&& [node_1, node_2, cost] : edge_list) {
    if (uf.merge(node_1, node_2)) {
      res.first.emplace_back(node_1, node_2, cost);
      res.second += cost;
    }
  }

  return res;
}

//! @brief Find the minimum spanning tree from adjacency list using Prim method.
//! @tparam TotalCostType type of total cost (NOT deduced from parameter, int or long long should work in most cases)
//! @tparam NodeIndexType type of node indices (deduced from parameter)
//! @tparam CostType type of costs (deduced from parameter)
//! @tparam Container container type of adjacency list (deduced from parameter)
//! @param adjacency_list adjacency_list[i] = { std::pair(a, cost_between_i_a), std::pair(b, cost_between_i_b), ... }
//! @return std::pair<2d vector, CostType> (adjacency list of minimun spanning tree, total cost)
//! @note time complexity: O(E log V) where E is number of edges and V is number of nodes
template <typename TotalCostType, typename NodeIndexType, typename CostType, template <typename...> typename Container>
[[nodiscard]] auto minimum_spanning_tree(const Container<Container<std::pair<NodeIndexType, CostType>>>& adjacency_list) {
  const int nodes = static_cast<int>(std::size(adjacency_list));
  std::pair res {std::vector<std::vector<std::pair<NodeIndexType, CostType>>>(nodes), TotalCostType(0)};

  if (nodes == 0) {
    CP_LIBRARY_WARN("An empty adjacency list is provided.");
    return res;
  }

  using Edge = std::tuple<CostType, NodeIndexType, NodeIndexType>;
  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> heap;

  std::vector<signed char> reached(nodes, false);
  reached[0] = true;

  for (const auto& [node, cost] : adjacency_list[0])
    heap.emplace(cost, 0, node);

  while (!heap.empty()) {
    const auto [cost_1_2, node_1, node_2] = heap.top();
    heap.pop();

    if (reached[node_2])
      continue;

    reached[node_2] = true;
    res.second += cost_1_2;
    res.first[node_1].emplace_back(node_2, cost_1_2);
    res.first[node_2].emplace_back(node_1, cost_1_2);

    for (const auto& [node_3, cost_2_3] : adjacency_list[node_2])
      if (!reached[node_3])
        heap.emplace(cost_2_3, node_2, node_3);
  }

  return res;
}

//! @brief Find the minimum spanning tree from adjacency matrix using Prim method.
//! @tparam TotalCostType type of total cost (NOT deduced from parameter, int or long long should work in most cases)
//! @tparam CostType type of costs (deduced from parameter)
//! @tparam Container container type of adjacency matrix (deduced from parameter)
//! @param adjacency_matrix adjacency_matrix[i][j] = (cost between i, j) or (infinity) if there's no edge between i, j
//! @param infinity very large number that indicates there is no edge
//! @return std::pair<2d vector, CostType> (adjacency matrix of minimun spanning tree, total cost)
//! @note time complexity: O(E log V) where E is number of edges and V is number of nodes
template <typename TotalCostType, typename CostType, template <typename...> typename Container>
[[nodiscard]] auto minimum_spanning_tree(const Container<Container<CostType>>& adjacency_matrix,
                                         const CostType infinity) {
  const int nodes = static_cast<int>(std::size(adjacency_matrix));
  std::pair res {std::vector(nodes, std::vector<CostType>(nodes, infinity)), TotalCostType(0)};

  if (nodes == 0) {
    CP_LIBRARY_WARN("An empty adjacency matrix is provided.");
    return res;
  }

  using Edge = std::tuple<CostType, int, int>;
  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> heap;

  std::vector<signed char> reached(nodes, false);
  reached[0] = true;

  for (int i = 1; i < nodes; ++i)
    if (adjacency_matrix[0][i] < infinity)
      heap.emplace(adjacency_matrix[0][i], 0, i);

  while (!heap.empty()) {
    const auto [cost_1_2, node_1, node_2] = heap.top();
    heap.pop();

    if (reached[node_2])
      continue;

    reached[node_2] = true;
    res.second += cost_1_2;
    res.first[node_1][node_2] = res.first[node_2][node_1] = cost_1_2;

    for (int node_3 = 0; node_3 < nodes; ++node_3)
      if (adjacency_matrix[node_2][node_3] < infinity && !reached[node_3])
        heap.emplace(adjacency_matrix[node_2][node_3], node_2, node_3);
  }

  return res;
}

}  // namespace lib

#ifdef CP_LIBRARY_WARN_NOT_DEFINED
#  undef CP_LIBRARY_WARN
#  undef CP_LIBRARY_WARN_NOT_DEFINED
#  ifdef CP_LIBRARY_WARN
#    undef CP_LIBRARY_WARN
#  endif
#endif

#ifdef CP_LIBRARY_ASSERT_NOT_DEFINED
#  undef CP_LIBRARY_ASSERT
#  undef CP_LIBRARY_ASSERT_NOT_DEFINED
#endif

#endif  // CP_LIBRARY_MINIMUM_SPANNING_TREE_HPP
