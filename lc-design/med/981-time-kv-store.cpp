#include <vector>
#include <unordered_map>

class TimeMap
{
public:
  std::unordered_map<std::string, std::vector<std::pair<int, std::string>>>
      map;
  // ket : timestamp, value
  TimeMap() {}

  void set(std::string key, std::string value, int timestamp)
  {
    map[key].push_back(std::make_pair(timestamp, value));
  }

  std::string get(std::string key, int timestamp)
  {
    if (map.find(key) == map.end())
      return "";
    const std::vector<std::pair<int, std::string>> &values = map[key];
    auto it = std::upper_bound(values.begin(), values.end(),
                               std::make_pair(timestamp, std::string{}),
                               [](const std::pair<int, std::string> &a,
                                  const std::pair<int, std::string> &b)
                               {
                                 return a.first < b.first;
                               });
    if (it == values.begin())
      return "";
    --it;
    return it->second;
  }
};