#include <map>
#include <list>
#include <unordered_map>

class FreqStack
{
  std::map<int, std::list<int>> freqToVals;
  std::unordered_map<int, int> valToFreq;

public:
  FreqStack()
  {
  }

  void push(int val)
  {
    if (valToFreq.find(val) == valToFreq.end())
    {
      valToFreq[val] = 1;
      freqToVals[1].push_back(val);
      return;
    }
    // exists
    int prevFreq = valToFreq[val]++; // increment
    freqToVals[prevFreq + 1].push_back(val);
  }

  int pop()
  {
    auto &[freq, list] = *--freqToVals.end();
    int val = list.back();
    list.pop_back();
    if (list.empty())
      freqToVals.erase(freq);
    valToFreq[val]--;
    return val;
  }
};