---
title: Modint (for runtime constant modulo)
documentation_of: //include/algebra/dynamic_modint.hpp
---

「$M$ で割った余りを求めよ」等の要求がある問題で使える `dynamic_modint` 構造体が定義されています。コンパイル時に $M$ の値が確定している場合には [`static_modint`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) を使用してください。基本的に [`static_modint`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) と同じように扱えるので、ここに載っていない内容は [`static_modint`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) の説明を参照してください。

---

### クラステンプレート

`dynamic_modint` 構造体は 2 つのテンプレート引数を取ります。**グローバルに**整数型の変数を宣言して、以下のようにして使います。

```cpp
int MOD;
using mint = lib::dynamic_modint<decltype(MOD), &MOD>;
```

上記の例では、`mint` 型の変数は自動的に `MOD` で割った余りが計算される整数となります。

この型の変数を宣言(宣言時に初期化も行われます)する前に、必ず `MOD` の値を標準入力から入力するなどして設定するようにしてください。そうでないと、$0$ での除算が発生します(厳密には、何も値を与えずに宣言するだけなら値が $0$ で初期化されるだけで問題は無いのでどうしてもグローバルに置きたい等の理由により `MOD` の値が定まる前に宣言を行いたいならそれをしても構いません。しかし `mint x = 200;` のように値を与えてはいけません)。

[`static_modint`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) とは異なり、変数 `MOD` (`MOD` という名前である必要はありません)は `long long` 型にすることもできます(ただし、あまりテストされていません)。

---
