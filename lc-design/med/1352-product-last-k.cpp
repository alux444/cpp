#include <vector>

class ProductOfNumbers
{
  std::vector<int> prefixProducts;

public:
  ProductOfNumbers()
  {
    prefixProducts.push_back(1);
  }

  void add(int num)
  {
    if (num == 0)
    {
      prefixProducts = {1};
      return;
    }
    int prevNum = prefixProducts.back();
    prefixProducts.push_back(num * prevNum);
  }

  int getProduct(int k)
  {
    if (k >= prefixProducts.size())
      return 0;
    return prefixProducts.back() / prefixProducts[prefixProducts.size() - 1 - k];
  }
};