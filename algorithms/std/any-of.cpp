#include <vector>
#include <algorithm>
#include <iostream>

/* runs a check through all of the numbers if any pass */

int main()
{

  std::vector<int> v{1, 4, 5, 55};

  if (std::any_of(v.begin(), v.end(), [](int i)
                  { return i % 2 == 0; }))
  {
    std::cout << "There is atleast one even number\n";
  }
  else
  {
    std::cout << "There are no even numbers\n";
  }
}
