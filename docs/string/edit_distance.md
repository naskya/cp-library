---
title: Edit distance
documentation_of: //include/string/edit_distance.hpp
---

[編集距離](https://ja.wikipedia.org/wiki/%E3%83%AC%E3%83%BC%E3%83%99%E3%83%B3%E3%82%B7%E3%83%A5%E3%82%BF%E3%82%A4%E3%83%B3%E8%B7%9D%E9%9B%A2)を求める関数が定義されています。

## `edit_distance(A, B)`

`A` と `B` の編集距離を返します。`A`, `B` として文字列だけではなく `std::vector<int>` 等のコンテナを渡すこともできます。`A`, `B` の長さをそれぞれ $\lvert A \rvert, \lvert B \rvert$ とすると時間計算量は $\Theta(\lvert A \rvert \, \lvert B \rvert)$ です(ただし、要素の参照や整数の四則演算・コピー等の操作に掛かる時間が $\Theta(1)$ であることを仮定しています)。
