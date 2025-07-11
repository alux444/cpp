#include <vector>
using namespace std;

class Solution
{
public:
  vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  int longestIncreasingPath(vector<vector<int>> &matrix)
  {
    int r = matrix.size();
    int c = matrix[0].size();
    vector<vector<int>> dp(r, vector<int>(c, -1));
    int res = 0;
    for (int i = 0; i < r; ++i)
    {
      for (int j = 0; j < c; ++j)
      {
        res = max(res, dfs(matrix, dp, i, j));
      }
    }
    return res;
  }

  int dfs(const vector<vector<int>> &matrix, vector<vector<int>> &dp, int i,
          int j)
  {
    if (dp[i][j] != -1)
      return dp[i][j];

    dp[i][j] = 1;
    int max = 1;

    for (auto [dx, dy] : dirs)
    {
      int r = i + dx;
      int c = j + dy;
      if (r >= 0 && r < matrix.size() && c >= 0 && c < matrix[0].size() &&
          matrix[r][c] > matrix[i][j])
      {
        max = std::max(max, 1 + dfs(matrix, dp, r, c));
      }
    }

    dp[i][j] = max;
    return max;
  }
};