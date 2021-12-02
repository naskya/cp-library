---
title: Segment tree
documentation_of: //include/data_structure/segment_tree.hpp
---

配列に対して以下のクエリが対数時間で行えるデータ構造である `segment_tree` クラスと、その制御に用いる `no_range_query_in_this_scope` クラスが定義されています。[`binary_indexed_tree`](https://naskya.github.io/cp-library-cpp/include/data_structure/binary_indexed_tree.hpp) や [`sparse_table`](https://naskya.github.io/cp-library-cpp/include/data_structure/sparse_table.hpp) が利用できる場合、そちらを利用した方が高速に動作することが期待できます。

- 配列の一つの要素の値を更新する
- 配列の一つの要素の値を取得する
- 配列の区間積を取得する

ここでいう「区間積」とは、配列のある区間内に二項演算を繰り返し適用した結果です。例えば二項演算を加算とすると、配列 $\{a_1,\, a_2,\, a_3,\, a_4,\, a_5,\, a_6\}$ の $a_2$ から $a_4$ までの区間の区間積は $a_2 + a_3 + a_4$ です。二項演算は単位元が存在して結合法則を満たすものであれば構いません。例えば掛け算・最小値を求める演算・最大値を求める演算等を使うこともできます。

---

### クラステンプレート

`segment_tree` クラスは 2 つの省略可能なテンプレート引数をとります。

```cpp
lib::segment_tree  // 1.
lib::segment_tree<int>  // 2.
lib::segment_tree<lib::static_modint<1000000007>>  // 3.
lib::segment_tree<int, std::bit_xor<>>  // 4.
```

1. テンプレート引数を省略した場合、要素の型は long long で二項演算は加算 (+) となります。
1. 第一引数で要素の型を指定できます。この場合要素の型は int で二項演算は加算 (+) となります。
1. 要素の型は組み込み型でなくてもよいです。この場合要素の型は [`lib::static_modint<1000000007>`](https://naskya.github.io/cp-library-cpp/include/algebra/static_modint.hpp) で二項演算は加算 (+) となります。
1. 第二引数で二項演算を指定できます。この場合要素の型は int で二項演算は bitwise xor (^) となります。後述の通り他にも二項演算を変更する方法があります。

### コンストラクタ

```cpp
std::vector<int> v {1, 2, 3, 4, 5};

lib::segment_tree tree_1(N);      // 1.
lib::segment_tree tree_2(N, 10);  // 2.
lib::segment_tree tree_3(v);      // 3.

lib::segment_tree<long long, std::bit_xor<>> tree_4(N);      // 4.
lib::segment_tree<long long, std::bit_xor<>> tree_5(N, 10);  // 5.
lib::segment_tree<long long, std::bit_xor<>> tree_6(v);      // 6.

// 最小値を返す演算
const auto func_min = [](const long long x, const long long y) constexpr { return std::min(x, y); };
// 最小値を返す演算の単位元
constexpr long long id_min = 1000000000000000005LL;

lib::segment_tree tree_7(N, id_min, func_min);       // 7.
lib::segment_tree tree_8(N, 500, id_min, func_min);  // 8.
lib::segment_tree tree_9(v, id_min, func_min);       // 9.

// 引数の部分にラムダ式を直接書いても良い
// lib::segment_tree tree_9 (v, 1000000000000000005LL,
//                           [](long long x, long long y) { return std::min(x, y); });
```

1. 要素数 $N$ の、全ての要素が $0$ で初期化された、二項演算を加算とした [segment tree](https://en.wikipedia.org/wiki/Segment_tree) を構築します。
1. 要素数 $N$ の、全ての要素が $10$ で初期化された、二項演算を加算とした [segment tree](https://en.wikipedia.org/wiki/Segment_tree) を構築します。
1. $v$ の要素で初期化された、$v$ と同じ要素数の、二項演算を加算とした [segment tree](https://en.wikipedia.org/wiki/Segment_tree) を構築します。
1. 要素数 $N$ の、全ての要素が $0$ で初期化された、二項演算を bitwise xor とした [segment tree](https://en.wikipedia.org/wiki/Segment_tree) を構築します。
1. 要素数 $N$ の、全ての要素が $10$ で初期化された、二項演算を bitwise xor とした [segment tree](https://en.wikipedia.org/wiki/Segment_tree) を構築します。
1. $v$ の要素で初期化された、$v$ と同じ要素数の、二項演算を bitwise xor とした [segment tree](https://en.wikipedia.org/wiki/Segment_tree) を構築します。
1. 要素数 $N$ の、全ての要素が `id_min` で初期化された、二項演算を最小値をとる演算とした [segment tree](https://en.wikipedia.org/wiki/Segment_tree) を構築します。
1. 要素数 $N$ の、全ての要素が $500$ で初期化された、二項演算を最小値をとる演算とした [segment tree](https://en.wikipedia.org/wiki/Segment_tree) を構築します。
1. $v$ の要素で初期化された、$v$ と同じ要素数の、二項演算を最小値をとる演算とした [segment tree](https://en.wikipedia.org/wiki/Segment_tree) を構築します。

二項演算として関数へのポインタを渡すこともできます。

```cpp
unsigned max(unsigned x, unsigned y) {
  return (x >= y) ? x : y;
}

int main() {
  int N;
  std::cin >> N;

  lib::segment_tree tree(N, 0u, &max);  // OK
  //                            ^^^^
}
```

### メンバ関数

#### `size()`

要素数を返します。

#### `add(i, x)`

$i$ 番目 (0-indexed) の要素に $x$ を加算します。

#### `prod(l, r)`

半開区間 $[l, r)$ (0-indexed) に含まれる要素の区間積を返します。

#### `all_prod(l, r)`

全要素についての区間積を返します (`prod(0, size())` と同じ値を返します)。

#### `get(i)`

$i$ 番目 (0-indexed) の要素の値を返します。

#### `set(i, x)`

$i$ 番目 (0-indexed) の要素の値を $x$ にします。

#### `debug_print()`

[デバッグレベル](https://naskya.github.io/cp-library-cpp/about#cp_library_debug_level-%E3%83%9E%E3%82%AF%E3%83%AD)が $1$ 以上のとき、標準エラー出力にデバッグ情報(配列の内容)を出力します。

---

以下は処理をほんのり高速化させるためのメンバ関数です。使い方を間違えると [`CP_LIBRARY_ASSERT`](https://naskya.github.io/cp-library-cpp/about#%E3%81%9D%E3%81%AE%E4%BB%96%E3%81%AE%E3%83%9E%E3%82%AF%E3%83%AD) マクロによって異常終了するか、正しくない計算結果が返ります。

これらの関数の使用を検討する場合、他に適したデータ構造が無いかを考えてください。

#### `lock()`

`set` 関数や `add` 関数で要素を変更した時に、その変更が自動的に親ノードに**伝播されない**ようにします。そのため `lock()` を行った後には (`unlock()` を行うまでは) 区間積は取得できなくなります。この関数を呼び、`unlock()` を行わずにもう一度この関数を呼ぶと [`CP_LIBRARY_ASSERT`](https://naskya.github.io/cp-library-cpp/about#%E3%81%9D%E3%81%AE%E4%BB%96%E3%81%AE%E3%83%9E%E3%82%AF%E3%83%AD) マクロによって異常終了します。

#### `unlock()`

`set` 関数や `add` 関数で要素を変更した時に、その変更が自動的に親ノードに**伝播される**ようにします。`lock()` を呼んでいない状態でこの関数を呼ぶと [`CP_LIBRARY_ASSERT`](https://naskya.github.io/cp-library-cpp/about#%E3%81%9D%E3%81%AE%E4%BB%96%E3%81%AE%E3%83%9E%E3%82%AF%E3%83%AD) マクロによって異常終了します。

この関数は内部に保持されている `locked` という変数の値を `false` にセットするだけなので、この関数を呼んだだけでは変更が親ノードへ伝播されないことに注意してください。

#### `propagate(i)`

$i$ 番目の要素の変更を親ノードに伝播します。変更が自動的に親ノードに伝播されない状態で行った変更を手動で反映させるために使います。

#### `propagate_all()`

全ての要素の変更を親ノードに伝播します。変更が自動的に親ノードに伝播されない状態で行った変更を手動で反映させるために使います。

#### `propagate_all_and_unlock()`

`propagate_all()` と `unlock()` を呼びます。

#### `is_locked()`

変更が自動的に親ノードに**伝播されない**状態になっているかどうかを返します。

---

`lock()` や `unlock()` を直接使用するとバグの原因となるので、`no_range_query_in_this_scope` クラスを通して使用するとよいです。

`no_range_query_in_this_scope` クラスのコンストラクタで自動的に `lock()` が呼ばれ、デストラクタで自動的に `propagate_all_and_unlock()` が呼ばれます。

```cpp
lib::segmant_tree tree(N);

{
  // コンストラクタが呼ばれ、tree は変更が自動的に親ノードに伝播されない状態になる
  lib::no_range_query_in_this_scope query_lock(tree);

  // 大量の変更クエリ (ここで区間積の取得はできないが、get() を使うことはできる)
  for (int i = 0; i < Q; ++i)
    tree.set(x[i], y[i]);

  // スコープを抜けるのでデストラクタが呼ばれ、tree への変更が適用される
}
```

---
