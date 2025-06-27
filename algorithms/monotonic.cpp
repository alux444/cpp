#include <vector>
#include <stack>
#include <queue>

void monotonic_stack(std::vector<int> vals) {
  std::stack<int> stack {};
  for (int val : vals) {
    while (!stack.empty() && stack.top() <= val)
      stack.pop();
    stack.push(val);
  }
}

void monotonic_queue(std::vector<int> vals) {
  std::deque<int> queue {};
  for (int val : vals) {
    while (!queue.empty() && queue.back() <= val)
      queue.pop_back();
    queue.push_back(val);
  }
}