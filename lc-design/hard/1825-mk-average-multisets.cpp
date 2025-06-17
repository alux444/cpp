#include <queue>
#include <set>

class MKAverage
{
  int m;
  int k;
  std::queue<int> stream;
  std::multiset<int, std::greater<int>> largeToSmall;
  std::multiset<int> smallToLarge;
  std::multiset<int> middle;
  long long midTotal;

public:
  MKAverage(int m, int k) : m(m), k(k), midTotal(0) {}

  void addElement(int num)
  {
    if (stream.size() == m)
    {
      int toRemove = stream.front();
      stream.pop();
      if (largeToSmall.find(toRemove) != largeToSmall.end())
      {
        largeToSmall.erase(largeToSmall.find(toRemove));
      }
      else if (smallToLarge.find(toRemove) != smallToLarge.end())
      {
        smallToLarge.erase(smallToLarge.find(toRemove));
      }
      else
      {
        middle.erase(middle.find(toRemove));
        midTotal -= toRemove;
      }
    }
    stream.push(num);

    if (stream.size() < k)
    {
      smallToLarge.insert(num);
    }
    else if (stream.size() < 2 * k)
    {
      smallToLarge.insert(num);
      int smallest = *smallToLarge.begin();
      largeToSmall.insert(smallest);
      smallToLarge.erase(smallToLarge.begin());
    }
    else
    {
      // we need to balance
      smallToLarge.insert(num);
      int smallest = *smallToLarge.begin();
      middle.insert(smallest);
      smallToLarge.erase(smallToLarge.begin());

      midTotal += smallest;
      smallest = *middle.begin();
      middle.erase(middle.begin());
      largeToSmall.insert(smallest);
      midTotal -= smallest;

      // now we need to balance by adding the largest of the smaller into middle
      if (largeToSmall.size() > k)
      {
        int largest = *largeToSmall.begin();
        largeToSmall.erase(largeToSmall.begin());

        middle.insert(largest);
        midTotal += largest;

        // if middle has now ovf, but we know smallest is K
        // then we need to push to smallToLarge
        if (middle.size() > m - (2 * k))
        {
          auto it = middle.end();
          largest = *--it;
          smallToLarge.insert(largest);
          midTotal -= largest;
          middle.erase(std::prev(middle.end()));
        }
      }
    }
  }

  int calculateMKAverage()
  {
    if (stream.size() != m)
      return -1;
    return midTotal / (m - (2 * k));
  }
};