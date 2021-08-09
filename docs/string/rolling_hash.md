---
title: Rolling hash
documentation_of: //include/string/rolling_hash.hpp
---

ハッシュ値を前計算しておくことで文字列や配列の大量の比較を定数時間で行うための `rolling_hash` クラスと `single_hash` 構造体が定義されています。実装は[安全で爆速なRollingHashの話](https://qiita.com/keymoon/items/11fac5627672a6d6a9f6)を参考にしています。

文字列(`std::string`)以外のコンテナ(`std::vector<int>` 等)でもハッシュ値を計算する事が可能です。以下では便宜上、計算の入力に用いるコンテナを文字列と呼びます。

---

## `rolling_hash` クラス

`rolling_hash` クラスは元となる文字列の(元の文字列自体を含む)連続部分文字列のハッシュ値を高速に計算するための情報を保持するクラスです。このクラスは連続部分文字列のハッシュ値の計算のためにあり、文字列のハッシュ値そのものを表現するためのものではありません。文字列のハッシュ値は `single_hash` 構造体で表現されます。

以下「ハッシュ値」は `single_hash` 型のオブジェクトを指します。

つまり `rolling_hash` 型のオブジェクトは様々な情報を保持した「未分化な状態」で、そこから連続部分文字列の情報を取り出すことで特定の文字列に対するハッシュ値を取得します。連続部分文字列のハッシュ値を計算する必要が無い場合、[後述](https://naskya.github.io/cp-library/include/string/rolling_hash.hpp#single_hash-%E6%A7%8B%E9%80%A0%E4%BD%93)の方法で直接ハッシュ値を取得するとよいです。

### 構築

文字列を `get_rolling_hash` 関数に渡して使います。戻り値の型は `rolling_hash_t<コンテナの型>` と同じです。

```cpp
// 文字列のローリングハッシュを取得
std::string S = "Hello";
const auto S_rhash = lib::get_rolling_hash(S);

// 型名が必要な場合は rolling_hash_t を用いる
std::vector<lib::rolling_hash_t<std::string>> rhash;
rhash.emplace_back(S_rhash);  // OK

// 文字列以外のローリングハッシュも取得可能
std::vector<int> A {1, 2, 3};
const auto A_rhash = lib::get_rolling_hash(A);
```

### メンバ関数

#### `size()`

元の文字列の長さを返します。

#### `substring(start, length)`

C++ の標準ライブラリの `std::string` のメンバ関数 `substr` と同様に、連続部分文字列の開始位置 `start` と長さ `length` を指定することで元の文字列に含まれる連続部分文字列のハッシュ値を取得します。`length` を省略すると文字列の末尾までの連続部分文字列を指定したことになります。戻り値の型は `single_hash_t<コンテナの型>` と同じです。

#### `whole_string()`

文字列全体のハッシュ値(`substring(0)` や `substring(0, size())` と同じ値)を返します。戻り値の型は `single_hash_t<コンテナの型>` と同じです。

```cpp
const std::string S = "0123456789";
const auto S_rhash  = lib::get_rolling_hash(S);

const auto a = S_rhash.substring(5);     // 文字列 "56789" のハッシュ値 (`single_hash` 型のオブジェクト)
const auto b = S_rhash.substring(2, 3);  // 文字列 "234" のハッシュ値
const auto c = S_rhash.whole_string();   // 文字列 "0123456789" のハッシュ値
```

---

## `single_hash` 構造体

文字列のハッシュ値を保持する構造体です。この構造体のオブジェクトは文字列のハッシュ値と長さの情報だけを持ちます。そのため `single_hash` 構造体のオブジェクトからその文字列に含まれる連続部分文字列のハッシュ値の計算をすることはできません。

### 構築

連続部分文字列のハッシュ値を計算する必要が無く、文字列のハッシュ値を直接取得したい時は `get_single_hash` 関数を使います。戻り値の型は `single_hash_t<コンテナの型>` と同じです。

```cpp
// 文字列のハッシュ値を取得
std::string S = "good";
const auto S_hash = lib::get_single_hash(S);
// const auto S_hash = lib::get_rolling_hash(S).whole_string(); と同じ

// 型名が必要な場合は single_hash_t を用いる
std::vector<lib::single_hash_t<std::string>> hash;
hash.emplace_back(S_hash);  // OK

// 文字列以外のハッシュ値も取得可能
std::vector<int> A {9, 8, 7};
const auto A_hash = lib::get_single_hash(A);
```

### 演算子

以下の演算子がオーバーロードされています。

- `==`
- `!=`
- `+`
- `+=`

#### `operator==`

両辺の `single_hash` 型のオブジェクトが等しいか定数時間で比較します。文字列の長さの比較とハッシュ値の比較が行われ、どちらも等しい時に `true` を、そうでないときに `false` を返します。

```cpp
const std::string A = "This";
const std::string B = "is";
const bool check = (lib::get_rolling_hash(A).substring(2) == lib::get_single_hash(B));  // true
```

マクロ `CP_LIBRARY_DEBUG_LEVEL` が $2$ 以上の値として定義されている場合には線形時間を掛けて元の文字列を直接比較し、ハッシュ値が等しいのに文字列が異なっている状態(ハッシュ値の衝突)を検知した場合にそれを報告して異常終了します。

#### `operator!=`

`A != B` は `operator==` を呼び出し、`!(A == B)` と同じ値を返します。

#### `operator+`

文字列を結合します。

```cpp
const std::string A = "This ";
const std::string B = "is";
const std::string C = "This is";

const auto A_hash = lib::get_single_hash(A);
const auto B_hash = lib::get_single_hash(B);
const auto C_hash = lib::get_single_hash(C);

const bool check = ((A_hash + B_hash) == C_hash);  // true
```

#### `operator+=`

文字列を末尾に加えます。

```cpp
const std::string A = "This ";
const std::string B = "is";
const std::string C = "This is";

const auto A_hash = lib::get_single_hash(A);
const auto B_hash = lib::get_single_hash(B);
const auto C_hash = lib::get_single_hash(C);

A_hash += B_hash;

const bool check = (A_hash == C_hash);  // true
```

### メンバ関数

#### `size()`

文字列の長さを返します。

#### `hash_value()`

ハッシュ値を返します。戻り値は `std::uint_least64_t` がいくつか入ったタプル (`std::tuple<std::uint_least64_t, std::uint_least64_t, ...>`) です。比較判定などはこの関数でハッシュ値を取得しなくても行えるので基本的には使用する必要の無い関数です。

#### `debug_print()`

マクロ `CP_LIBRARY_DEBUG_LEVEL` が $1$ 以上の値として定義されている場合、標準エラー出力にデバッグ情報(`hash_value()` の返す値)を出力します。
マクロ `CP_LIBRARY_DEBUG_LEVEL` が $2$ 以上の値として定義されている場合、文字列の内容も加えて出力します。

コンパイル時にこのマクロを定義する場合には

```sh
g++ -std=c++17 -DCP_LIBRARY_DEBUG_LEVEL=1 main.cpp
```

のように、`-DCP_LIBRARY_DEBUG_LEVEL=` に続けて値を指定します。

---
