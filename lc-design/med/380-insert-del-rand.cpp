#include <vector>
#include <unordered_map>
#include <cstdlib>

class RandomizedSet
{
  std::vector<int> v;
  std::unordered_map<int, int> map; // val : idx
public:
  RandomizedSet() {}

  bool insert(int val)
  {
    if (map.find(val) != map.end())
      return false;
    v.push_back(val);
    map[val] = v.size() - 1;
    return true;
  }

  bool remove(int val)
  {
    if (map.find(val) == map.end())
      return false;
    // swap with the last value and delete this
    int idx = map[val];
    v[idx] = v[v.size() - 1];
    map[v[idx]] = idx;
    map.erase(val);
    v.pop_back();
    return true;
  }

  int getRandom()
  {
    return v[std::rand() % v.size()];
  }
};