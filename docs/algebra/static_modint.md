---
title: Modint (for compile-time constant modulo)
documentation_of: //include/algebra/static_modint.hpp
---

「1000000007 で割った余りを求めよ」等の要求がある問題で使える `static_modint` 構造体が定義されています。演算子オーバーロードによって四則演算を行った時に指定された数で割った余りが自動的に計算されます。何で割った余りを求めるかがコンパイル時に確定しない場合(標準入力から与えられる等)には [`dynamic_modint`](https://naskya.github.io/cp-library/include/algebra/dynamic_modint.hpp) を使用してください。

---

### クラステンプレート

`static_modint` 構造体は 1 つの [`std::int_least32_t`](https://cpprefjp.github.io/reference/cstdint/int_least32_t.html) 型のテンプレート引数をとります。以下のように型エイリアスを宣言して使うとよいです。

```cpp
using mint = lib::static_modint<1000000007>;
```

計算の高速化のために、`static_modint<M>` 型の 2 つの値を足し合わせても(剰余を計算する前の時点で)オーバーフローが起きない事を仮定しています。そのため、[`std::int_least32_t`](https://cpprefjp.github.io/reference/cstdint/int_least32_t.html) の最大値の半分を超える値をテンプレート引数に取ることはできません。

```cpp
using mint = lib::static_modint<2000000000>;  // 多くの環境ではエラー
```

この仕様でも多くの競技プログラミングの問題では困らないはずです。

$p$ が素数のとき、`static_modint<p>` は $0$ から $p - 1$ までの $p$ 個の元からなる剰余体 $\mathbf{Z}/p\mathbf{Z}$ を表す型として扱えます。

### コンストラクタ

```cpp
using mint = lib::static_modint<1000000007>;

mint a;                   // 1.
std::vector<mint> A(10);  // 1.

mint b = 100;             // 2.
mint c = 10000000000LL;   // 2.
mint d(10000000000LL);    // 2.

static_assert(a == 0);
assert(std::all_of(std::cbegin(A), std::cend(A), [](auto val) { val == 0; }));
static_assert(b == 100);
static_assert(c == (10000000000LL % mint::mod()));
static_assert(d == (10000000000LL % mint::mod()));
```

1. 引数無しで初期化すると、値は 0 で初期化されます。
1. 引数を 1 つ与えて初期化すると、値が代入されます。必要に応じて余りも計算されます。

### 演算子

以下の演算子がオーバーロードされています。

- `++` (前置, 後置)
- `--` (前置, 後置)
- `+` (単項, 二項)
- `-` (単項, 二項)
- `*` (二項)
- `/`
- `+=`
- `-=`
- `*=`
- `/=`
- `==`
- `!=`
- `>>` ([`std::istream&` からの入力](https://cpprefjp.github.io/reference/istream/basic_istream/op_istream_free.html))
- `<<` ([`std::ostream&` への出力](https://cpprefjp.github.io/reference/ostream/basic_ostream/op_ostream_free.html))

以下の演算子もオーバーロードされていますが、[デバッグレベル](https://naskya.github.io/cp-library/about#cp_library_debug_level-%E3%83%9E%E3%82%AF%E3%83%AD)が $1$ 以上のとき、使用すると標準エラー出力に警告が出ます。この警告は 18 行目のコメントアウトを解除すると抑制できます。

- `%`
- `|`
- `^`
- `&` (二項)
- `>>` (ビット演算)
- `<<` (ビット演算)
- `%=`
- `|=`
- `^=`
- `&=`
- `>>=`
- `<<=`
- `>`
- `<`
- `>=`
- `<=`
- `!`
- `~`

### メンバ関数

以下の関数が使用できます。ここで、変数が保持している値を $x$ とします。

#### `inv()`

$x$ の乗法の逆元 $x^{-1}$ を返します。$x = 0$ である時、[`CP_LIBRARY_ASSERT`](https://naskya.github.io/cp-library/about#%E3%81%9D%E3%81%AE%E4%BB%96%E3%81%AE%E3%83%9E%E3%82%AF%E3%83%AD) マクロによって異常終了します。

#### `pow(n)`

$x^n$ を返します。

#### `to_frac()`

$x = a \cdot b^{-1}$ であるような $(a, b)$ の組のうち $a + b$ が最小であるものを返します。例えば $x = 2$ の時 `x.inv().to_frac()` は $(1, 2)$ を返します。

---
