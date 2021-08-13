---
title: Binary indexed tree
documentation_of: //include/data_structure/binary_indexed_tree.hpp
---

数の配列に対して以下のクエリが対数時間で行えるデータ構造である `binary_indexed_tree` クラスが定義されています。

- 配列の一つの要素の値を更新する
- 配列の一つの要素の値を取得する
- 配列の区間内に含まれる全ての要素に同じ値を加算する
- 配列の区間内に含まれる要素の和を取得する

---

### クラステンプレート

`binary_indexed_tree` クラスは要素の型を表す 1 つのテンプレート引数をとります。

```cpp
lib::binary_indexed_tree<int>  // int 型の要素を持つ binary indexed tree
```

要素の型には `int`, `long long` 等の整数型の他に、`double` 等の浮動小数点数型や [`__int128`](https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html), [`cpp_int`](https://www.boost.org/doc/libs/1_76_0/libs/multiprecision/doc/html/boost_multiprecision/tut/ints/cpp_int.html), [`static_modint`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) 等の加減算の演算子が適切に定義された型を用いることができます。

### コンストラクタ

```cpp
std::vector<int> v {1, 2, 3, 4, 5};

lib::binary_indexed_tree<int> tree_1(N);      // 1.
lib::binary_indexed_tree<int> tree_2(N, 10);  // 2.
lib::binary_indexed_tree<int> tree_3(v);      // 3.
```

1. 要素数 $N$ の、全ての要素が $0$ で初期化された [binary indexed tree](https://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A7%E3%83%8B%E3%83%83%E3%82%AF%E6%9C%A8) を構築します。
1. 要素数 $N$ の、全ての要素が $10$ で初期化された [binary indexed tree](https://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A7%E3%83%8B%E3%83%83%E3%82%AF%E6%9C%A8) を構築します。
1. $v$ の要素で初期化された、$v$ と同じ要素数の [binary indexed tree](https://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A7%E3%83%8B%E3%83%83%E3%82%AF%E6%9C%A8) を構築します。

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

[デバッグレベル](https://naskya.github.io/cp-library/about#cp_library_debug_level-%E3%83%9E%E3%82%AF%E3%83%AD)が $1$ 以上のとき、標準エラー出力にデバッグ情報(配列の内容)を出力します。

---
