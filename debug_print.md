# デバッグ出力

デバッグ出力のためのマクロです。任意の個数の引数を取れて、数値や文字列やコンテナや `std::pair` や `std::tuple` やそれらが入れ子になったオブジェクト等を出力することができます。詳しい説明は[ここ](https://naskya.net/post/0002/)にあります。

## 使用例

### コード

```cpp
#include <set>
#include <vector>
#include "debug_print.hpp"
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)

int main() {
  int a = 1, b = 2, c = 3;
  std::set<int> A {10, 20, 30};
  debug(a, b, c, A);

  std::vector<std::vector<int>> B {
    {0, 1},
    {2, 3},
    {4, 5}
  };
  debug(B);
}
```

```sh
$ g++ -std=c++17 -o a.out main.cpp && ./a.out
```

### 出力

```
a: 1 | b: 2 | c: 3
A: [ 10 20 30 ]
B: [ 0 1 ]
   [ 2 3 ]
   [ 4 5 ]
```

## Code

<script src="https://gist.github.com/naskya/1e5e5cd269cfe16a76988378a60e2ca3.js"></script>
