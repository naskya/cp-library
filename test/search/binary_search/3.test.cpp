#define PROBLEM "https://yukicoder.me/problems/no/1350"
#include <iostream>
#include <numeric>

#include "../../../include/search/binary_search.hpp"

int main() {
  long long A, B, K;
  std::cin >> A >> B >> K;

  const long long L = std::lcm(A, B);

  const auto f = [&](const long long x) -> bool {
    return (x / A + x / B - x / L) >= K;
  };

  std::cout << lib::binary_search(A * K + 1, 0LL, f) << '\n';
}
