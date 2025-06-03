#include <string>

struct Node {
    char val;
    bool isWord;
    Node* children[26] = {};
    Node(char val) : val(val), isWord(false) {}
};

class WordDictionary {
    Node* root;

public:
    WordDictionary() : root(new Node('\n')) {}

    void addWord(std::string word) {
        Node* cur = root;
        for (char ch : word) {
            if (cur->children[ch - 'a'] == nullptr) {
                cur->children[ch - 'a'] = new Node(ch);
            }
            cur = cur->children[ch - 'a'];
        }
        cur->isWord = true;
    }

    bool search(std::string word) { return backtrackForWord(word, 0, root); }

    bool backtrackForWord(std::string& word, int idx, Node* node) {
        for (int i = idx; i < word.length(); i++) {
            if (node == nullptr)
                return false;
            char ch = word[i];
            if (ch == '.') {
                for (Node* n : node->children) {
                    if (n == nullptr)
                        continue;
                    if (backtrackForWord(word, i + 1, n))
                        return true;
                }
                return false;
            }
            if (node->children[ch - 'a'] == nullptr)
                return false;
            node = node->children[ch - 'a'];
        }
        return node && node->isWord;
    }
};