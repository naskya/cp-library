#define PROBLEM "https://atcoder.jp/contests/abc143/tasks/abc143_c"
#include <iostream>
#include <string>

#include "../../../include/string/run_length_encoding.hpp"

int main() {
  int N;
  std::string S;
  std::cin >> N >> S;
  std::cout << std::size(lib::run_length_encoding(S)) << '\n';
}
