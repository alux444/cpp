#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> origin{1, 2, 3};
  std::vector<int> destination;

  // Will copy from origin [begin, end), to destination
  std::copy_if(origin.begin(), origin.end(), std::back_inserter(destination), [](const int i)
               { return i % 2 == 1; });

  // destination is now {1, 3}
  for (auto value : destination)
  {
    std::cout << value << " ";
  }
}