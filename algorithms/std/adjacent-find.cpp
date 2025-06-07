#include <iostream>
#include <vector>
#include <algorithm>

bool myop(int &a, int &b)
{
  return a - b == -4;
}

int main()
{
  std::vector<int> v{1, 2, 3, 4, 4, 3, 7, 8, 9, 10};

  // returns the iterator pointing to the first element matching the condition
  // by default, equality check
  auto i = std::adjacent_find(v.begin(), v.end());
  std::cout << "The first pair of repeated elements are: " << *i << '\n';
  
  // custom function
  auto j = std::adjacent_find(v.begin(), v.end(), myop);
  std::cout << "The first element where the next index has a diff of -4: " << *j << '\n';
  
}