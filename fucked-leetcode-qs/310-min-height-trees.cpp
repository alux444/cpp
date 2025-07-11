#include <vector>
#include <map>
#include <unordered_set>
using namespace std;

class Solution
{
public:
  vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
  {
    if (n == 1)
      return {0};
    unordered_map<int, unordered_set<int>> adjMap{};
    for (vector<int> &edge : edges)
    {
      int e1 = edge[0];
      int e2 = edge[1];
      adjMap[e1].insert(e2);
      adjMap[e2].insert(e1);
    }
    vector<int> leaves{};
    for (auto &[node, edge] : adjMap)
    {
      if (edge.size() == 1)
        leaves.push_back(node);
    }
    while (n > 2)
    {
      n -= leaves.size();
      vector<int> newLeaves{};
      for (int leaf : leaves)
      {
        int neighbour = *(adjMap[leaf].begin());
        adjMap[neighbour].erase(leaf);
        if (adjMap[neighbour].size() == 1)
          newLeaves.push_back(neighbour);
      }
      leaves = newLeaves;
    }
    return leaves;
  }
};