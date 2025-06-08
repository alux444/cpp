#include <unordered_map>
#include <vector>

class Cashier
{
  int cust;
  int n;
  int discount;
  std::unordered_map<int, int> price; // id : price
public:
  Cashier(int n, int discount, std::vector<int> &products, std::vector<int> &prices) : n(n), cust(0), discount(discount)
  {
    for (int i = 0; i < products.size(); i++)
      price[products[i]] = prices[i];
  }

  double getBill(std::vector<int> product, std::vector<int> amount)
  {
    double bill{0};
    for (int i = 0; i < product.size(); i++)
      bill += price[product[i]] * amount[i];
    return ++cust % n == 0 ? (bill * (100 - discount)) / 100 : bill;
  }
};