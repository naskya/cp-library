---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/graph/topological_sort/1.test.cpp
    title: test/graph/topological_sort/1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/topological_sort/2.test.cpp
    title: test/graph/topological_sort/2.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Sort the vertices in the given directed graph in topological order.
    links: []
  bundledCode: "#line 1 \"include/graph/topological_sort.hpp\"\n\n//! @file topologocal_sort.hpp\n\
    \n#ifndef CP_LIBRARY_TOPOLOGICAL_SORT_HPP\n#define CP_LIBRARY_TOPOLOGICAL_SORT_HPP\n\
    \n#include <iostream>\n#include <queue>\n#include <type_traits>\n#include <vector>\n\
    \nnamespace lib {\n\nnamespace internal::topological_sort_hpp {\n  template <typename\
    \ Comp>\n  constexpr auto invert_compare_function = [](auto lhs, auto rhs) ->\
    \ bool {\n    static_assert(std::is_same_v<decltype(lhs), decltype(rhs)>);\n \
    \   static_assert(std::is_same_v<decltype(Comp {}(rhs, lhs)), bool>);\n    return\
    \ Comp {}(rhs, lhs);\n  };\n\n  template <typename Comp>\n  [[nodiscard]] auto\
    \ queue() {\n    if constexpr (std::is_void_v<Comp>) {\n      return std::queue<int>();\n\
    \    } else {\n      return std::priority_queue<int,\n                       \
    \          std::vector<int>,\n                                 decltype(invert_compare_function<Comp>)>(invert_compare_function<Comp>);\n\
    \    }\n  }\n\n  template <typename Container>\n  [[nodiscard]] std::vector<int>\
    \ in_degree(const Container& adjacency_list) {\n    const int vertices = static_cast<int>(std::size(adjacency_list));\n\
    \    std::vector<int> res(vertices);\n    for (int from = 0; from < vertices;\
    \ ++from) {\n      for (const auto to : adjacency_list[from]) {\n        ++res[to];\n\
    \      }\n    }\n    return res;\n  }\n}  // namespace internal::topological_sort_hpp\n\
    \n//! @brief Sort the vertices in the given directed graph in topological order.\n\
    //! @tparam Comp Compare function (e.g. std::less<void>)\n//! @tparam Container\
    \ Container type (deduced from parameter)\n//! @param adjacency_list Graph in\
    \ the adjacency list format (i.e. adjacency_list[i] = {nodes adjacent to node\
    \ i})\n//! @return List of the vertices (std::vector<int>) sorted in topological\
    \ order.\n//! @note If a compare function is specified, the result will be further\
    \ sorted maintaining topological order.\n//! @note The length of the result will\
    \ be less than the number of the vertices if the given graph has a cycle.\n//!\
    \ @note time complexity: O(V + E)       if a compare function is not specified\n\
    //! @note time complexity: O(V log V + E) if a compare function is specified\n\
    template <typename Comp = void, typename Container>\n[[nodiscard]] std::vector<int>\
    \ topological_sort(const Container& adjacency_list) {\n  const int vertices  \
    \       = static_cast<int>(std::size(adjacency_list));\n  std::vector<int> in_degree\
    \ = internal::topological_sort_hpp::in_degree(adjacency_list);\n  auto q     \
    \                = internal::topological_sort_hpp::queue<Comp>();\n\n  for (int\
    \ i = 0; i < vertices; ++i) {\n    if (in_degree[i] == 0) {\n      q.emplace(i);\n\
    \    }\n  }\n\n  std::vector<int> res;\n  res.reserve(vertices);\n\n  while (!q.empty())\
    \ {\n    int from;\n    if constexpr (std::is_void_v<Comp>) {\n      from = q.front();\n\
    \    } else {\n      from = q.top();\n    }\n\n    q.pop();\n    res.emplace_back(from);\n\
    \n    for (const int to : adjacency_list[from]) {\n      --in_degree[to];\n  \
    \    if (in_degree[to] == 0) {\n        q.emplace(to);\n      }\n    }\n  }\n\n\
    \  return res;\n}\n\n}  // namespace lib\n\n#endif  // CP_LIBRARY_TOPOLOGICAL_SORT_HPP\n"
  code: "\n//! @file topologocal_sort.hpp\n\n#ifndef CP_LIBRARY_TOPOLOGICAL_SORT_HPP\n\
    #define CP_LIBRARY_TOPOLOGICAL_SORT_HPP\n\n#include <iostream>\n#include <queue>\n\
    #include <type_traits>\n#include <vector>\n\nnamespace lib {\n\nnamespace internal::topological_sort_hpp\
    \ {\n  template <typename Comp>\n  constexpr auto invert_compare_function = [](auto\
    \ lhs, auto rhs) -> bool {\n    static_assert(std::is_same_v<decltype(lhs), decltype(rhs)>);\n\
    \    static_assert(std::is_same_v<decltype(Comp {}(rhs, lhs)), bool>);\n    return\
    \ Comp {}(rhs, lhs);\n  };\n\n  template <typename Comp>\n  [[nodiscard]] auto\
    \ queue() {\n    if constexpr (std::is_void_v<Comp>) {\n      return std::queue<int>();\n\
    \    } else {\n      return std::priority_queue<int,\n                       \
    \          std::vector<int>,\n                                 decltype(invert_compare_function<Comp>)>(invert_compare_function<Comp>);\n\
    \    }\n  }\n\n  template <typename Container>\n  [[nodiscard]] std::vector<int>\
    \ in_degree(const Container& adjacency_list) {\n    const int vertices = static_cast<int>(std::size(adjacency_list));\n\
    \    std::vector<int> res(vertices);\n    for (int from = 0; from < vertices;\
    \ ++from) {\n      for (const auto to : adjacency_list[from]) {\n        ++res[to];\n\
    \      }\n    }\n    return res;\n  }\n}  // namespace internal::topological_sort_hpp\n\
    \n//! @brief Sort the vertices in the given directed graph in topological order.\n\
    //! @tparam Comp Compare function (e.g. std::less<void>)\n//! @tparam Container\
    \ Container type (deduced from parameter)\n//! @param adjacency_list Graph in\
    \ the adjacency list format (i.e. adjacency_list[i] = {nodes adjacent to node\
    \ i})\n//! @return List of the vertices (std::vector<int>) sorted in topological\
    \ order.\n//! @note If a compare function is specified, the result will be further\
    \ sorted maintaining topological order.\n//! @note The length of the result will\
    \ be less than the number of the vertices if the given graph has a cycle.\n//!\
    \ @note time complexity: O(V + E)       if a compare function is not specified\n\
    //! @note time complexity: O(V log V + E) if a compare function is specified\n\
    template <typename Comp = void, typename Container>\n[[nodiscard]] std::vector<int>\
    \ topological_sort(const Container& adjacency_list) {\n  const int vertices  \
    \       = static_cast<int>(std::size(adjacency_list));\n  std::vector<int> in_degree\
    \ = internal::topological_sort_hpp::in_degree(adjacency_list);\n  auto q     \
    \                = internal::topological_sort_hpp::queue<Comp>();\n\n  for (int\
    \ i = 0; i < vertices; ++i) {\n    if (in_degree[i] == 0) {\n      q.emplace(i);\n\
    \    }\n  }\n\n  std::vector<int> res;\n  res.reserve(vertices);\n\n  while (!q.empty())\
    \ {\n    int from;\n    if constexpr (std::is_void_v<Comp>) {\n      from = q.front();\n\
    \    } else {\n      from = q.top();\n    }\n\n    q.pop();\n    res.emplace_back(from);\n\
    \n    for (const int to : adjacency_list[from]) {\n      --in_degree[to];\n  \
    \    if (in_degree[to] == 0) {\n        q.emplace(to);\n      }\n    }\n  }\n\n\
    \  return res;\n}\n\n}  // namespace lib\n\n#endif  // CP_LIBRARY_TOPOLOGICAL_SORT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/graph/topological_sort.hpp
  requiredBy: []
  timestamp: '2021-10-21 19:21:04+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/graph/topological_sort/2.test.cpp
  - test/graph/topological_sort/1.test.cpp
