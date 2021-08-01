#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_D"
#include <iostream>

#include "../../../include/algebra/eulers_totient_function.hpp"

int main() {
  long long n;
  std::cin >> n;
  std::cout << lib::totient_function(n) << "\n";
}
