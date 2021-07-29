---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/string/edit_distance/1.test.cpp
    title: test/string/edit_distance/1.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Edit distance
    links: []
  bundledCode: "#line 1 \"include/string/edit_distance.hpp\"\n\n//! @file edit_distance.hpp\n\
    //! @brief Edit distance\n\n#ifndef EDIT_DISTANCE_HPP\n#define EDIT_DISTANCE_HPP\n\
    \n#include <vector>\n\nnamespace lib {\n\n//! @tparam Container container type\
    \ (deduced from parameters)\n//! @param list_1 container 1\n//! @param list_2\
    \ container 2\n//! @return edit distance between container 1 and container 2\n\
    template <typename Container> int edit_distance(const Container& list_1, const\
    \ Container& list_2) {\n  const int n = static_cast<int>(std::size(list_1));\n\
    \  const int m = static_cast<int>(std::size(list_2));\n\n  std::vector dp(n +\
    \ 1, std::vector<int>(m + 1));\n\n  for (int i = 0; i <= n; ++i)\n    dp[i][0]\
    \ = i;\n  for (int j = 0; j <= m; ++j)\n    dp[0][j] = j;\n\n  for (int i = 1;\
    \ i <= n; i++) {\n    for (int j = 1; j <= m; j++) {\n      dp[i][j] = std::min(dp[i\
    \ - 1][j], dp[i][j - 1]) + 1;\n      dp[i][j] = std::min(dp[i][j], dp[i - 1][j\
    \ - 1] + (list_1[i - 1] != list_2[j - 1]));\n    }\n  }\n\n  return dp[n][m];\n\
    }\n\n}  // namespace lib\n\n#endif  // EDIT_DISTANCE_HPP\n"
  code: "\n//! @file edit_distance.hpp\n//! @brief Edit distance\n\n#ifndef EDIT_DISTANCE_HPP\n\
    #define EDIT_DISTANCE_HPP\n\n#include <vector>\n\nnamespace lib {\n\n//! @tparam\
    \ Container container type (deduced from parameters)\n//! @param list_1 container\
    \ 1\n//! @param list_2 container 2\n//! @return edit distance between container\
    \ 1 and container 2\ntemplate <typename Container> int edit_distance(const Container&\
    \ list_1, const Container& list_2) {\n  const int n = static_cast<int>(std::size(list_1));\n\
    \  const int m = static_cast<int>(std::size(list_2));\n\n  std::vector dp(n +\
    \ 1, std::vector<int>(m + 1));\n\n  for (int i = 0; i <= n; ++i)\n    dp[i][0]\
    \ = i;\n  for (int j = 0; j <= m; ++j)\n    dp[0][j] = j;\n\n  for (int i = 1;\
    \ i <= n; i++) {\n    for (int j = 1; j <= m; j++) {\n      dp[i][j] = std::min(dp[i\
    \ - 1][j], dp[i][j - 1]) + 1;\n      dp[i][j] = std::min(dp[i][j], dp[i - 1][j\
    \ - 1] + (list_1[i - 1] != list_2[j - 1]));\n    }\n  }\n\n  return dp[n][m];\n\
    }\n\n}  // namespace lib\n\n#endif  // EDIT_DISTANCE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: include/string/edit_distance.hpp
  requiredBy: []
  timestamp: '2021-07-29 22:09:58+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/string/edit_distance/1.test.cpp
documentation_of: include/string/edit_distance.hpp
layout: document
redirect_from:
- /library/include/string/edit_distance.hpp
- /library/include/string/edit_distance.hpp.html
title: Edit distance
---
