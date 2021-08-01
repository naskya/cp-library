#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_D"
#include <iostream>

#include "../../../include/algebra/eulers_totient_function.hpp"

int main() {
  long long n;
  std::cin >> n;

  if (n > 50000000)
    std::cout << lib::totient_function(n) << "\n";
  else
    std::cout << lib::totient_function_sequence(50000000)[n] << "\n";
}
