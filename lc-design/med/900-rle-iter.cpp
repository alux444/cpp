#include <vector>

class RLEIterator
{
  std::vector<int> v;
  int index;
  int quantity;

public:
  RLEIterator(std::vector<int> &encoding) : v(std::move(encoding)), index(0), quantity(0)
  {
  }

  int next(int n)
  {
    while (index < v.size())
    {
      if (quantity + n > v[index])
      // qty consumed + n is enough to deplete
      {
        n -= v[index] - quantity; // consume rem qty
        quantity = 0;
        index += 2;
      }
      else
      {
        quantity += n;
        return v[index + 1];
      }
    }
    return -1;
  }
};