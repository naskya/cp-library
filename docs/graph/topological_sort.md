---
title: Topological sort
documentation_of: //include/graph/tolopogical_sort.hpp
---

有向グラフを[トポロジカルソート](https://ja.wikipedia.org/wiki/%E3%83%88%E3%83%9D%E3%83%AD%E3%82%B8%E3%82%AB%E3%83%AB%E3%82%BD%E3%83%BC%E3%83%88)する関数が含まれています。

### `tolopogical_sort(adjacency_list)`

隣接リスト(`adjacency_list`)で表される有向グラフを[トポロジカルソート](https://ja.wikipedia.org/wiki/%E3%83%88%E3%83%9D%E3%83%AD%E3%82%B8%E3%82%AB%E3%83%AB%E3%82%BD%E3%83%BC%E3%83%88)し、トポロジカル順に並んだ頂点番号の配列([`std::vector<int>`](https://cpprefjp.github.io/reference/vector/vector.html))を返します。与えられたグラフに閉路が含まれる場合、返される配列の長さは元のグラフの頂点数よりも小さくなります。

### `tolopogical_sort<Comp>(adjacency_list)`

2 つの頂点番号を引数にとり、第一引数が第二引数よりも真に小さいかを返す比較関数 `Comp` を渡してソートすることもできます。このとき、返される配列はトポロジカル順を維持したままなるべく(与えられた比較関数で頂点同士を比較する場合に)[辞書式順序](https://ja.wikipedia.org/wiki/%E8%BE%9E%E6%9B%B8%E5%BC%8F%E9%A0%86%E5%BA%8F)が小さいものとなります。
