#include <queue>
#include <vector>

class MedianFinder
{
  std::priority_queue<int> maxHeap;
  std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

public:
  MedianFinder() {}

  void addNum(int num)
  {
    maxHeap.push(num);
    if (!minHeap.empty() && maxHeap.top() > minHeap.top())
    {
      minHeap.push(maxHeap.top());
      maxHeap.pop();
    }
    int minDiff = minHeap.size() - maxHeap.size();
    if (minDiff > 1)
    {
      maxHeap.push(minHeap.top());
      minHeap.pop();
    }
    int maxDiff = maxHeap.size() - minHeap.size();
    if (maxDiff > 1)
    {
      minHeap.push(maxHeap.top());
      maxHeap.pop();
    }
  }

  double findMedian()
  {
    int elements = maxHeap.size() + minHeap.size();
    if (elements % 2 == 0)
      return (maxHeap.top() + minHeap.top()) / 2.0;
    return maxHeap.size() > minHeap.size()
               ? static_cast<double>(maxHeap.top())
               : static_cast<double>(minHeap.top());
  }
};