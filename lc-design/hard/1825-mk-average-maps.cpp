#include <queue>
#include <map>

class MKAverage
{
  int m;
  int k;
  std::queue<int> stream;
  std::map<int, int> values;
  std::map<int, int, std::greater<int>> reverseValues;
  long long total;

public:
  MKAverage(int m, int k) : m(m), k(k), total(0)
  {
  }

  void addElement(int num)
  {
    stream.push(num);
    values[num]++;
    reverseValues[num]++;
    total += num;

    if (stream.size() > m)
    {
      int r = stream.front();
      stream.pop();
      values[r]--;
      if (values[r] == 0)
        values.erase(r);
      reverseValues[r]--;
      if (reverseValues[r] == 0)
        reverseValues.erase(r);
      total -= r;
    }
  }

  int calculateMKAverage()
  {
    if (stream.size() < m)
      return -1;

    int i = k;
    int mkAverage = total;
    for (auto it : values)
    {
      int count = it.second;
      while (i && count)
      {
        mkAverage -= it.first;
        --i;
        --count;
      }
    }
    i = k;
    for (auto it : reverseValues)
    {
      int count = it.second;
      while (i && count)
      {
        mkAverage -= it.first;
        --i;
        --count;
      }
    }
    return mkAverage / (m - (2 * k));
  }
};