#include <queue>
#include <unordered_set>
#include <map>
#include <vector>

class Router
{
  std::queue<std::tuple<int, int, int>> queue;
  std::unordered_set<std::string> used;
  std::unordered_map<int, std::vector<int>> destToTimes;
  int memoryLimit;

  std::string packetString(int src, int dest, int time)
  {
    return std::to_string(src) + "," + std::to_string(dest) + "," + std::to_string(time);
  }

public:
  Router(int memoryLimit) : memoryLimit(memoryLimit)
  {
  }

  bool addPacket(int source, int destination, int timestamp)
  {
    std::string str = packetString(source, destination, timestamp);
    if (used.count(str))
      return false;
    if (queue.size() == memoryLimit)
    {
      auto toRemove = queue.front();
      queue.pop();

      int src = std::get<0>(toRemove);
      int dest = std::get<1>(toRemove);
      int time = std::get<2>(toRemove);

      std::string toRemoveStr = packetString(src, dest, time);
      used.erase(toRemoveStr);

      auto &times = destToTimes[dest];
      auto it = std::lower_bound(times.begin(), times.end(), time); // logN because timestamps strictly increase, so vector is sorted
      times.erase(it);
    }
    queue.push({source, destination, timestamp});
    used.insert(str);
    destToTimes[destination].push_back(timestamp);
    return true;
  }

  std::vector<int> forwardPacket()
  {
    if (queue.empty())
      return {};

    auto [src, dest, time] = queue.front();
    queue.pop();
    used.erase(packetString(src, dest, time));

    auto &times = destToTimes[dest];
    auto it = std::lower_bound(times.begin(), times.end(), time);
    times.erase(it);

    return {src, dest, time};
  }

  int getCount(int destination, int startTime, int endTime)
  {
    auto &times = destToTimes[destination];
    auto low = std::lower_bound(times.begin(), times.end(), startTime);
    auto high = std::upper_bound(times.begin(), times.end(), endTime);
    return high - low;
  }
};