template <class T>
class UnionFind
{
private:
  std::unordered_map<T, T> id;

public:
  T find(T x)
  {
    T y = id.count(x) ? id[x] : x;
    if (y != x)
    {
      y = find(y);
      id[x] = y;
    }
    return y;
  }

  void union_(T x, T y)
  {
    id[find(x)] = find(y);
  }
};
