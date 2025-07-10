#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
  bool isMatch(string s, string p)
  {
    vector<vector<int>> dp(s.length() + 1, std::vector<int>(p.length() + 1, -1));
    return backtrack(0, 0, s, p, dp);
  }

  bool backtrack(int sIdx, int pIdx, string &s, string &p,
                 vector<vector<int>> &dp)
  {
    if (dp[sIdx][pIdx] != -1)
      return dp[sIdx][pIdx];

    if (pIdx >= p.length())
    {
      return dp[sIdx][pIdx] = sIdx >= s.length();
    }
    bool match = (sIdx < s.length() && (s[sIdx] == p[pIdx] || p[pIdx] == '.'));

    if (pIdx + 1 < p.length() && p[pIdx + 1] == '*')
    {
      bool m = backtrack(sIdx, pIdx + 2, s, p, dp) ||
               (match && backtrack(sIdx + 1, pIdx, s, p, dp));
      dp[sIdx][pIdx] = m;
      return dp[sIdx][pIdx];
    }

    if (match)
    {
      bool m = backtrack(sIdx + 1, pIdx + 1, s, p, dp);
      dp[sIdx][pIdx] = m;
      return dp[sIdx][pIdx];
    }

    dp[sIdx][pIdx] = 0;
    return dp[sIdx][pIdx];
  }
};