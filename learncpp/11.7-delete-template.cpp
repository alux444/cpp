#include <iostream>
#include <string>

template <typename T>
T addOne(T x)
{
  return x + 1;
}

// Use function template specialization to tell the compiler that addOne(const char*) should emit a compilation error
// const char* will match a string literal
template <>
const char *addOne(const char *x) = delete;

int main()
{
  std::cout << addOne("Hello, world!") << '\n'; // compile error

  return 0;
}