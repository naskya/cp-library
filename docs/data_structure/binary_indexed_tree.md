---
title: Binary indexed tree
documentation_of: //include/data_structure/binary_indexed_tree.hpp
---

`binary_indexed_tree` クラスが定義されています。

## `binary_indexed_tree` クラス

区間一様加算の機能がついた [Binary indexed tree](https://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A7%E3%83%8B%E3%83%83%E3%82%AF%E6%9C%A8) です。

### 型テンプレート

`binary_indexed_tree` クラスは要素の型を表す 1 つのテンプレート引数をとります。

```C++
lib::binary_indexed_tree<type>
```

要素の型には `int`, `long long` 等の整数型の他に、`double` 等の浮動小数点数型や `__int128`, [`cpp_int`](https://www.boost.org/doc/libs/1_76_0/libs/multiprecision/doc/html/boost_multiprecision/tut/ints/cpp_int.html), [`lib::static_modint<1000000007>`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) 等の加減算の演算子が適切に定義された型を用いることができます。

### コンストラクタ

```C++
lib::binary_indexed_tree<int> tree_1(N);     // 1.
lib::binary_indexed_tree<int> tree_2(N, x);  // 2.

std::vector<int> v {1, 2, 3, 4, 5};
lib::binary_indexed_tree<int> tree_3(v);  // 3.
```

1. $N$ 要素の Binary indexed tree を構築します。
1. $N$ 要素で、全ての要素が $x$ で初期化された Binary indexed tree を構築します。
1. $v$ の要素で初期化された、$v$ と同じ要素数の Binary indexed tree を構築します。

### メンバ関数

#### `size()`

要素数を返します。

#### `add(i, x)`

$i$ 番目 (0-indexed) の要素に $x$ を加算します。

#### `uniform_add(l, r, x)`

半開区間 $[l, r)$ (0-indexed) に含まれる全ての要素に $x$ を加算します。

#### `sum(l, r)`

半開区間 $[l, r)$ (0-indexed) に含まれる要素の総和を返します。

#### `get(i)`

$i$ 番目 (0-indexed) の要素の値を返します。

#### `set(i, x)`

$i$ 番目 (0-indexed) の要素の値を $x$ にします。


#### `debug_print()`

標準エラー出力にデバッグ情報を出力します。
