---
title: Euler's totient function
documentation_of: //include/algebra/eulers_totient_function.hpp
---

[Euler の $\varphi$ 関数](https://ja.wikipedia.org/wiki/%E3%82%AA%E3%82%A4%E3%83%A9%E3%83%BC%E3%81%AE%CF%86%E9%96%A2%E6%95%B0)が定義されています。

---

### `totient_function(n)`

$\varphi (n)$ の値、すなわち $n$ 以下の正整数のうち $n$ と互いに素であるものの個数を返します。

### `totient_function_sequence(n)`

$0, \varphi(1), \varphi(2), \ldots, \varphi(n-1), \varphi(n)$ が格納された、要素数 $n + 1$ の配列 (`std::vector`) を返します。

<!-- ToDo: totient_function_sum(n) \sum_{i = 1}^n \varphi(i) -->

---
