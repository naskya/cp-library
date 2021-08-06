#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include <iostream>
#include <string>

#include "../../../include/string/manachers_algorithm.hpp"

int main() {
  std::string S;
  std::cin >> S;

  for (auto&& l : lib::palindrome_length_array(S))
    std::cout << l << ' ';
}
