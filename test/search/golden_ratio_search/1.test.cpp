#define PROBLEM "https://yukicoder.me/problems/no/306"
#define ERROR 1e-6
#include <cmath>
#include <iomanip>
#include <iostream>

#include "../../../include/search/golden_ratio_search.hpp"

int main() {
  long double x_a, y_a, x_b, y_b;
  std::cin >> x_a >> y_a >> x_b >> y_b;

  const long double x_a_2 = x_a * x_a;
  const long double x_b_2 = x_b * x_b;

  const auto l = [&](const long double y) -> long double {
    const long double y_a_1 = y - y_a;
    const long double y_b_1 = y - y_b;
    return std::sqrt(y_a_1 * y_a_1 + x_a_2) + std::sqrt(y_b_1 * y_b_1 + x_b_2);
  };

  std::cout << std::fixed << std::setprecision(10)
            << lib::golden_ratio_search<true>(-100.0L, 1100.0L, l).first << '\n';
}
