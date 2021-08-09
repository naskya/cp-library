# このリポジトリについて

私が競技プログラミングのコンテストで使用するために用意したライブラリの置き場です。競技プログラミングの問題の C++17 による解答コード中にコピーして使用することを想定しています。

---

## 使い方

全てのファイルは単体で完結するようになっています。ただし、中には組み合わせて使うことができるものもあります。

ファイル内で定義される関数・変数・クラス・型エイリアス等は全て `namespace lib` の中に入っています。そのため、使用するには `lib::binary_search` のように識別子の先頭に `lib::` をつける必要があります。

これは、ファイルの内容を詳しく知らなくてもライブラリを貼って `lib::` と打ち込むと使うべきものがエディタによってサジェストされることを期待しているためです。`using namespace lib;` を書くと `lib::` を書かなくてもよくなりますが、標準ライブラリ等に含まれる他の識別子と名前が衝突しないことは保証しません。

`namespace lib::internal` には、実装時に内部で必要になったけれど外部からいじることはないもののみが含まれています。そのため、エディタに `lib::` と打って、続けて入力するものの候補に `internal::` が現れた場合はそれを無視してください。

---

## `CP_LIBRARY_DEBUG_LEVEL` マクロ

`CP_LIBRARY_DEBUG_LEVEL` が定義されている場合、その値に応じてデバッグ用の機能が有効になります。現在提供されている機能は以下の通りです。

### `CP_LIBRARY_DEBUG_LEVEL >= 1` が満たされるとき

- [`static_modint`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) や [`dynamic_modint`](https://naskya.github.io/cp-library/include/algebra/dynamic_modint.hpp) 型の値に対して一部の演算子(`<, <=, >, >=` 等)を用いた場合に警告が出るようになります。
- [階乗・順列の数・二項係数・多項係数を計算する関数](https://naskya.github.io/cp-library/include/combinatorics/factorial.hpp)の引数に $0$ 以下の数を与えたときなどに警告が出るようになります。
- [`binary_indexed_tree`](https://naskya.github.io/cp-library/include/data_structure/binary_indexed_tree.hpp), [`segment_tree`](https://naskya.github.io/cp-library/include/data_structure/segment_tree.hpp), [`union_find`](https://naskya.github.io/cp-library/include/data_structure/union_find.hpp), [`single_hash`](https://naskya.github.io/cp-library/include/string/rolling_hash.hpp#single_hash-%E6%A7%8B%E9%80%A0%E4%BD%93) の `debug_print` 関数の出力が表示されるようになります。
- [最小全域木を求める関数](https://naskya.github.io/cp-library/include/graph/minimum_spanning_tree.hpp)に空のグラフを与えたときに警告が出るようになります。
- [連長圧縮をする関数](https://naskya.github.io/cp-library/include/string/run_length_encoding.hpp)に空の配列が与えられたときに警告が出るようになります。

### `CP_LIBRARY_DEBUG_LEVEL >= 2` が満たされるとき

- [`single_hash`](https://naskya.github.io/cp-library/include/string/rolling_hash.hpp#single_hash-%E6%A7%8B%E9%80%A0%E4%BD%93) の比較演算で、定数時間でのハッシュ値の比較だけでなく線形時間を掛けて元の配列の内容の比較も行われるようになります。これによりハッシュ値の衝突が検出された場合、そのことを報告します。
- [`single_hash`](https://naskya.github.io/cp-library/include/string/rolling_hash.hpp#single_hash-%E6%A7%8B%E9%80%A0%E4%BD%93) の `debug_print` 関数で元の配列の内容も出力されるようになります。

コンパイル時にこのマクロを定義する場合には

```sh
g++ -std=c++17 -DCP_LIBRARY_DEBUG_LEVEL=1 main.cpp
```

のように、`-DCP_LIBRARY_DEBUG_LEVEL=` に続けて値を指定します。

---

## その他のマクロ

ライブラリの中で `assert` マクロを用いる際、必ず

```cpp
#include <cassert>

#ifndef O_assert
//! @brief Assert macro
#  define O_assert(...) assert(__VA_ARGS__)
#  define O_assert_not_defined
#endif

namespace lib {

/* 関数の定義など */

}

#ifdef O_assert_not_defined
#  undef O_assert
#  undef O_assert_not_defined
#endif
```

のようにして、`assert` ではなく `O_assert` を用いるようにしています。そのまま使うと通常の `assert` マクロと同じ挙動となります。

マクロをカスタマイズしたい場合には、ライブラリよりも上の行で独自の `O_assert` マクロを定義してください。`O_assert` が定義されている場合、そちらのマクロが使用されます。

他にも警告を出力する `warn` マクロやエラーメッセージを出力して異常終了する `err_and_exit` マクロが同様に定義されています。カスタマイズしたい場合には、ライブラリよりも上の行で独自のものを定義してください。
