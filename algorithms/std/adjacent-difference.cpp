#include <iostream>
#include <functional>
#include <numeric>

// runs execution on adjacent (starting from 1st and 2nd)

int myop(int x, int y) { return x + y; }

int main()
{
  int val[] = {1, 2, 3, 4, 5, 9, 11, 12};
  int result[8];

  std::adjacent_difference(val, val + 8, result); 
  std::cout << "default adjacent_difference: ";
  for (int i = 0; i < 8; ++i)
  {
    std::cout << result[i] << ' ';
  }
  std::cout << '\n';

  std::adjacent_difference(val, val + 8, result, myop);
  std::cout << "using custom function: ";
  for (int i = 0; i < 8; ++i)
  {
    std::cout << result[i] << ' ';
  }
  std::cout << '\n';

  return 0;
}