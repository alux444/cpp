#include <array>
#include <string>
#include <vector>

struct Trie
{
  char val;
  bool isWord;
  std::array<Trie *, 26> children;
  Trie(char val) : val(val), isWord(false), children{} {}
};

class MagicDictionary
{
  Trie *root;

public:
  MagicDictionary() : root(new Trie('\n')) {}

  void buildDict(std::vector<std::string> dictionary)
  {
    for (std::string &word : dictionary)
    {
      Trie *cur = this->root;
      for (char ch : word)
      {
        if (!cur->children[ch - 'a'])
          cur->children[ch - 'a'] = new Trie(ch);
        cur = cur->children[ch - 'a'];
      }
      cur->isWord = true;
    }
  }

  bool search(std::string searchWord)
  {
    return backtrackSearch(searchWord, 0, false, this->root);
  }

  bool backtrackSearch(std::string word, int idx, bool isLetterUsed, Trie *node)
  {
    // if end - check if we have the end of the word
    if (!node)
      return false;
    if (idx == word.size())
      return node && node->isWord && isLetterUsed;

    size_t pos = word[idx] - 'a';
    // lets just keep going with this value if we can
    if (node->children[pos])
      if (backtrackSearch(word, idx + 1, isLetterUsed,
                          node->children[pos]))
        return true;

    // now branch out no matter what in this case
    if (!isLetterUsed)
      for (Trie *child : node->children)
        if (child)
        {
          if (child->val == word[idx])
            continue;
          if (backtrackSearch(word, idx + 1, true, child))
            return true;
        }

    return false;
  }
};