#include <vector>
using namespace std;

class Solution
{
public:
  // profit, left, right
  tuple<int, int, int> profit(vector<int> &prices)
  {
    int min = INT_MAX;
    int minI = -1;
    int res = 0;
    int left = -1;
    int right = -1;

    for (int i = 0; i < prices.size(); ++i)
    {
      int price = prices[i];
      if (price < min)
      {
        min = price;
        minI = i;
      }
      if (price - min > res)
      {
        res = price - min;
        left = minI;
        right = i;
      }
    }

    return {res, left, right};
  }

  int loss(vector<int> &prices)
  {
    int max = 0;
    int res = 0;
    for (int price : prices)
    {
      if (price > max)
        max = price;
      res = std::max(res, max - price);
    }
    return res;
  }

  int maxProfit(vector<int> &prices)
  {
    if (prices.size() == 0)
      return 0;

    auto [p, l, r] = profit(prices);

    if (l == -1) // we never have any profit anywhere
      return 0;

    int largestL = 0;
    if (r - l - 1 >= 2)
    { // exclude the full range, only the sub range
      vector<int> profitRange(prices.begin() + l + 1, prices.begin() + r);
      largestL = loss(profitRange);
    }

    int leftProf = 0;
    if (l >= 1)
    {
      vector<int> leftRange(prices.begin(), prices.begin() + l);
      leftProf = get<0>(profit(leftRange));
    }

    int rightProf = 0;
    if (r < prices.size() - 1)
    {
      vector<int> rightRange(prices.begin() + r + 1, prices.end());
      rightProf = get<0>(profit(rightRange));
    }

    // cout << "p " << p << " m " << largestL << " " << leftProf << " " << rightProf;
    return p + max({largestL, leftProf, rightProf});
  }
};