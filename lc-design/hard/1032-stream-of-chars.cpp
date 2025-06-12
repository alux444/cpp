#include <array>
#include <deque>
#include <vector>

struct Trie
{
  char val;
  bool isWord;
  std::array<Trie *, 26> children;
  Trie(char val) : val(val), isWord(false), children{} {}
};

class StreamChecker
{
  Trie *root;
  std::deque<char> curQuery;
  int maxSize;

public:
  StreamChecker(std::vector<std::string> &words) : curQuery{}, maxSize(0)
  {
    root = new Trie('\n');
    for (std::string &word : words)
    {
      Trie *cur = root;
      maxSize = std::max<int>(maxSize, word.length());
      // add them in reverse
      for (int i = word.length() - 1; i >= 0; --i)
      {
        char ch = word[i];
        if (!cur->children[ch - 'a'])
        {
          cur->children[ch - 'a'] = new Trie(ch);
        }
        cur = cur->children[ch - 'a'];
      }
      cur->isWord = true;
    }
  }

  bool query(char letter)
  {
    curQuery.push_back(letter);
    if (curQuery.size() > maxSize)
      curQuery.pop_front();
    Trie *cur = root;
    std::string str(curQuery.begin(), curQuery.end());
    for (int i = str.length() - 1; i >= 0; --i)
    {
      char ch = str[i];
      if (cur->isWord)
        return true;
      if (!cur->children[ch - 'a'])
        return false;
      cur = cur->children[ch - 'a'];
    }
    return cur->isWord;
  }
};