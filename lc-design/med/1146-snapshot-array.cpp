#include <vector>

class SnapshotArray
{
public:
  int snapId;
  std::vector<std::vector<std::pair<int, int>>> history;
  // index for index key
  // vector of pairs < snapshotid, value >

  SnapshotArray(int length) : snapId(0), history(length)
  {
    for (int i = 0; i < length; i++)
      history[i].push_back(std::make_pair(0, 0));
  }

  void set(int index, int val)
  {
    history[index].push_back(std::make_pair(snapId, val));
  }

  int snap()
  {
    return snapId++;
  }

  int get(int index, int snap_id)
  {
    auto &indexHistory = history[index];
    auto it = std::upper_bound(
        indexHistory.begin(), indexHistory.end(),
        std::make_pair(snap_id, INT_MAX));
    return prev(it)->second;
  }
};