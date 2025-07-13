#include <vector>
using namespace std;

class Solution
{
public:
  double knightProbability(int n, int k, int row, int column)
  {
    vector<pair<int, int>> dirs = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    vector<vector<double>> dp(n, vector<double>(n, 0));
    vector<vector<double>> prevDp(n, vector<double>(n, 0));
    prevDp[row][column] = 1;

    while (k > 0)
    {
      for (int i = 0; i < n; ++i)
      {
        for (int j = 0; j < n; ++j)
        {
          dp[i][j] = 0;
          for (auto &[dx, dy] : dirs)
          {
            int prevX = i + dx;
            int prevY = j + dy;
            if (prevX >= 0 && prevX < n && prevY >= 0 && prevY < n)
              dp[i][j] += prevDp[prevX][prevY] / 8.0;
          }
        }
      }
      std::swap(dp, prevDp);
      --k;
    }

    double res = 0;
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
        res += prevDp[i][j];
    }
    return res;
  }
};