#include <vector>
#include <list>

template <typename K, typename V>
class HashMap
{
private:
  static const size_t DEFAULT_BUCKETS = 101;
  // vector is an underlying array, list is underlying DLL
  std::vector<std::list<std::pair<K, V>>> buckets;
  size_t numElements;

  size_t getBucket(const K &key) const
  {
    return std::hash<K>{}(key) % buckets.size();
  }

public:
  HashMap(size_t bucketCount = DEFAULT_BUCKETS) : buckets(bucketCount), numElements(0) {}

  void insert(const K &key, const V &val)
  {
    size_t idx = getBucket(key);
    for (auto &kv : buckets[idx])
    {
      if (kv.first == key)
      {
        kv.second = val;
        return;
      }
    }
    buckets[idx].emplace_back(std::make_pair(key, val));
    numElements++;
    return;
  }

  bool contains(const K &key) const
  {
    size_t idx = getBucket(key);
    for (const auto &kv : buckets[idx])
    {
      if (kv.first == key)
        return true;
    }
    return false;
  }

  V &at(const K &key)
  {
    size_t idx = getBucket(key);
    for (auto &kv : buckets[idx])
    {
      if (kv.first == key)
        return kv.second;
    }
    throw std::out_of_range("Key not found");
  }

  const V &at(const K &key) const
  {
    size_t idx = getBucket(key);
    for (const auto &kv : buckets[idx])
    {
      if (kv.first == key)
        return kv.second;
    }
    throw std::out_of_range("Key not found");
  }

  bool erase(const K &key)
  {
    size_t idx = getBucket(key);
    for (auto it = buckets[idx].begin(); it != buckets[idx].end(); it++)
    {
      if (it->first == key)
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