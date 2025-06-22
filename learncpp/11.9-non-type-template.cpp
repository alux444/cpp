#include <cmath>
#include <iostream>

template <double D>
double getSqrt()
{
  static_assert(D >= 0 && "getSqrt<D>(): D must be positive");
  if (D >= 0)
    return std::sqrt(D);
  return 0.0;
}

// why is this better than:
// double getSqrt(double d)
// {
//     assert(d >= 0.0 && "getSqrt(): d must be non-negative");

//     // The assert above will probably be compiled out in non-debug builds
//     if (d >= 0)
//         return std::sqrt(d);

//     return 0.0;
// }

// because we get a compile-time error with static assert rather than runtime

int main()
{
  std::cout << getSqrt<5.0>() << '\n';
  std::cout << getSqrt<-5.0>() << '\n';

  return 0;
}