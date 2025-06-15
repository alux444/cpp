#include <map>

class RangeModule
{
  std::map<int, int> map; // left : right
public:
  RangeModule() {}

  std::pair<int, int> compact(int left, int right)
  {
    std::pair<int, int> compacted = {left, right};
    auto it = map.upper_bound(left);
    if (it != map.begin())
      --it; // first bound that overlaps with the left start

    while (it != map.end())
    {
      int start = it->first;
      int end = it->second;
      if (end < left) // increment end
      {
        ++it;
        continue;
      }
      if (start > right)
        break; // first interval that doesnt overlap

      compacted.first = std::min(compacted.first, start);
      compacted.second = std::max(compacted.second, end);
      it = map.erase(it);
    }

    return compacted;
  }

  void addRange(int left, int right)
  {
    std::pair<int, int> pair = compact(left, right);
    map[pair.first] = pair.second;
  }

  bool queryRange(int left, int right)
  {
    auto it = map.upper_bound(left); // first bound above left
    if (it == map.begin())
      return false;
    --it;
    return it->second >= right;
  }

  void removeRange(int left, int right)
  {
    std::pair<int, int> pair = compact(left, right);
    if (pair.first < left)
      map[pair.first] = left; // updated left bound after removal
    if (pair.second > right)
      map[right] = pair.second; // updated right bound after removing
  }
};