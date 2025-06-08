#include <vector>
#include <algorithm>
#include <iostream>

/* o(logn) binary search for a specific value in a sorted collection */

int main()
{

  std::vector<int> v{2, 4, 6, 8, 9, 10, 15, 16, 19};

  int lookingFor = 16;
  if (std::binary_search(v.begin(), v.end(), lookingFor))
  {
    std::cout << "Found number\n";
  }
  else
  {
    std::cout << "Didn't find number\n";
  }
}
