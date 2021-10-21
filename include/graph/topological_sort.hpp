
//! @file topologocal_sort.hpp

#ifndef CP_LIBRARY_TOPOLOGICAL_SORT_HPP
#define CP_LIBRARY_TOPOLOGICAL_SORT_HPP

#include <iostream>
#include <queue>
#include <type_traits>
#include <vector>

namespace lib {

namespace internal::topological_sort_hpp {
  template <typename Comp>
  constexpr auto invert_compare_function = [](auto lhs, auto rhs) -> bool {
    static_assert(std::is_same_v<decltype(lhs), decltype(rhs)>);
    static_assert(std::is_same_v<decltype(Comp {}(rhs, lhs)), bool>);
    return Comp {}(rhs, lhs);
  };

  template <typename Comp>
  [[nodiscard]] auto queue() {
    if constexpr (std::is_void_v<Comp>) {
      return std::queue<int>();
    } else {
      return std::priority_queue<int,
                                 std::vector<int>,
                                 decltype(invert_compare_function<Comp>)>(invert_compare_function<Comp>);
    }
  }

  template <typename Container>
  [[nodiscard]] std::vector<int> in_degree(const Container& adjacency_list) {
    const int vertices = static_cast<int>(std::size(adjacency_list));
    std::vector<int> res(vertices);
    for (int from = 0; from < vertices; ++from) {
      for (const auto to : adjacency_list[from]) {
        ++res[to];
      }
    }
    return res;
  }
}  // namespace internal::topological_sort_hpp

//! @brief Sort the vertices in the given directed graph in topological order.
//! @tparam Comp Compare function (e.g. std::less<void>)
//! @tparam Container Container type (deduced from parameter)
//! @param adjacency_list Graph in the adjacency list format (i.e. adjacency_list[i] = {nodes adjacent to node i})
//! @return List of the vertices (std::vector<int>) sorted in topological order.
//! @note If a compare function is specified, the result will be further sorted maintaining topological order.
//! @note The length of the result will be less than the number of the vertices if the given graph has a cycle.
//! @note time complexity: O(V + E)       if a compare function is not specified
//! @note time complexity: O(V log V + E) if a compare function is specified
template <typename Comp = void, typename Container>
[[nodiscard]] std::vector<int> topological_sort(const Container& adjacency_list) {
  const int vertices         = static_cast<int>(std::size(adjacency_list));
  std::vector<int> in_degree = internal::topological_sort_hpp::in_degree(adjacency_list);
  auto q                     = internal::topological_sort_hpp::queue<Comp>();

  for (int i = 0; i < vertices; ++i) {
    if (in_degree[i] == 0) {
      q.emplace(i);
    }
  }

  std::vector<int> res;
  res.reserve(vertices);

  while (!q.empty()) {
    int from;
    if constexpr (std::is_void_v<Comp>) {
      from = q.front();
    } else {
      from = q.top();
    }

    q.pop();
    res.emplace_back(from);

    for (const int to : adjacency_list[from]) {
      --in_degree[to];
      if (in_degree[to] == 0) {
        q.emplace(to);
      }
    }
  }

  return res;
}

}  // namespace lib

#endif  // CP_LIBRARY_TOPOLOGICAL_SORT_HPP
