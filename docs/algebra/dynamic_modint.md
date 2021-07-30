---
title: Modint (for runtime constant modulo)
documentation_of: //include/algebra/dynamic_modint.hpp
---

`dynamic_modint` 構造体が定義されています。

## `dynamic_modint` 構造体

基本的に `static_modint` と同じように扱えるので、ここに載っていない内容は [`static_modint` の説明](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp)を参照してください。

### クラステンプレート

`dynamic_modint` 構造体は 2 つのテンプレート引数を取ります。**グローバルに**整数型の変数を宣言して、以下のようにして使います。

```cpp
int MOD;
using mint = lib::dynamic_modint<decltype(MOD), &MOD>;
```

上記の例では、`mint` 型の変数は自動的に `MOD` で割った余りが計算される整数となります。

この型の変数を宣言する前に、必ず `MOD` の値を標準入力から入力するなどして設定するようにしてください。そうでないと、0 での除算が発生します。

`static_modint` とは異なり、変数 `MOD` (`MOD` という名前である必要はありません)は `long long` 型にすることもできます(ただし、あまりテストされていません)。
