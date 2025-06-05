#include <vector>

class CustomStack
{
  std::vector<int> arr;
  int top;
  int cap;

public:
  CustomStack(int maxSize) : arr(maxSize), top(-1), cap(maxSize) {}

  void push(int x)
  {
    if (top == cap - 1)
      return;
    arr[++top] = x;
  }

  int pop()
  {
    if (top == -1)
      return -1;
    return arr[top--];
  }

  void increment(int k, int val)
  {
    int idx = 0;
    while (k > 0 && idx <= top)
    {
      arr[idx] += val;
      ++idx;
      --k;
    }
  }
};