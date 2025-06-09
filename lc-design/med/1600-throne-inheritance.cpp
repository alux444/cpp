#include <vector>
#include <unordered_map>
#include <unordered_set>

class ThroneInheritance
{
  std::unordered_map<std::string, std::vector<std::string>> children;
  std::unordered_set<std::string> dead;
  std::string king;

public:
  ThroneInheritance(std::string kingName) : king(kingName)
  {
  }

  void birth(std::string parentName, std::string childName)
  {
    children[parentName].push_back(childName);
  }

  void death(std::string name)
  {
    dead.insert(name);
  }

  std::vector<std::string> getInheritanceOrder()
  {
    std::vector<std::string> res{};
    dfs(res, king);
    return res;
  }

  void dfs(std::vector<std::string> &order, std::string cur)
  {
    if (dead.find(cur) == dead.end())
      order.push_back(cur);
    for (std::string child : children[cur])
      dfs(order, child);
  }
};