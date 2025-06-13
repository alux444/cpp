#include <unordered_map>
#include <list>

class LFUCache
{
  std::unordered_map<int, std::pair<int, int>> cache; // key : val, freq
  std::unordered_map<int, std::list<int>> freqList;   // frequency
  std::unordered_map<int, std::list<int>::iterator> positions;
  int capacity;
  int minFreq;

public:
  LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

  int get(int key)
  {
    if (cache.find(key) == cache.end())
      return -1;

    increaseFreq(key);

    return cache[key].first;
  }

  void increaseFreq(int key)
  {
    // exists. we need to bump it to the next frequency up
    int prevFreq = cache[key].second;

    cache[key].second++;

    // move the freq up, update minfreq if needed
    freqList[prevFreq].erase(positions[key]);
    if (freqList[minFreq].empty())
      ++minFreq;

    // add the value to the next freq and update the iterator
    freqList[prevFreq + 1].push_back(key);
    positions[key] = --freqList[prevFreq + 1].end(); // val is at the back
  }

  void put(int key, int value)
  {
    if (cache.find(key) == cache.end())
    {
      if (cache.size() == capacity)
      {
        // pop the lowest freq LFU
        int toRemoveKey = freqList[minFreq].front();
        cache.erase(toRemoveKey);
        positions.erase(toRemoveKey);
        freqList[minFreq].pop_front();
      }
      cache[key] = {value, 1}; // 1st instance
      freqList[1].push_back(key);
      positions[key] = --freqList[1].end();
      minFreq = 1;
    }
    else
    {
      // we just update the frq up
      cache[key].first = value;
      increaseFreq(key);
    }
  }
};