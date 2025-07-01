#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> v{0, 2, 3, 25, 5};
  std::vector<int> t{3, 19, 10, 2};

  auto result = std::find_first_of(v.begin(), v.end(), t.begin(), t.end());
  // finds the FIRST element in the first range that matches ANY element in the second range

  if (result == v.end())
  {
    std::cout << "no elements of v were equal to 3, 19, 10 or 2\n";
  }
  else
  {
    std::cout << "found a match at "
              << std::distance(v.begin(), result) << "\n";
  };
}