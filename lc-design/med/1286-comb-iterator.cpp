#include <vector>

class CombinationIterator
{
  std::vector<std::string> combinations;
  int ptr;

public:
  CombinationIterator(std::string characters, int combinationLength) : combinations{}
  {
    ptr = 0;
    backtrack(characters, 0, combinationLength, "");
    std::sort(combinations.begin(), combinations.end());
  }

  void backtrack(std::string chars, int idx, int len, std::string cur)
  {
    if (cur.length() == len)
    {
      combinations.push_back(cur);
      return;
    }
    if (idx == chars.length())
      return;

    // skip this char
    backtrack(chars, idx + 1, len, cur);
    // add this char
    backtrack(chars, idx + 1, len, cur + chars[idx]);
  }

  std::string next()
  {
    return combinations[ptr++];
  }

  bool hasNext()
  {
    return ptr != combinations.size();
  }
};