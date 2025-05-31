#include <vector>
#include <list>

template <typename T>
class HashSet
{
private:
  static const size_t DEFAULT_BUCKETS = 101;
  std::vector<std::list<T>> buckets;
  size_t numElements;

  size_t getBucket(const T &value) const
  {
    return std::hash<T>{}(value) % buckets.size();
  }

public:
  HashSet(size_t bucketCount = DEFAULT_BUCKETS)
      : buckets(bucketCount), numElements(0) {}

  bool insert(const T &value)
  {
    size_t idx = getBucket(value);
    for (const auto &v : buckets[idx])
    {
      if (v == value)
        return false;
    }
    buckets[idx].push_back(value);
    numElements++;
    return true;
  }

  bool contains(const T &value) const
  {
    size_t idx = getBucket(value);
    for (const auto &v : buckets[idx])
    {
      if (v == value)
        return true;
    }
    return false;
  }

  bool erase(const T &value)
  {
    size_t idx = getBucket(value);
    for (auto it = buckets[idx].begin(); it != buckets[idx].end(); it++)
    {
      if (*it == value)
      {
        buckets[idx].erase(it);
        numElements--;
        return true;
      }
    }
    return false;
  }

  size_t size() const
  {
    return numElements;
  }

  bool empty() const
  {
    return numElements == 0;
  }
};