#include <map>

class Allocator
{
public:
  std::map<int, std::map<int, int>> allocatedBlocks;
  std::map<int, int> freeBlocks;

  Allocator(int n) { freeBlocks[0] = n - 1; }

  int allocate(int size, int mID)
  {
    for (auto it = freeBlocks.begin(); it != freeBlocks.end(); ++it)
    {
      int start = it->first;
      int end = it->second;

      if (end - start + 1 >= size)
      {
        int newStart = start;
        int newEnd = start + size - 1;

        allocatedBlocks[mID][newStart] = newEnd;

        freeBlocks.erase(it);
        if (newEnd + 1 <= end)
        {
          freeBlocks[newEnd + 1] = end;
        }

        return newStart;
      }
    }
    return -1;
  }

  int freeMemory(int mID)
  {
    int freed = 0;

    if (!allocatedBlocks.count(mID))
      return 0;

    for (auto &[start, end] : allocatedBlocks[mID])
    {
      freed += end - start + 1;

      std::vector<std::pair<int, int>> toErase;
      int newStart = start;
      int newEnd = end;

      for (auto &[freeStart, freeEnd] : freeBlocks)
      {
        if (freeEnd + 1 >= start && freeStart - 1 <= end)
        {
          toErase.push_back({freeStart, freeEnd});
          newStart = std::min(newStart, freeStart);
          newEnd = std::max(newEnd, freeEnd);
        }
      }

      for (auto &[fs, _] : toErase)
      {
        freeBlocks.erase(fs);
      }

      freeBlocks[newStart] = newEnd;
    }

    allocatedBlocks.erase(mID);
    return freed;
  }
};