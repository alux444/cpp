#include <string>

struct Node
{
    char val;
    bool isWord;
    Node *children[26];
    Node(char val) : val(val), isWord(false), children{} {}
};

class Trie
{
    Node *root;

public:
    Trie() : root(new Node('\n')) {}

    void insert(std::string word)
    {
        Node *cur = root;
        for (char ch : word)
        {
            if (cur->children[ch - 'a'] == nullptr)
            {
                cur->children[ch - 'a'] = new Node(ch);
            }
            cur = cur->children[ch - 'a'];
        }
        cur->isWord = true;
    }

    bool search(std::string word)
    {
        Node *cur = root;
        for (char ch : word)
        {
            if (cur == nullptr || cur->children[ch - 'a'] == nullptr)
            {
                return false;
            }
            cur = cur->children[ch - 'a'];
        }
        return cur == nullptr ? false : cur->isWord;
    }

    bool startsWith(std::string prefix)
    {
        Node *cur = root;
        for (char ch : prefix)
        {
            if (cur == nullptr || cur->children[ch - 'a'] == nullptr)
            {
                return false;
            }
            cur = cur->children[ch - 'a'];
        }
        return true;
    }
};