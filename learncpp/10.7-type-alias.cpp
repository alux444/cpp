#include <iostream>

using Distance = double;
typedef double Distance2;

using FuncType = int (*)(double, char);

int add(double x, char y)
{
  return static_cast<int>(x) + static_cast<int>(y);
}

int subtract(double x, char y)
{
  return static_cast<int>(x) - static_cast<int>(y);
}

int compute(FuncType f, double x, char y)
{
  return f(x, y);
}

int main()
{
  Distance d1{4.44};
  Distance2 d2{4.56};
  std::cout << d1 << "\n";
  std::cout << d2 << "\n";

  double x{1.0};
  char y{'b'};
  std::cout << compute(add, x, y) << "\n";
  std::cout << compute(subtract, x, y) << "\n";
}