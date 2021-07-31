---
title: Factorial, Permutation, Combination
documentation_of: //include/combinatorics/factorial.hpp
---

階乗を計算する関数・順列の数を計算する関数・二項係数を計算する関数が定義されています。

---

### `factorial(n)`

$n$ の階乗 ($n!$) を返します。

### `permutation(n, r)`

$n$ 個の区別できるものの中から $r$ 個を選んで任意の順番で横一列に並べるとき、考えられる並べ方の数 (${}_nP_r$) を返します。

### `combination(n, r)`

$n$ 個の区別できるものの中から $r$ 個を選ぶとき、考えられる選び方の数 (${}_nC_r$) を返します。

### `factorial_array<N, type>()`

$0$ から $N$ までの階乗が入った長さ $N + 1$ の `type` 型の配列 (`std::array`) を返します。

### `factorial_modinv_array<N, modint_type>(x)`

`modint_type` には [`static_modint`](https://naskya.github.io/cp-library/include/algebra/static_modint.hpp) または [`dynamic_modint`](https://naskya.github.io/cp-library/include/algebra/dynamic_modint.hpp) または類似の型 (`atcoder::modint` 等) が指定できます。$x$ として $N$ の階乗 ($N!$) を与えると、$0$ から $N$ までの階乗の `modint_type` 型における乗法の逆元が入った長さ $N + 1$ の `modint_type` 型の配列 (`std::array`) を返します。

---

`factorial_array` と `factorial_modinv_array` を用いると、時間計算量 $\Theta(N)$ の前計算を行うことで ${}_nC_r$ や ${}_nP_r$ の値を $\Theta(1)$ の時間計算量で求めることができるようになります。

```cpp
using mint = lib::static_modint<1000000007>;
constexpr int N = 100000;

const auto fact     = lib::factorial_array<N, mint>();
const auto fact_inv = lib::factorial_modinv_array<N, mint>(fact[N]);

assert(lib::permutation(n, r) == fact[n] * fact_inv[n - r]);
assert(lib::combination(n, r) == fact[n] * fact_inv[n - r] * fact_inv[r]);
```

---
