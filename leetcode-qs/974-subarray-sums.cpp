#include <map>
using namespace std;

class Solution
{
public:
  int subarraysDivByK(vector<int> &nums, int k)
  {
    int mod = 0;
    int res = 0;
    unordered_map<int, int> map{};
    map[0] = 1;

    for (int num : nums)
    {
      mod = (mod + num) % k;
      if (mod < 0)
        mod += k;
      res += map[mod];
      map[mod]++;
    }

    return res;
  }
};