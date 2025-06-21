#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> origin{1, 2, 3};
  std::vector<int> destination;

  int count = std::count_if(origin.begin(), origin.end(), [](const int i)
                            { return i % 2 == 1; });

  std::cout << count << "\n";
}