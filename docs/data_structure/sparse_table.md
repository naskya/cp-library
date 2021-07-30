---
title: Sparse table
documentation_of: //include/data_structure/sparse_table.hpp
---

`sparse_table` クラスが定義されています。

## `sparse_table` クラス

要素が変化しない配列を格納し、結合法則と冪等性を満たす演算(最小値, 最大値, 最小公倍数, 最大公約数 等)の区間積を高速に求めることができるデータ構造 (sparse table) です。

### コンストラクタ

```C++
std::vector<int> v {1, 2, 3, 4, 5, 6};
const auto lcm = [](const int x, const int y) constexpr -> int { return std::lcm(x, y); };

lib::sparse_table t1(v, lcm);  // 1.
lib::sparse_table<long long, decltype(lcm)> t2(v, lcm);  // 2.
```

1. 配列と関数オブジェクトを受け取って sparse table を構築します。
1. 最小公倍数のように関数が返す値が配列の要素よりも大きくオーバーフローの恐れがある場合等には(より大きな値を表現できる)要素の型を明示して構築をすることができます。

### メンバ関数

#### `size()`

配列の要素数を返します。

#### `get(i)`

$i$ 番目 (0-indexed) の要素の値を返します。

#### `query(l, r)`

半開区間 $[l, r)$ (0-indexed) に含まれる要素に対して演算を作用させた結果(区間積)を返します。
