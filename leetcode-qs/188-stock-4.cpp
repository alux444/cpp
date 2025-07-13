#include <vector>
using namespace std;

class Solution
{
public:
  int maxProfit(int k, vector<int> &prices)
  {
    int days = prices.size();
    vector<vector<vector<int>>> dp(
        days + 1, vector<vector<int>>(k + 1, vector<int>(2, -1)));
    return backtrack(0, k, 0, dp, prices);
  }

  int backtrack(int day, int k, int holdingStock,
                vector<vector<vector<int>>> &dp, vector<int> &prices)
  {
    if (day == prices.size() || k == 0)
      return 0;

    if (dp[day][k][holdingStock] != -1)
      return dp[day][k][holdingStock];

    int dont = backtrack(day + 1, k, holdingStock, dp, prices);

    int action = 0;
    if (holdingStock)
      action = prices[day] + backtrack(day + 1, k - 1, 0, dp, prices);
    else
      action = -prices[day] + backtrack(day + 1, k, 1, dp, prices);

    return dp[day][k][holdingStock] = max(dont, action);
  }
};