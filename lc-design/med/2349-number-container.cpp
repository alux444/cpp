#include <unordered_map>
#include <unordered_set>
#include <set>

class NumberContainers
{
public:
  std::unordered_map<int, int> indicesToNumber;
  std::unordered_map<int, std::set<int>> numberToIndices;

  NumberContainers() {}

  void change(int index, int number)
  {
    if (indicesToNumber.find(index) != indicesToNumber.end())
    {
      int prevNum = indicesToNumber[index];
      numberToIndices[prevNum].erase(index);
    }
    indicesToNumber[index] = number;
    numberToIndices[number].insert(index);
  }

  int find(int number)
  {
    if (numberToIndices[number].empty())
      return -1;
    return *(numberToIndices[number].begin());
  }
};