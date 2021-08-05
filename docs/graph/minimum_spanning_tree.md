---
title: Minimun spanning tree
documentation_of: //include/graph/minimum_spanning_tree.hpp
---

グラフの[最小全域木](https://ja.wikipedia.org/wiki/%E5%85%A8%E5%9F%9F%E6%9C%A8#%E6%9C%80%E5%B0%8F%E5%85%A8%E5%9F%9F%E6%9C%A8)を求める関数が定義されています。

---

### `minimum_spanning_tree<TotalCostType>(N, edge_list)`

$N$ 頂点の、`edge_list` に含まれる辺を持つグラフの最小全域木を[Kruskal 法](https://ja.wikipedia.org/wiki/%E3%82%AF%E3%83%A9%E3%82%B9%E3%82%AB%E3%83%AB%E6%B3%95)によって求めます。

#### テンプレート引数

- `TotalCostType` - コストの総和の型
  - 辺のコストを `int` 型で保持しているがコストの和が `int` 型で表せる範囲を超えている場合にはここで `long long` 型を指定すればよいです。

#### 引数

- `N` - グラフの頂点数
- `edge_list` - 辺のリスト
  - `std::tuple` のリストです。頂点 $u$ と頂点 $v$ を繋ぐコスト $c$ の辺を `std::tuple(u, v, c)` として表します。

#### 戻り値

最小全域木の辺のリスト(`edge_list` と同じ形式)と辺のコストの総和(`TotalCostType` 型)をこの順に保持した `std::pair` 型の値

### `minimum_spanning_tree<TotalCostType>(adjacency_list)`

隣接リスト `adjacency_list` で表されるグラフの最小全域木を[Prim 法](https://ja.wikipedia.org/wiki/%E3%83%97%E3%83%AA%E3%83%A0%E6%B3%95)によって求めます。

#### テンプレート引数

- `TotalCostType` - コストの総和の型
  - 辺のコストを `int` 型で保持しているがコストの和が `int` 型で表せる範囲を超えている場合にはここで `long long` 型を指定すればよいです。

#### 引数

- `N` - グラフの頂点数
- `adjacency_list` - 隣接リスト
  - 頂点 $u$ と頂点 $v$ を繋ぐコスト $c$ の辺が有る場合、`adjacency_list[u]` の中に `std::pair(v, c)` が含まれるようにします。

#### 戻り値

最小全域木の隣接リスト(`adjacency_list` と同じ形式)と辺のコストの総和(`TotalCostType` 型)をこの順に保持した `std::pair` 型の値

### `minimum_spanning_tree<TotalCostType>(adjacency_matrix, infinity)`

隣接行列 `adjacency_matrix` で表されるグラフの最小全域木を[Prim 法](https://ja.wikipedia.org/wiki/%E3%83%97%E3%83%AA%E3%83%A0%E6%B3%95)によって求めます。

#### テンプレート引数

- `TotalCostType` - コストの総和の型
  - 辺のコストを `int` 型で保持しているがコストの和が `int` 型で表せる範囲を超えている場合にはここで `long long` 型を指定すればよいです。

#### 引数

- `N` - グラフの頂点数
- `adjacency_matrix` - 隣接リスト
  - 頂点 $u$ と頂点 $v$ を繋ぐコスト $c$ の辺が有る場合、`adjacency_matrix[u][v] = c` とし、辺が無い場合は `adjacency_matrix[u][v] = infinity` とします。
- `infinity` - 辺が無いことを表す十分大きい値

#### 戻り値

最小全域木の隣接行列(`adjacency_matrix` と同じ形式)と辺のコストの総和(`TotalCostType` 型)をこの順に保持した `std::pair` 型の値

---
