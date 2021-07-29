
//! @file union_find.hpp
//! @details Provide a data structure for managing disjoint sets.
//! @note This file is based on AtCoder Library https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp

#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include <algorithm>
#include <cassert>
#include <vector>

#ifndef O_assert
//! @brief Assert macro
#  define O_assert(...) assert(__VA_ARGS__)
#  define O_assert_not_defined
#endif

namespace lib {

//! @brief Data structure for managing disjoint sets
class union_find {
private:
  const int nodes;
  mutable std::vector<int> par_or_size;

public:
  //! @brief Construct an undirected graph with number_of_nodes nodes and 0 edges
  union_find(const int number_of_nodes)
      : nodes(number_of_nodes), par_or_size(number_of_nodes, -1) {}

  //! @return Number of nodes in the whole graph
  [[nodiscard]] int size() const noexcept {
    return nodes;
  }

  //! @param node Index of the node (0-indexed)
  //! @return Index of the parent node (0-indexed)
  //! @note Time complexity: O(a(number_of_nodes)) where a is the inverse ackermann function
  [[nodiscard]] int parent(const int node) const {
    O_assert(0 <= node && node < nodes);
    if (par_or_size[node] < 0)
      return node;
    else
      return par_or_size[node] = parent(par_or_size[node]);
  }

  //! @param node_1 Index of node 1 (0-indexed)
  //! @param node_2 Index of node 2 (0-indexed)
  //! @return Whether node 1 and node 2 belong to the same group
  //! @note Time complexity: O(a(number_of_nodes)) where a is the inverse ackermann function
  [[nodiscard]] bool same(const int node_1, const int node_2) const {
    return parent(node_1) == parent(node_2);
  }

  //! @param node Index of the node (0-indexed)
  //! @return Size of the group to which node belongs
  //! @note Time complexity: O(1)
  [[nodiscard]] int group_size(const int node) const {
    return -par_or_size[parent(node)];
  }

  //! @param node_1 Index of node 1 (0-indexed)
  //! @param node_2 Index of node 2 (0-indexed)
  //! @return Whether the graph is changed by the operation
  //! @note Time complexity: O(a(number_of_nodes)) where a is the inverse ackermann function
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

  //! @return Vector of the connected components of the graph
  //! @note Time complexity: O(number_of_nodes)
  [[nodiscard]] std::vector<std::vector<int>> groups() const {
    std::vector<int> leader_buf(nodes), group_size(nodes);
    for (int i = 0; i < nodes; i++) {
      leader_buf[i] = parent(i);
      group_size[leader_buf[i]]++;
    }
    std::vector<std::vector<int>> res(nodes);
    for (int i = 0; i < nodes; i++) {
      res[i].reserve(group_size[i]);
    }
    for (int i = 0; i < nodes; i++) {
      res[leader_buf[i]].emplace_back(i);
    }
    res.erase(
      std::remove_if(std::begin(res), std::end(res),
                     [&](const std::vector<int>& v) { return v.empty(); }),
      std::end(res));
    return res;
  }
};

}  // namespace lib

#ifdef O_assert_not_defined
#  undef O_assert
#  undef O_assert_not_defined
#endif

#endif  // UNION_FIND_HPP
