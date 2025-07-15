#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
public:
  int longestStrChain(vector<string> &words)
  {
    sort(words.begin(), words.end(),
         [](const string &a, const string &b) -> bool
         {
           return a.length() < b.length();
         });

    unordered_map<string, int> dp;
    int res = 0;

    for (string wrd : words)
    {
      for (int i = 0; i < wrd.length(); ++i)
      {
        string removed = wrd.substr(0, i) + wrd.substr(i + 1); // exclude i
        int removedChain = dp.find(removed) == dp.end() ? 1 : dp[removed] + 1;
        dp[wrd] = max(dp[wrd], removedChain);
      }
      res = max(res, dp[wrd]);
    }
    return res;
  }
};