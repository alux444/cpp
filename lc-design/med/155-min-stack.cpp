#include <stack>

struct Node
{
  int val;
  int minVal;
  Node(int val, int minVal) : val(val), minVal(minVal) {}
};

class MinStack
{
  std::stack<Node> stack;

public:
  MinStack()
  {
  }

  void push(int val)
  {
    if (stack.empty())
    {
      stack.push(Node(val, val));
      return;
    }
    // not empty
    int minVal = std::min(val, stack.top().minVal);
    stack.push(Node(val, minVal));
  }

  void pop()
  {
    stack.pop();
  }

  int top()
  {
    return stack.top().val;
  }

  int getMin()
  {
    return stack.top().minVal;
  }
};