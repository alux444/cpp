#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution
{
public:
  int numBusesToDestination(vector<vector<int>> &routes, int source,
                            int target)
  {
    if (source == target)
      return 0;

    unordered_map<int, unordered_set<int>> busToStops{}; // bus no. -> stops
    unordered_map<int, unordered_set<int>>
        stopToBus{}; // stop -> bus overlap

    queue<int> q{};
    unordered_set<int> visitedBus{};
    unordered_set<int> visitedStops{};

    int bus = 0;
    for (vector<int> &route : routes)
    {
      for (int stop : route)
      {
        busToStops[bus].insert(stop);
        stopToBus[stop].insert(bus);
        if (stop == source)
        {
          q.push(bus);
          visitedBus.insert(bus);
          visitedStops.insert(source);
        }
      }
      ++bus;
    }

    int res = 0;
    while (!q.empty())
    {
      int sz = q.size();
      ++res;

      for (int i = 0; i < sz; ++i)
      {
        int bus = q.front();
        q.pop();

        if (busToStops[bus].count(target))
          return res;

        for (int stop : busToStops[bus])
        {
          if (visitedStops.count(stop))
            continue;

          visitedStops.insert(stop);
          // go through all the buses we havent visitedBus
          for (int bus : stopToBus[stop])
          {
            if (!visitedBus.count(bus))
            {
              q.push(bus);
              visitedBus.insert(bus);
            }
          }
        }
      }
    }
    return -1;
  }
};