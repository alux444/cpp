#include <array>
#include <vector>

struct Trie
{
  int weight;
  std::array<Trie *, 27> children;
  Trie() : weight(0), children{} {}
};

class WordFilter
{
  Trie *root;

  int toIndex(char ch)
  {
    return ch == '#' ? 26 : ch - 'a';
  }

public:
  WordFilter(std::vector<std::string> &words)
  {
    root = new Trie();
    for (int weight = 0; weight < words.size(); ++weight)
    {
      std::string word = words[weight];
      // add every suffix combo, then add the whole word after
      for (int i = word.length() - 1; i >= 0; --i)
      {
        std::string suffix = word.substr(i, word.length());
        // suffix from the back index
        Trie *cur = root;
        for (char ch : suffix)
        {
          int idx = toIndex(ch);
          if (!cur->children[idx])
            cur->children[idx] = new Trie();
          cur = cur->children[idx];
          cur->weight = weight;
        }
        // add the '}'
        int delimIdx = toIndex('#');
        if (!cur->children[delimIdx])
          cur->children[delimIdx] = new Trie();
        cur = cur->children[delimIdx];
        cur->weight = weight;
        // add the whole word (possible prefix)
        for (char ch : word)
        {
          int idx = toIndex(ch);
          if (!cur->children[idx])
            cur->children[idx] = new Trie();
          cur = cur->children[idx];
          cur->weight = weight;
        }
      }
    }
  }

  int f(std::string pref, std::string suff)
  {
    std::string search = suff + "#" + pref;
    Trie *cur = root;
    for (char ch : search)
    {
      int idx = toIndex(ch);
      if (!cur->children[idx])
      {
        return -1;
      }
      cur = cur->children[idx];
    }
    return cur->weight;
  }
};