---
title: Binary search
documentation_of: //include/search/golden_ratio_search.hpp
---

[黄金分割探索](https://ja.wikipedia.org/wiki/%E9%BB%84%E9%87%91%E5%88%86%E5%89%B2%E6%8E%A2%E7%B4%A2)によって凸関数の区間内の最小値(または最大値)とそれを達成する引数を求める関数が定義されています。

---

### `golden_ratio_search<true>(a, b, f, diff)`

区間 $I = [a, b]$ で定義される凸関数 $f: I \to \mathbf{R}$ に対して $\displaystyle\argmin_{x \in I} f(x)$ と $\displaystyle\min_{x \in I} f(x)$ をこの順番で持つ `std::pair` 型の値を返します。

`diff` は $\argmin$ に対する許容誤差です。

### `golden_ratio_search<false>(a, b, f, diff)`

区間 $I = [a, b]$ で定義される凸関数 $f: I \to \mathbf{R}$ に対して $\displaystyle\argmax_{x \in I} f(x)$ と $\displaystyle\max_{x \in I} f(x)$ をこの順番で持つ `std::pair` 型の値を返します。

`diff` は $\argmax$ に対する許容誤差です。
