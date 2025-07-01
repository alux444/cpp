#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
  std::vector<int> vec = {0, 1, 2, 3, 1, 6, 1};
  // equal_range requires a sorted input {0, 1, 1, 1, 2, 3, 6}
  std::sort(vec.begin(), vec.end());

  // {0, 1, 1, 1, 2, 3, 6}
  //     ^        ^
  auto equalRangeIt = std::equal_range(vec.begin(), vec.end(), 1);
  for (auto it = equalRangeIt.first; it != equalRangeIt.second; ++it)
  {
    std::cout << " Position: " << (it - vec.begin()) << " = " << *it << std::endl;
  }
}