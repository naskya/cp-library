---
title: Union-find
documentation_of: //include/data_structure/union_find.hpp
---

AtCoder Library の [dsu.hpp](https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp) を元にしています。[素集合を管理するデータ構造](https://ja.wikipedia.org/wiki/%E7%B4%A0%E9%9B%86%E5%90%88%E3%83%87%E3%83%BC%E3%82%BF%E6%A7%8B%E9%80%A0)である `union_find` クラスが定義されています。

---

### コンストラクタ

```cpp
lib::union_find uf(N);
```

で、$N$ 頂点 $0$ 辺の無向グラフを構築します。

### メンバ関数

#### `size()`

頂点の数を返します。

#### `parent(i)`

$i$ 番目 (0-indexed) の頂点が属する集合(連結成分)の代表元の番号を返します。

#### `same(i, j)`

$i$ 番目 (0-indexed) の頂点と $j$ 番目 (0-indexed) の頂点が同じ集合に属している(連結である)かを返します。

#### `group_size(i)`

$i$ 番目 (0-indexed) の頂点が属する集合(連結成分)に属する頂点の数を返します。

#### `merge(i, j)`

$i$ 番目 (0-indexed) の頂点と $j$ 番目 (0-indexed) の頂点が属する集合をマージします。頂点間に辺を張るとも言えます。この操作によってグラフに変更が起きた場合は `true` を、元々 $i$ 番目の頂点と $j$ 番目 の頂点が連結であった場合には `false` を返します。

#### `groups()`

グラフを連結成分に分け、その情報を返します(AtCoder Library の dsu.hpp と同じ内容です)。

#### `debug_print()`

`ONLINE_JUDGE` が定義されていない場合、標準エラー出力にデバッグ情報(`groups()` の内容)を出力します。`ONLINE_JUDGE` の定義の有無で切り替えるよりも自分のローカルの環境でのみ設定したマクロの定義の有無で切り替えた方が良いと思いますが、人によってその内容は変わるのでここではオンラインジャッジであるかどうかの判定に `ONLINE_JUDGE` を用いています。この部分を別のマクロに書き換えて使っても構いません。

---
