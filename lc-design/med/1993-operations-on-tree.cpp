#include <unordered_map>
#include <vector>

class LockingTree
{
private:
  std::unordered_map<int, std::vector<int>> descendants;
  std::vector<std::vector<int>> nodes;
  // 0 - parent
  // 1 - lockedby
  int n;

public:
  LockingTree(std::vector<int> &parent)
  {
    n = parent.size();
    nodes.resize(n, std::vector<int>(2, -1));

    for (int i = 1; i < n; i++)
    {
      int thisParent = parent[i];
      nodes[i][0] = thisParent;
      descendants[thisParent].push_back(i);
    }
  }

  bool lock(int num, int user)
  {
    if (nodes[num][1] != -1)
      return false;
    nodes[num][1] = user;
    return true;
  }

  bool unlock(int num, int user)
  {
    if (nodes[num][1] != user)
      return false;
    nodes[num][1] = -1;
    return true;
  }

  bool upgrade(int num, int user)
  {
    bool isNodeUnlocked = nodes[num][1] == -1;
    if (!isNodeUnlocked)
      return false;

    bool isOneLocked = false;
    isAnyDescendantLocked(num, isOneLocked);
    if (!isOneLocked)
      return false;

    if (isAnyAncestorLocked(num))
      return false;

    nodes[num][1] = user;
    unlockAllDescendants(num);
    return true;
  }

  void isAnyDescendantLocked(int num, bool &isOneLocked)
  {
    for (int &descendant : descendants[num])
    {
      if (nodes[descendant][1] != -1)
      {
        isOneLocked = true;
        return;
      }
      isAnyDescendantLocked(descendant, isOneLocked);
    }
  }

  void unlockAllDescendants(int num)
  {
    for (int descendant : descendants[num])
    {
      nodes[descendant][1] = -1;
      unlockAllDescendants(descendant);
    }
  }

  bool isAnyAncestorLocked(int num)
  {
    if (num == -1)
      return false;
    return nodes[num][1] != -1 || isAnyAncestorLocked(nodes[num][0]);
  }
};