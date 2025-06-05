#include <string>
#include <array>
#include <unordered_map>

struct Trie
{
  char val;
  int cnt;
  std::array<Trie *, 26> children;
  Trie(char val) : val(val), cnt(0), children{} {}
};

class MapSum
{
  std::unordered_map<std::string, int> map; // key : val
  Trie *root;

public:
  MapSum() : root(new Trie('\n')) {}

  void insert(std::string key, int val)
  {
    if (map.find(key) != map.end())
    {
      int prevVal = map[key];
      map[key] = val;
      val -= prevVal;
    }
    else
    {
      map[key] = val;
    }

    Trie *cur = root;
    for (char ch : key)
    {
      if (!cur->children[ch - 'a'])
        cur->children[ch - 'a'] = new Trie(ch);
      cur->children[ch - 'a']->cnt += val;
      cur = cur->children[ch - 'a'];
    }
  }

  int sum(std::string prefix)
  {
    Trie *cur = root;
    for (char ch : prefix)
    {
      if (!cur->children[ch - 'a'])
        return 0;
      cur = cur->children[ch - 'a'];
    }
    return cur->cnt;
  }
};