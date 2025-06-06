#include <stack>

class StockSpanner
{
  std::stack<std::array<int, 2>> st;

public:
  StockSpanner()
  {
  }

  int next(int price)
  {
    int consec = 1;
    while (!st.empty() && st.top()[0] <= price)
    {
      consec += st.top()[1];
      st.pop();
    }
    st.push({price, consec});
    return st.top()[1];
  }
};