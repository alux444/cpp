#include <vector>
using namespace std;

class Solution
{
public:
  int maximalSquare(vector<vector<char>> &matrix)
  {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp{};
    dp.resize(n, vector<int>(m, -1));
    check(0, 0, dp, matrix);
    int max = 0;
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < m; ++j)
        max = std::max(max, dp[i][j]);
    }
    return max * max;
  }

  int check(int r, int c, vector<vector<int>> &dp,
            vector<vector<char>> &matrix)
  {
    if (r >= matrix.size() || c >= matrix[0].size())
      return 0;
    if (dp[r][c] == -1)
    {
      int right = check(r, c + 1, dp, matrix);
      int down = check(r + 1, c, dp, matrix);
      int diag = check(r + 1, c + 1, dp, matrix);

      dp[r][c] = 0;
      if (matrix[r][c] == '1')
      {
        dp[r][c] = 1 + min(right, min(down, diag));
      }
    }
    return dp[r][c];
  }
};