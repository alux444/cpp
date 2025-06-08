#include <vector>
#include <algorithm>
#include <iostream>

/* runs a check through all of the numbers */

int main()
{

  std::vector<int> v{2, 4, 6, 8};

  if (std::all_of(v.begin(), v.end(), [](int i)
                  { return i % 2 == 0; }))
  {
    std::cout << "All numbers are even\n";
  }
  else
  {
    std::cout << "All numbers are not even\n";
  }
}
