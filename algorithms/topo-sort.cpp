#include <unordered_map>
#include <vector>
#include <queue>

template <typename T>
std::unordered_map<T, int> get_indegree_map(std::unordered_map<T, std::vector<T>> graph)
{
  std::unordered_map<T, int> indegrees{};
  for (auto [node, _] : graph)
    indegrees[node] = 0;
  for (auto [node, neighbours] : graph)
  {
    for (T neighbour : neighbours)
      indegrees[neighbour]++;
  }
  return indegrees;
}

template <typename T>
std::vector<T> topo_sort(std::unordered_map<T, std::vector<T>> graph)
{
  std::vector<T> topoSort{};
  std::queue<T> queue{};
  std::unordered_map<T, int> indegrees = get_indegree_map(graph);
  for (auto [node, indegree] : indegrees)
    if (indegree == 0)
      queue.push(node);
  while (!queue.empty())
  {
    T top = queue.front();
    topoSort.push_back(top);
    for (T neighbour : graph[top])
    {
      if (--indegrees[neighbour] == 0)
        queue.push(neighbour);
    }
    queue.pop();
  }
  if (topoSort.size() != graph.size())
  {
    std::cout << "No valid topological sort - graph contains cycle\n";
    return {};
  }
  return topoSort;
}
