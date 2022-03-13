---
title: Factorial, Permutation, Combination, Multinomial coefficient
documentation_of: //include/combinatorics/factorial.hpp
---

[階乗](https://ja.wikipedia.org/wiki/%E9%9A%8E%E4%B9%97)・[順列](https://ja.wikipedia.org/wiki/%E7%BD%AE%E6%8F%9B_(%E6%95%B0%E5%AD%A6))の数・[二項係数](https://ja.wikipedia.org/wiki/%E4%BA%8C%E9%A0%85%E4%BF%82%E6%95%B0)・[多項係数](https://ja.wikipedia.org/wiki/%E5%A4%9A%E9%A0%85%E4%BF%82%E6%95%B0)を計算する関数が定義されています。

---

### `factorial(n)`

$n$ の階乗 $\left(= n! = n \times (n - 1) \times (n - 2) \times \cdots \times 1 \right)$ を返します。

### `permutation(n, r)`

$n$ 個の区別できるものの中から $r$ 個を選んで任意の順番で横一列に並べるとき、考えられる並べ方の数 $\left(= {}_nP_r  = \frac{n!}{(n - r)!} \right)$ を返します。

### `combination(n, r)`

$n$ 個の区別できるものの中から $r$ 個を選ぶとき、考えられる選び方の数 $\left(= {}_nC_r = \frac{n!}{r!(n-r)!} \right)$ を返します。

### `multinomial(n, r...)`

$n$ 個のもののうち $r_1, \, r_2, \, \cdots, r_k$ 個のものがお互いに区別できないとき、それらを任意の順番で横一列に並べる方法の数 $\left(= \binom{n}{r_1, \, r_2, \, \cdots, r_k, 1, 1, \ldots, 1 \ } = \frac{n!}{r_1! \, r_2! \, \cdots \, r_k!} \right)$ を返します。$\sum_{i = 1}^k r_i \leq n$ が成り立つ必要があります。

### `stars_and_bars(n, r)`

$n$ 個の区別できるものの中から重複を許して(同じものを複数回選んでもよいとして) $r$ 個を選ぶとき、考えられる選び方の数 $\left(= {}_{n + r - 1}C_r \right)$ を返します。

### `factorial_array<N, type>()`

$0$ から $N$ までの階乗が入った長さ $N + 1$ の `type` 型の配列 ([`std::array`](https://cpprefjp.github.io/reference/array/array.html)) を返します。

### `factorial_modinv_array<N, modint_type>(x)`

`modint_type` には [`static_modint`](https://naskya.github.io/cp-library-cpp/include/algebra/static_modint.hpp) または [`dynamic_modint`](https://naskya.github.io/cp-library-cpp/include/algebra/dynamic_modint.hpp) が指定できます。$x$ として $N$ の階乗 ($N!$) を与えると、$0$ から $N$ までの階乗の `modint_type` 型における乗法の逆元が入った長さ $N + 1$ の `modint_type` 型の配列 ([`std::array`](https://cpprefjp.github.io/reference/array/array.html)) を返します。

---

[`static_modint`](https://naskya.github.io/cp-library-cpp/include/algebra/static_modint.hpp) または [`dynamic_modint`](https://naskya.github.io/cp-library-cpp/include/algebra/dynamic_modint.hpp) を用いた組み合わせの計算では、`factorial_array` 関数と `factorial_modinv_array` 関数で行った前計算の結果を関数の引数の末尾に与えると定数時間で値を計算できるようになります。

```cpp
using mint = lib::static_modint<1000000007>;
constexpr int N = 500000;

// 階乗と階乗の逆元を前計算
const auto fact_array     = lib::factorial_array<N, mint>();
const auto fact_inv_array = lib::factorial_modinv_array<N, mint>(fact_array.back());

// 以下の計算は全て定数時間で行われる
const mint a = fact_array[n];  // factorial(n) は fact_array[n]
const mint b = permutation   (n, r,                       fact_array, fact_inv_array);
const mint c = combination   (n, r,                       fact_array, fact_inv_array);
const mint d = multinomial   (n, r_1, r_2, n - r_1 - r_2, fact_array, fact_inv_array);
const mint e = stars_and_bars(n, r,                       fact_array, fact_inv_array);
//                                                        ^^^^^^^^^^^^^^^^^^^^^^^^^^
```

---
