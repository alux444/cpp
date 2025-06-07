#include <vector>
#include <numeric>
#include <iostream>

/* std accumulator */

int product(int a, int b)
{
  return a * b;
}

int main()
{
  std::vector<int> v{10, 2, 4, 6};

  std::cout << "The sum of elements of v is : " << std::accumulate(v.begin(), v.end(), 0) << std::endl;
  std::cout << "The product of all elements is : " << std::accumulate(v.begin(), v.end(), 1, product) << std::endl;
}