#include <set>
#include <vector>

class SummaryRanges
{
public:
  std::set<int> set;

  SummaryRanges() {}

  void addNum(int value) { set.insert(value); }

  std::vector<std::vector<int>> getIntervals()
  {
    std::vector<std::vector<int>> res{};

    int left = -1;
    int right = -1;

    for (int value : set)
    {
      if (left == -1)
      {
        left = value;
        right = value;
      }
      else if (value == right + 1)
      {
        right = value;
      }
      else
      {
        res.push_back({left, right});
        left = value;
        right = value;
      }
    }
    if (left == -1)
      return res;
    res.push_back({left, right});
    return res;
  }
};