
//! @file edit_distance.hpp

#ifndef CP_LIBRARY_EDIT_DISTANCE_HPP
#define CP_LIBRARY_EDIT_DISTANCE_HPP

#include <vector>

namespace lib {

//! @tparam Container container type (deduced from parameters)
//! @param list_1 container 1
//! @param list_2 container 2
//! @return edit distance between container 1 and container 2
template <typename Container>
[[nodiscard]] int edit_distance(const Container& list_1, const Container& list_2) {
  const int n = static_cast<int>(std::size(list_1));
  const int m = static_cast<int>(std::size(list_2));

  std::vector dp(n + 1, std::vector<int>(m + 1));

  for (int i = 0; i <= n; ++i)
    dp[i][0] = i;
  for (int j = 0; j <= m; ++j)
    dp[0][j] = j;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + 1;
      dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1] + (list_1[i - 1] != list_2[j - 1]));
    }
  }

  return dp[n][m];
}

}  // namespace lib

#endif  // CP_LIBRARY_EDIT_DISTANCE_HPP
