#include <map>
#include <vector>
#include <unordered_set>

class RandomizedCollection
{
  std::unordered_map<int, int> valuesToCount;
  std::vector<int> values;
  std::unordered_map<int, std::unordered_set<int>> valuesToIndices;

public:
  RandomizedCollection() {}

  bool insert(int val)
  {
    values.push_back(val);
    valuesToIndices[val].insert(values.size() - 1);
    valuesToCount[val]++;
    return valuesToCount[val] == 1; // just added.
  }

  bool remove(int val)
  {
    if (valuesToCount[val] == 0)
      return false;

    int toSwapVal = values[values.size() - 1];

    int idx = *valuesToIndices[val].begin(); // random index that has val
    valuesToIndices[val].erase(idx);         // rm that index

    if (idx != values.size() - 1)
    {
      valuesToIndices[toSwapVal].insert(idx);
      valuesToIndices[toSwapVal].erase(values.size() - 1);
    }

    values[idx] = toSwapVal;
    valuesToCount[val]--;
    values.pop_back();

    return true;
  }

  int getRandom() { return values[std::rand() % values.size()]; }
};