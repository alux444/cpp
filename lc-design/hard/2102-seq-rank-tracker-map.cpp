#include <map>
#include <set>
#include <string>

class SORTracker
{
  std::map<int, std::set<std::string>> map;
  int count;

public:
  SORTracker() : count(0)
  {
  }

  void add(std::string name, int score)
  {
    map[score].insert(name);
  }

  std::string get()
  {
    ++count;
    auto it = map.end();
    --it;

    // find the count we need
    int len = count;
    while (len > it->second.size())
    {
      if (it == map.begin())
        break;
      len -= it->second.size();
      --it;
    }

    auto setIt = it->second.begin();
    for (int i = 0; i < len - 1; ++i)
      ++setIt;
    return *setIt;
  }
};