---
title: Golden section search
documentation_of: //include/search/golden_section_search.hpp
---

[黄金分割探索](https://ja.wikipedia.org/wiki/%E9%BB%84%E9%87%91%E5%88%86%E5%89%B2%E6%8E%A2%E7%B4%A2)によって凸関数の区間内の最小値(または最大値)とそれを達成する引数を求める関数が定義されています。

---

### `golden_section_search<true>(a, b, f, diff)`

区間 $I = [a, b]$ で定義される[凸関数](https://ja.wikipedia.org/wiki/%E5%87%B8%E9%96%A2%E6%95%B0) $f: I \to \mathbf{R}$ に対して $\mathrm{argmin}_{x \in I} \, f(x)$ と $\mathrm{min}_{x \in I} f(x)$ をこの順番で持つ [`std::pair`](https://cpprefjp.github.io/reference/utility/pair.html) 型の値を返します。

`diff` は $\mathrm{argmin} \, f(x)$ に対する許容誤差です。

### `golden_section_search<false>(a, b, f, diff)`

区間 $I = [a, b]$ で定義される[凸関数](https://ja.wikipedia.org/wiki/%E5%87%B8%E9%96%A2%E6%95%B0) $f: I \to \mathbf{R}$ に対して $\mathrm{argmax}_{x \in I} \, f(x)$ と $\mathrm{max}_{x \in I} f(x)$ をこの順番で持つ [`std::pair`](https://cpprefjp.github.io/reference/utility/pair.html) 型の値を返します。

`diff` は $\mathrm{argmax} \, f(x)$ に対する許容誤差です。

---