documentation_of: include/graph/topological_sort.hpp
layout: document
title: Topological sort
---

有向グラフを[トポロジカルソート](https://ja.wikipedia.org/wiki/%E3%83%88%E3%83%9D%E3%83%AD%E3%82%B8%E3%82%AB%E3%83%AB%E3%82%BD%E3%83%BC%E3%83%88)する関数が含まれています。

### `topological_sort(adjacency_list)`

隣接リスト(`adjacency_list`)で表される有向グラフを[トポロジカルソート](https://ja.wikipedia.org/wiki/%E3%83%88%E3%83%9D%E3%83%AD%E3%82%B8%E3%82%AB%E3%83%AB%E3%82%BD%E3%83%BC%E3%83%88)し、トポロジカル順に並んだ頂点番号の配列([`std::vector<int>`](https://cpprefjp.github.io/reference/vector/vector.html))を返します。与えられたグラフに閉路が含まれる場合、返される配列の長さは元のグラフの頂点数よりも小さくなります。

### `topological_sort<Comp>(adjacency_list)`

2 つの頂点番号を引数にとり、第一引数が第二引数よりも真に小さいかを返す比較関数 `Comp` を渡してソートすることもできます。このとき、返される配列はトポロジカル順を維持したままなるべく(与えられた比較関数で頂点同士を比較する場合に)[辞書式順序](https://ja.wikipedia.org/wiki/%E8%BE%9E%E6%9B%B8%E5%BC%8F%E9%A0%86%E5%BA%8F)が小さいものとなります。
