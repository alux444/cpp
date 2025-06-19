#include <deque>

class FrontMiddleBackQueue
{
  std::deque<int> a;
  std::deque<int> b;

  // Maintain: size(a) == size(b) OR size(a) == size(b) + 1
  void rebalance()
  {
    while (a.size() > b.size() + 1)
    {
      b.push_front(a.back());
      a.pop_back();
    }
    while (b.size() > a.size())
    {
      a.push_back(b.front());
      b.pop_front();
    }
  }

public:
  FrontMiddleBackQueue() {}

  bool empty() { return a.empty() && b.empty(); }

  void pushFront(int val)
  {
    a.push_front(val);
    rebalance();
  }

  void pushMiddle(int val)
  {
    // need to make sure the value is the middle
    if ((a.size() + b.size()) % 2 != 0)
    {
      b.push_front(a.back());
      a.pop_back();
    }
    a.push_back(val);
    rebalance();
  }

  void pushBack(int val)
  {
    b.push_back(val);
    rebalance();
  }

  int popFront()
  {
    if (empty())
      return -1;
    int res = a.front();
    a.pop_front();
    rebalance();
    return res;
  }

  int popMiddle()
  {
    if (empty())
      return -1;
    int res = a.back();
    a.pop_back();
    rebalance();
    return res;
  }

  int popBack()
  {
    if (empty())
      return -1;
    int res;
    if (b.empty())
    {
      res = a.back();
      a.pop_back();
    }
    else
    {
      res = b.back();
      b.pop_back();
    }
    rebalance();
    return res;
  }
};